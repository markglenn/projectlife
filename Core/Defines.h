#ifndef __DEFINES_H__
#define __DEFINES_H__

#ifdef	_DEBUG
	#define	Assert(x) if ((x) == false) __asm { int 3 }
#else
	#define	Assert(x) {}
#endif

#endif