#pragma once

#include <string>
#include <map>
#include "../Core/cSingleton.h"

#define REGISTER_CLASS(base, object, id)				\
	namespace											\
	{													\
    cRegisterInFactory<base, object> registerMe(id);	\
	}


typedef std::string defaultIDKeyType;

template <	class ancestorType,
			class manufacturedObject, 
			typename classIDKey=defaultIDKeyType>
class cRegisterInFactory
{
public:
	static ancestorType* createInstance()
	{
		return new manufacturedObject;
	}

	cRegisterInFactory(const classIDKey &id)
	{
		cFactory<ancestorType>::Instance().Register(id, createInstance);
	}

};

template <class manufactoredObject, typename classIDKey = defaultIDKeyType>
class cFactory
{
	typedef manufactoredObject* (*tFnPointer)();
	typedef std::map<classIDKey, tFnPointer> tFnRegistry;

	tFnRegistry m_registry;

public:
	cFactory(void) {};
	~cFactory(void) {};

	void Register (std::string identifier, tFnPointer fn)
	{
		m_registry[identifier] = fn;
	};

	static cFactory& Instance();
	manufactoredObject* Create (const classIDKey &identifier) const
	{
		tFnRegistry::const_iterator regEntry = m_registry.find(identifier);
		if (regEntry != m_registry.end())
			return (*regEntry).second();

		return NULL;
	}
};

template <class manufactoredObject, typename classIDKey>
cFactory<manufactoredObject, classIDKey> &cFactory<manufactoredObject, classIDKey>::Instance()
{
	static cFactory theInstance;
	return theInstance;
}