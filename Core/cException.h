#pragma once

#include <string>

#define EXCEPTION(a,b) (cException(a,b,__FILE__,__FUNCTION__,__LINE__))

/** The thrown exception class
    @remarks
		This is the class that is thrown with the current error message.
*/
class cException
{
public:
	/**
		Exception constructor.

		@param error		The current error message.
		@param message		The message to display.
		@param filename		The filename the exception occurred in.
		@param function		The function the exception occurred in.
		@param line			The line number the exception occured at.
	*/
	cException(int error, std::string message, char *filename, char *function, long line);

	/// Returns the error message
	std::string what ();

private:
	std::string		m_message;				///< Error message
	int				m_errorNumber;			///< Error number
	std::string		m_filename;				///< File where exception occurred
	std::string		m_function;				///< Function where exception occurred
	long			m_line;					///< Line where exception occurred
};
