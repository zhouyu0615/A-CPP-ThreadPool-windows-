#include "stdafx.h"
#include "MyThreadPool.h"


CMyThreadPool::CMyThreadPool(int NumofThreads) :m_nThreadNum(NumofThreads)
{


};


CMyThreadPool::~CMyThreadPool()
{


}



CThread* CMyThreadPool::PopIdleThread()
{
	return m_IdleThreadStack.pop();
}
CTask*   CMyThreadPool::GetNewTask()
{

	return m_TaskQueue.pop();
}
bool CMyThreadPool::SwitchActiveThread(CThread* thread)
{
	if (!m_TaskQueue.isEmpty())
	{
		CTask* pTask = NULL;
		pTask = m_TaskQueue.pop();
		thread->assignTask(pTask);
		thread->startTask();
	}
	else
	{
		m_ActiveThreadList.removeThread(thread);
		m_IdleThreadStack.push(thread);
	}
	return true;
}


bool CMyThreadPool::addTask(CTask* task, PRIORITY priority)
{

	if (!task || m_bIsExit)
	{
		return false;
	}

	if (priority==PRIORITY::HIGH)
	{
		m_TaskQueue.pushFront(task);
	}
	else
	{
		m_TaskQueue.push(task);
	}

	if (!m_IdleThreadStack.isEmpty()) //´æÔÚ¿ÕÏÐÏß³Ì//
	{
		task = m_TaskQueue.pop();
		if (task==NULL)
		{
			return 0;
		}

		CThread* pThread = PopIdleThread();
		m_ActiveThreadList.addThread(pThread);
		pThread->assignTask(task);
		pThread->startTask();
	}

};



bool CMyThreadPool::start()
{
	for (int i = 0; i < m_nThreadNum;i++)
	{
		CThread* pthread = new CThread(this);
		pthread->StartThread();
		m_IdleThreadStack.push(pthread);
	}
	return true;
};


bool CMyThreadPool::destoryThreadPool()
{

	return true;
};



