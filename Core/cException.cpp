#include <string.h>

#include "cException.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cException::cException(int error, std::string message, 
	char *filename, char *function, long line)
/////////////////////////////////////////////////////////////////////////////////////
		: m_errorNumber(error), m_message (message),
		  m_filename (filename), m_function (function),
		  m_line (line)
{}

std::string cException::what ()
{
	std::string desc;
	char		line[10];
	char		errorNumber[10];

	sprintf(line, "%d", m_line);
	sprintf(errorNumber, "%d", m_errorNumber);

	desc  = "Exception Occurred";
	desc += "\n----------------------------";
	desc += "\nError Number : ";
	desc += errorNumber;
	desc += "\nFile         : ";
	desc += m_filename;
	desc += "\nFunction     : ";
	desc += m_function;
	desc += "\nLine         : ";
	desc += line;
	desc += "\nDescription  : ";
	desc += m_message;

	return desc;

}