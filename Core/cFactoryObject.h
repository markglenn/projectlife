#pragma once

#include <string>

template <class T, class registerClass, typename >
class cFactoryObject
{
public:
	cFactoryObject(void) {};
	~cFactoryObject(void) {};

	void *Create() { return (void *)new T; }

private:
	class cRegisterFactory
	{
		cRegisterFactory() 
		{ registerClass::Register ("T", T::Create()); }
	};

	static cRegisterFactory m_registerme;
};
