#pragma once

#include <assert.h>

template <class T>
class cSingleton
{

public:
	cSingleton();
	~cSingleton ();
	
	static T* Singleton ();

//protected:
	static T* m_singleton;
};

template <class T>
T* cSingleton <T>::m_singleton = 0;

template <class T>
cSingleton <T>::cSingleton()
{
	assert ( !m_singleton);
	m_singleton = (T*)this;
}

template <class T>
cSingleton <T>::~cSingleton ()
{
	assert (m_singleton);
	m_singleton = 0;
}

template <class T>
T* cSingleton <T>::Singleton ()
{
	return m_singleton;
}
