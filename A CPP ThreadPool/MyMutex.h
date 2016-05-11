#pragma once
#include <windows.h>
class CMyMutex
{
public:
	CMyMutex();
	~CMyMutex();

	bool Lock();
	bool UnLock();

private:
	CRITICAL_SECTION m_Cs;
};

