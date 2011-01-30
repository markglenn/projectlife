#pragma once
#include <string>

#include "cIStream.h"

#define ios_begin std::ios_base::beg
#define ios_end std::ios_base::end

class cIFile
{
public:
	cIFile(std::string filename, unsigned char *data, long length);
	cIFile () {}
	~cIFile(void);

	int Read (void *buffer, long size);
	bool Seek (long offset, int origin);
	long Tell () { return m_position; }
	long Size () { return m_length; }

	bool Eof () { return m_position >= m_length; }

	// Accessors
	unsigned char * GetData () { return m_data; }
	std::string GetLine ();
	std::string GetFilename () { return m_filename; }

protected:
	unsigned char  *m_data;
	long			m_length;
	long			m_position;

	std::string		m_filename;
};
