#pragma once
#include <stack>
#include "MyMutex.h"

class CThread;

class CThreadStack
{
public:
	CThreadStack();
	~CThreadStack();

	bool isEmpty();
	bool clear();
	int getSize();
	bool push(CThread* thread);
	CThread* pop();

private:
	std::stack<CThread*> m_ThreadStack;
	CMyMutex m_mutex;
};


