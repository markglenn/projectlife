#pragma once
#include <functional>
#include <algorithm>

template <class T>
class cDynamicClass
{
public:
	cDynamicClass(void);
	~cDynamicClass(void);

	static void* GetClass () { return (void *)new T; } 
};
