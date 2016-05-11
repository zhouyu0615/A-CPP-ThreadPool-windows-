#pragma once
#include <list>
#include "MyMutex.h"

class CThread;

class CThreadList
{
public:
	CThreadList();
	~CThreadList();

public:
	bool addThread(CThread* thread);
	bool removeThread(CThread* thread);
	int getSize();
	bool isEmpty();
	bool clear();


private:
	std::list<CThread*> m_list;
	CMyMutex m_mutex;

};

