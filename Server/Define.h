#ifndef Define_h__
#define Define_h__
#include "struct.h"

#include <map>
#include <io.h>
#include <algorithm>

#include <iostream>
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_errors.h"

#pragma comment (lib, "fmodex_vc.lib")

using namespace std;



#define DECLARE_SINGLETON(ClassName)			\
private:										\
	static ClassName*	m_pInstance;			\
public:											\
	static ClassName*	GetInstance(void)		\
	{											\
		if(m_pInstance == NULL)					\
		m_pInstance = new ClassName;			\
												\
		return m_pInstance;						\
	}											\
	void DestroyInstance(void)					\
	{											\
		if(m_pInstance)							\
		{										\
			delete m_pInstance;					\
			m_pInstance = NULL;					\
		}										\
	}											\
private:										\
	ClassName(ClassName& r){;}					\

#define IMPLEMENT_SINGLETON(ClassName)			\
	ClassName* ClassName::m_pInstance = NULL;	\

class CStringCmp
{
private:
	const char*		m_pName;

public:
	explicit CStringCmp(const char* pKey)
		:m_pName(pKey) {}

public:
	template<typename T>
	bool operator () (T data)
	{
		return (!lstrcmp(data.first, m_pName));
	}
};

#endif // Define_h__						
