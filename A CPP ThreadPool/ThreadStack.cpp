#include "stdafx.h"
#include "ThreadStack.h"


CThreadStack::CThreadStack()
{
}


CThreadStack::~CThreadStack()
{
}


bool CThreadStack::isEmpty()
{
	return m_ThreadStack.empty();
}


bool CThreadStack::clear()
{
	m_mutex.Lock();
	while (!m_ThreadStack.empty())
	{
		CThread* thread = m_ThreadStack.top();
		m_ThreadStack.pop();
		delete thread;
	}
	m_mutex.UnLock();
	return true;
}
int CThreadStack::getSize()
{
	return m_ThreadStack.size();
}
bool CThreadStack::push(CThread* thread)
{
	m_mutex.Lock();
	m_ThreadStack.push(thread);
	m_mutex.UnLock();
	return true;
}
CThread* CThreadStack::pop()
{
	m_mutex.Lock();
	CThread* thread = m_ThreadStack.top();
	m_ThreadStack.pop();
	m_mutex.UnLock();
	return  thread;
}
