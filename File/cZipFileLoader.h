#pragma once
#include "cFileLoader.h"

typedef unsigned long dword;
typedef unsigned short word;
typedef unsigned char byte;

class cZipFileLoader : public cFileLoader
{
public:
	cZipFileLoader();

	virtual bool InitDirectory (std::string directory);
	virtual ~cZipFileLoader(void);

	virtual unsigned char *ReadFile (std::string filename);
    
protected:
#pragma pack(2)
	struct sZipLocalHeader
	{
		enum
		{
			SIGNATURE	= 0x04034b50,
			COMP_STORE	= 0,
			COMP_DEFLAT	= 8
		};

		dword	sig;
		word	version;
		word	flag;
		word	compression;
		word	modTime;
		word	modDate;
		dword	crc32;
		dword	cSize;
		dword	ucSize;
		word	fnameLen;
		word	xtraLen;
	};

	struct sZipDirHeader
	{
		enum { SIGNATURE = 0x06054B50 };	// Dir signature
		
		dword	sig;
		word	nDisk;
		word	nStartDisk;
		word	nDirEntries;
		word	totalDirEntries;
		dword	dirSize;
		dword	dirOffset;
		word	commentLen;
	};

	struct sZipDirFileHeader
	{
		enum
		{
			SIGNATURE		= 0x02014B50,	// File signature
			COMP_STORE		= 0,			// No compression	(STORED)
			COMP_DEFLATE	= 8				// Compressed		(DEFLATED)
		};

		dword	sig;
		word	verMade;
		word	verNeeded;
		word	flag;
		word	compression;
		word	modTime;
		word	modDate;
		dword	crc32;
		dword	cSize;
		dword	ucSize;
		word	fnameLen;
		word	xtraLen;
		word	commentLen;
		word	diskStart;
		word	intAttr;
		dword	extAttr;
		dword	hdrOffset;

		char *GetName	() const { return (char *)(this + 1);	}
		char *GetExtra	() const { return GetName() + fnameLen;	}
		char *GetComment() const { return GetExtra() + xtraLen; }
	};

	std::string GetFilename (int i) const;
	int			GetFileLen	(int i) const;

	unsigned char *m_pDirData;
	const sZipDirFileHeader **m_papDir;
	int m_nEntries;
	FILE *m_fp;
#pragma pack()
};
