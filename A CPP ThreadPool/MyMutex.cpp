#include "stdafx.h"
#include "MyMutex.h"


CMyMutex::CMyMutex()
{
	InitializeCriticalSection(&m_Cs);
}


CMyMutex::~CMyMutex()
{
	DeleteCriticalSection(&m_Cs);
}


bool CMyMutex::Lock()
{
	EnterCriticalSection(&m_Cs);
	return true;
}
bool CMyMutex::UnLock()
{

	LeaveCriticalSection(&m_Cs);
	return true;
}


