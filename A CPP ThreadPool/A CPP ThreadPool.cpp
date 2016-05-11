// A CPP ThreadPool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MyThreadPool.h"
#include "TestTask.h"




int _tmain(int argc, _TCHAR* argv[])
{
	CMyThreadPool thPool(5);
	thPool.start();

	CTestTask* pTask=new CTestTask(1);
	pTask->SetTimeInterval(300);
	thPool.addTask(pTask, PRIORITY::NORMAL);

	CTestTask* pTask2 = new CTestTask(2);
	pTask2->SetTimeInterval(500);
	thPool.addTask(pTask2, PRIORITY::NORMAL);

	CTestTask* pTask3 = new CTestTask(3);
	pTask3->SetTimeInterval(800);
	thPool.addTask(pTask3, PRIORITY::NORMAL);

	
	getchar();
	return 0;
}

