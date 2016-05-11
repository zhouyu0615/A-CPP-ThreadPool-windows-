#pragma once
#include "Thread.h"
#include "ThreadList.h"
#include "ThreadStack.h"
#include "MyMutex.h"
#include "TaskQueue.h"

class CTask;
class CThread;

enum PRIORITY
{
     NORMAL,
	 HIGH
};



class CBaseThreadPool
{
 public:
	 virtual CThread*  PopIdleThread() = 0;
	 virtual CTask*   GetNewTask() = 0;
     virtual bool SwitchActiveThread(CThread*) = 0;
};





class CMyThreadPool:public CBaseThreadPool
{
public:
	CMyThreadPool(int NumofThreads);
	~CMyThreadPool();


public:
	virtual CThread*  PopIdleThread() ;
	virtual CTask*   GetNewTask();
	virtual bool SwitchActiveThread(CThread*);

public:
	bool addTask(CTask* task, PRIORITY priority);
	bool start();
	bool destoryThreadPool();
private:
	int m_nThreadNum;
	bool m_bIsExit;

	CThreadStack m_IdleThreadStack;
	CThreadList  m_ActiveThreadList;
	CTaskQueue   m_TaskQueue;
};

