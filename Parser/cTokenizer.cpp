#include "cTokenizer.h"

///////////////////////////////////////////////////////////////////////////////
cTokenizer::cTokenizer(std::istream& input): m_input(input)
{
	// set flags to default
	m_eolIsSignificant = false;
	m_lineNo = 0;
	m_lowerCaseMode = false;
	m_pushedBack = false;
	m_slslComments = true;
	m_slstComments = true;
	// reset tables
	resetSyntax();
	wordChars('a', 'z');
	wordChars('A', 'Z');
	wordChars(128, 255);
	wordChars('_', '_');
	quoteChar('"');
	quoteChar('\'');
	whitespaceChars(0, ' ');
	parseNumbers();
}

///////////////////////////////////////////////////////////////////////////////
cTokenizer::~cTokenizer() {
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::commentChar(int ch)
{
	if(ch >= 0 && ch <= NCHAR)
		{
			m_chType[ch] = CT_COMMENT;
		}
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::eolIsSignificant(bool flag)
{
	m_eolIsSignificant = flag;
}

///////////////////////////////////////////////////////////////////////////////
int cTokenizer::lineno(void)
{
	return m_lineNo;
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::lowerCaseMode(bool flag)
{
	m_lowerCaseMode = flag;
}

///////////////////////////////////////////////////////////////////////////////
int cTokenizer::nextToken(void)
{
	#define _CTYPE(c)	(((c) < 0) ? CT_WHITESPACE : (((c) > NCHAR) ? CT_ALPHA : m_chType[c]))

	// check if token has been pushed back
	if(m_pushedBack == true)
		{
			m_pushedBack = false;
			return m_ttype;
		}

	// get character from input stream
	int ch = m_input.get(); if(ch < 0) return TT_EOF;
	int ctype = _CTYPE(ch);

	// strip possible white space
	while((ctype & CT_WHITESPACE) == CT_WHITESPACE)
		{
			if(ch == '\n')
				{
					++m_lineNo;
					if(m_eolIsSignificant == true)
						{
							return (m_ttype = TT_EOL);
						}
				}
			ch = m_input.get(); if(ch < 0) return TT_EOF;
			ctype = _CTYPE(ch);
		}

	// parse number
	if((ctype & CT_DIGIT) == CT_DIGIT)
		{
			// if we got a minus sign we must also have a digit.
			if(ch == '-')
				{
					int pk = m_input.peek();
					if((_CTYPE(pk) & CT_DIGIT) == 0 || pk == '-')
						return (m_ttype = ch);
				}

			// get entire number
			std::string strnum = "";
			while((ctype & CT_DIGIT) == CT_DIGIT)
				{
					strnum += ch;
					int pk = m_input.peek();
					if((_CTYPE(pk) & CT_DIGIT) == 0 && pk != '.')
						break;
					ch = m_input.get(); if(ch < 0) break;
					ctype = CT_DIGIT;
				}

			// return number token
			m_nval = atof(strnum.c_str());
			return (m_ttype = TT_NUMBER);
		}

	// parse word
	if((ctype & CT_ALPHA) == CT_ALPHA)
		{
			std::string strwrd = "";
			while((ctype & CT_ALPHA) == CT_ALPHA)
				{
					strwrd += ch;
					int pk = m_input.peek();
					if((_CTYPE(pk) & CT_ALPHA) == 0)
						break;
					ch = m_input.get();
					ctype = CT_ALPHA;
				}
			// force lower case word
			if(m_lowerCaseMode == true)
				{
					for(int i = 0; i < strwrd.length(); i++)
						strwrd[i] = tolower(strwrd[i]);
				}
			// return word token
			m_sval = strwrd;
			return (m_ttype = TT_WORD);
		}

	// parse single-line comment
	if((ctype & CT_COMMENT) == CT_COMMENT)
		{
			while((ch = m_input.get()) >= 0 && (ch != '\n' && ch != '\r'));
			return nextToken();
		}

	// parse quoted string
	if((ctype & CT_QUOTE) == CT_QUOTE)
		{
			m_ttype = ch;
			std::string strqte = "";
			while((ch = m_input.get()) >= 0 && (ch != m_ttype && ch != '\n' && ch != '\r'))
				{
					strqte += ch;
				}
			// return quote token
			m_sval = strqte;
			return (m_ttype = TT_STRING);
		}

	// parse comments
	if(ch == '/' && (m_slslComments || m_slstComments))
		{
			int pk = m_input.peek();
			if(pk == '/' && m_slslComments == true)
				{
					// ignore characters until line break
					while((ch = m_input.get()) >= 0 && (ch != '\n' && ch != '\r'));
					++m_lineNo;
					// return next token
					if(ch < 0) return TT_EOF;
					return nextToken();
				}
			else if(pk == '*' && m_slstComments == true)
				{
					int pch = 0;
					while((ch = m_input.get()) >= 0 && (ch != '/' || pch != '*'))
						{
							if(ch == '\n') ++m_lineNo;
							pch = ch;
						}
					if(ch < 0) return TT_EOF;
					return nextToken();
				}
		}

	// return character token
	return (m_ttype = ch);
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::ordinaryChar(int ch)
{
	if(ch >= 0 && ch <= NCHAR)
		{
			m_chType[ch] = 0;
		}
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::ordinaryChars(int low, int hi)
{
	if(low < 0) low = 0; if(hi > NCHAR) hi = NCHAR;
	while(low <= hi)
		{
			m_chType[low] = 0;
			++low;
		}
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::parseNumbers(void)
{
	for(int i = '0'; i <= '9'; i++)
		{
			m_chType[i] |= CT_DIGIT;
		}
	m_chType['-'] |= CT_DIGIT;
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::pushBack(void)
{
	m_pushedBack = true;
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::quoteChar(int ch)
{
	if(ch >= 0 && ch <= NCHAR)
		{
			m_chType[ch] |= CT_QUOTE;
		}
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::resetSyntax(void)
{
	for(int i = 0; i < NCHAR; i++)
		{
			m_chType[i] = 0;
		}
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::slashSlashComments(bool flag)
{
	m_slslComments = flag;
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::slashStarComments(bool flag)
{
	m_slstComments = flag;
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::whitespaceChars(int low, int hi)
{
	if(low < 0) low = 0; if(hi > NCHAR) hi = NCHAR;
	while(low <= hi)
		{
			m_chType[low] |= CT_WHITESPACE;
			++low;
		}
}

///////////////////////////////////////////////////////////////////////////////
void cTokenizer::wordChars(int low, int hi)
{
	if(low < 0) low = 0; if(hi > NCHAR) hi = NCHAR;
	while(low <= hi)
		{
			m_chType[low] |= CT_ALPHA;
			++low;
		}
}
