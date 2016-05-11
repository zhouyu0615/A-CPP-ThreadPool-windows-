#pragma once
#include <deque>
#include "MyMutex.h"

class CTask;
class CTaskQueue
{
public:
	CTaskQueue();
	~CTaskQueue();

public:
	CTask* pop();
	bool push(CTask* task);
	bool pushFront(CTask* task);
	bool isEmpty();
	bool clear();

private:
	std::deque<CTask*> m_TaskQueue;
	CMyMutex m_mutex;
};

