#include "stdafx.h"
#include "TaskQueue.h"


CTaskQueue::CTaskQueue()
{
}


CTaskQueue::~CTaskQueue()
{
}


CTask* CTaskQueue::pop()
{
	m_mutex.Lock();
	CTask* task=m_TaskQueue.front();
	m_TaskQueue.pop_front();
	m_mutex.UnLock();
	return task;
}
bool CTaskQueue::push(CTask* task)
{
	m_mutex.Lock();
	m_TaskQueue.push_back(task);
	m_mutex.UnLock();
	return true;

}
bool CTaskQueue::pushFront(CTask* task)
{
	m_mutex.Lock();
	m_TaskQueue.push_front(task);
	m_mutex.UnLock();
	return true;
}
bool CTaskQueue::isEmpty()
{
	return m_TaskQueue.empty();
}
bool CTaskQueue::clear()
{
	m_mutex.Lock();
	m_TaskQueue.clear();
	m_mutex.UnLock();
	return true;
}