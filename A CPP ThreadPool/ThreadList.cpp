#include "stdafx.h"
#include "ThreadList.h"


CThreadList::CThreadList()
{
}


CThreadList::~CThreadList()
{
}

bool CThreadList::addThread(CThread* thread)
{
	m_mutex.Lock();
	m_list.push_back(thread);
	m_mutex.UnLock();
	return true;
}
bool CThreadList::removeThread(CThread* thread)
{
	m_mutex.Lock();
	m_list.remove(thread);
	m_mutex.UnLock();
	return true;
}
int CThreadList::getSize()
{
	return m_list.size();
}
bool CThreadList::isEmpty()
{
	return m_list.empty();
}
bool CThreadList::clear()
{
	m_mutex.Lock();
	m_list.clear();
	m_mutex.UnLock();
	return true;
}

