#include <algorithm>
#include "cZipFileLoader.h"
#include "../zlib/zlib.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

// This file based on Javier Arevalo's quick'n dirty ZIP file reader class

REGISTER_CLASS (cFileLoader, cZipFileLoader, ".PK3")

/////////////////////////////////////////////////////////////////////////////////////
cZipFileLoader::cZipFileLoader()
	: m_nEntries(0), m_fp(0), m_pDirData(0)
/////////////////////////////////////////////////////////////////////////////////////
{
	cFileLoader();
}

/////////////////////////////////////////////////////////////////////////////////////
cZipFileLoader::~cZipFileLoader(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	if (m_fp)
		fclose (m_fp);
	if (m_pDirData)
		delete[] m_pDirData;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cZipFileLoader::InitDirectory(std::string directory)
/////////////////////////////////////////////////////////////////////////////////////
{
	m_directory = directory;
    sZipDirHeader dh;

	m_fp = fopen (directory.c_str(), "rb");

	if (m_fp == NULL)
		return false;

	fseek (m_fp, -(int)sizeof(dh), SEEK_END);
	long dhOffset = ftell(m_fp);

	// Read in the header
	fread(&dh, sizeof(dh), 1, m_fp);

	// Check the signature
	if (dh.sig != sZipDirHeader::SIGNATURE)
	{
		fclose (m_fp);	m_fp = NULL;
		return false;
	}

	// Seek to the beginning of the directory
	fseek (m_fp, dhOffset - dh.dirSize, SEEK_SET);

	// Allocate the data buffer, and read in the whole directory
	m_pDirData = new unsigned char[dh.dirSize + dh.nDirEntries * sizeof(*m_papDir)];

	if (!m_pDirData)
	{
		fclose (m_fp);	m_fp = NULL;
		return false;
	}

	fread (m_pDirData, dh.dirSize, 1, m_fp);

	// Now process each entry
	unsigned char *pfh = m_pDirData;
	m_papDir = (const sZipDirFileHeader **)(m_pDirData + dh.dirSize);

	bool ret = true;

	for (int i = 0; i < dh.nDirEntries && ret; i++)
	{
		sZipDirFileHeader &fh = *(sZipDirFileHeader *)pfh;

		// Store the address of the nth file for qucker access
		m_papDir[i] = &fh;

		// Check the directory entry integrity
		if (fh.sig != sZipDirFileHeader::SIGNATURE)
			ret = false;
		else
		{
			pfh += sizeof(fh);

			// Convert UNIX slashes to DOS backslashes
			for (int j = 0; j < fh.fnameLen; j++)
			{
				if (pfh[j] == '\\')
					pfh[j] = '/';

				pfh[j] = tolower (pfh[j]);
			}

			// Skip name, extra and comment fields
			pfh += fh.fnameLen + fh.xtraLen + fh.commentLen;
		}
	}

	if (ret == false)
	{
		fclose (m_fp); m_fp = NULL;
		delete[] m_pDirData;
		return false;
	}

	m_nEntries = dh.nDirEntries;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
std::string cZipFileLoader::GetFilename(int i) const
/////////////////////////////////////////////////////////////////////////////////////
{
	std::string ret;

	if (i < 0 || i >= m_nEntries)
		return std::string(0);
	ret.assign(m_papDir[i]->GetName(), (int)m_papDir[i]->fnameLen);

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////
int cZipFileLoader::GetFileLen(int i) const
/////////////////////////////////////////////////////////////////////////////////////
{
	if (i < 0 || i >= m_nEntries)
		return -1;
	return m_papDir[i]->ucSize;
}

/////////////////////////////////////////////////////////////////////////////////////
unsigned char* cZipFileLoader::ReadFile (std::string filename)
/////////////////////////////////////////////////////////////////////////////////////
{
	int file = -1;
	char *data;
	int err;

	// Check if the file is open
	if (m_fp == NULL)
		return NULL;

	// Make the filename all lowercase
	std::transform (filename.begin(), filename.end(), 
			filename.begin(), tolower);

	// Find the filename
	for (int i = 0; i < m_nEntries; i++)
	{
		if (GetFilename(i) == filename)
		{
			file = i;
			break;
		}
	}

	// If the file does not exist
	if (file == -1)
		return NULL;

	m_filesize = GetFileLen (file);
	// Go to the actual file and read the local header
	fseek (m_fp, m_papDir[i]->hdrOffset, SEEK_SET);
	sZipLocalHeader h;

	fread (&h, sizeof(h), 1, m_fp);

	if (h.sig != sZipLocalHeader::SIGNATURE)
		return NULL;

	// Seek the extra fields
	fseek (m_fp, h.fnameLen + h.xtraLen, SEEK_CUR);

	if (h.compression == sZipLocalHeader::COMP_STORE)
	{
		data = new char[h.cSize];
		if (!data)
			return false;

		fread (data, h.cSize, 1, m_fp);
		return (unsigned char *)data;
	}

	if (h.compression != sZipLocalHeader::COMP_DEFLAT)
		return NULL;

	// Allocate compressed data buffer
	char* cData = new char[h.cSize];
	if (!cData)
		return NULL;

	// Read in the compressed data
	fread (cData, h.cSize, 1, m_fp);

	z_stream stream;

	// Allocate the memory for the file
	data = new char[h.ucSize];

	// Setup the stream object
	stream.next_in		= (Bytef *)	cData;
	stream.avail_in		= (uInt   )	h.cSize;
	stream.next_out		= (Bytef *)	data;
	stream.avail_out	= h.ucSize;
	stream.zalloc		= (alloc_func)	0;
	stream.zfree		= (free_func)	0;

	// Inflate the compressed file
	err = inflateInit2 (&stream, -MAX_WBITS);
	if (err == Z_OK)
	{
		err = inflate(&stream, Z_STREAM_END);
		inflateEnd(&stream);

		if (err == Z_STREAM_END)
			err = Z_OK;

		inflateEnd(&stream);
	}

	delete[] cData;

	if (err != Z_OK)
		return NULL;

	return (unsigned char *)data;
}