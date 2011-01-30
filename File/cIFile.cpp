#include <memory.h>
#include <stdio.h>

#include "cIFile.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cIFile::cIFile(std::string filename, unsigned char *data, long length)
	: m_data(data), m_length(length), m_position(0), m_filename(filename)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cIFile::~cIFile(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	if (m_data)
		delete[] m_data;
}

/////////////////////////////////////////////////////////////////////////////////////
int cIFile::Read (void *buffer, long size)
/////////////////////////////////////////////////////////////////////////////////////
{

	// Get the full length of the input
	int length = size;

	// Check what we still can read
	if (length + m_position > m_length)
		length = m_length - m_position;

	memcpy (buffer, &m_data[m_position], length);
	m_position += length;

	return length;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cIFile::Seek (long offset, int origin)
/////////////////////////////////////////////////////////////////////////////////////
{
	// Choose the seek method
	switch (origin)
	{
		case SEEK_CUR:
			m_position += offset;
			break;

		case SEEK_END:
			m_position = m_length + offset;
			break;

		case SEEK_SET:
			m_position = offset;
			break;
	}

	// Validate the cursor position
	if (m_position < 0)
	{
		m_position = 0;
		return false;
	}

	if (m_position >= m_length)
	{
		m_position = m_length - 1;
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
std::string cIFile::GetLine ()
/////////////////////////////////////////////////////////////////////////////////////
{
	std::string line;

	// Loop through the rest of the data
	for (int i = m_position; i < m_length; i++)
	{
		// Find the CR in the line
		if (m_data[i] == 13)
		{
			line.assign ((char *)m_data + m_position, i - m_position);
			m_position = i + 1;
			
			// Move past the LF in DOS format CRLF
			if (i < m_length - 1)
				if (m_data[m_position] == 10)
					m_position++;
			
			return line;
		}
	}

	line.assign ((char *)m_data + m_position, m_length - m_position);
	m_position = m_length;

	return line;

}