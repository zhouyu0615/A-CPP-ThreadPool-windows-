#include "stdafx.h"
#include "Thread.h"

CThread::CThread(void) :
m_pTask(NULL),
m_bRun(false)
{
	Init();
}

CThread::~CThread(void)
{
	CloseHandle(m_hEvent);
	CloseHandle(m_handle);
}

CThread::CThread(CTask * pTask) :
m_pTask(pTask),
m_bRun(false)
{
	Init();
}

CThread::CThread(const char * ThreadName, CTask * pTask) :
m_pTask(pTask),
m_bRun(false)
{
	Init();
}



CThread::CThread(CBaseThreadPool* cbThreadPool) :
m_pThreadPool(cbThreadPool)
{
	Init();
}

void CThread::Init()
{
	m_handle = NULL;
	m_hEvent = CreateEvent(NULL, false, false, NULL);//创建信号事件，自动复原，初始状态为无信号,未命名
}


bool CThread::StartThread(bool bSuspend)
{
	if (m_bRun)
	{
		return true;
	}
	if (bSuspend)
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 0, StaticThreadFunc, this, CREATE_SUSPENDED, &m_ThreadID);
	}
	else
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 0, StaticThreadFunc, this, 0, &m_ThreadID);
	}
	m_bRun = (NULL != m_handle);
	return m_bRun;
}


BOOL CThread::GetThreadCurrentRunState()
{
	return m_bRun;
}

void CThread::taskProc()
{
	if (!m_bRun)
	{
		return;
	}
	if (NULL != m_pTask)
	{
		m_pTask->taskProc();
	}
	m_bRun = false;
}

void CThread::Join(int timeout)
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	if (timeout <= 0)
	{
		timeout = INFINITE;
	}
	::WaitForSingleObject(m_handle, timeout);
}

void CThread::Resume()
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	::ResumeThread(m_handle);
}

void CThread::Suspend()
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	::SuspendThread(m_handle);
}

bool CThread::Terminate(unsigned long ExitCode)
{
	if (NULL == m_handle || !m_bRun)
	{
		return true;
	}
	if (::TerminateThread(m_handle, ExitCode))
	{
		::CloseHandle(m_handle);
		return true;
	}
	return false;
}

unsigned int CThread::GetThreadID()
{
	return m_ThreadID;
}







void CThread::SetThreadPriority(int ThreadPriority)
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	::SetThreadPriority(m_handle,ThreadPriority);

}

unsigned int CThread::StaticThreadFunc(void * arg)
{
	CThread *pThread = (CThread*)arg;
	while (pThread->m_bRun)
	{
		DWORD ret = WaitForSingleObject(pThread->m_hEvent, INFINITE);
		if (ret == WAIT_OBJECT_0)
		{
			if (pThread->m_pTask)
			{
				pThread->m_pTask->taskProc(); 
				delete pThread->m_pTask;
				pThread->m_pTask = NULL;
				pThread->m_pThreadPool->SwitchActiveThread(pThread);
			}
		}
	}
	return 0;
}



bool CThread::assignTask(CTask* pTask)
{
	m_pTask = pTask;
	return true;
}


bool CThread::startTask()
{
	return SetEvent(m_hEvent);	
}

