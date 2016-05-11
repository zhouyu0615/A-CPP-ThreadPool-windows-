#include "stdafx.h"
#include "TestTask.h"
#include <iostream>
#include <windows.h>


CTestTask::CTestTask(int id) :CTask(id)
{
	timeMs = 0;
}


CTestTask::~CTestTask()
{
}

void CTestTask::SetTimeInterval(int timeMs)
{
	this->timeMs = timeMs;
}

void CTestTask::taskProc()
{

	for (int i = 1; i < 100000;i++)
	{
		std::cout << "Thread id=" << GetTaskId() << "第"<<i<<"次运行" << std::endl;
		Sleep(timeMs);
	}
	
}
