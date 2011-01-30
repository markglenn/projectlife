#pragma once

#include <streambuf>

class cIStream : public std::streambuf
{
public:
	cIStream(unsigned char *data, int length) 
		{ setg ((char *)data, (char *)data, (char *)data + length); }
};
