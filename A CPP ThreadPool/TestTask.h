#pragma once
#include "Task.h"

class CTestTask:public CTask
{
public:
	CTestTask(int id);
	~CTestTask();

	void SetTimeInterval(int timeMs);
	virtual void taskProc();
private:
	int timeMs;;
};

