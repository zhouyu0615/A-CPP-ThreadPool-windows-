#pragma once
class CTask
{
public:
	CTask(int id):m_id(id){};
	CTask(void){};
	virtual ~CTask() {};
	virtual void taskProc() = 0;

	void SetTaskId(int id){ m_id = id; };
	int  GetTaskId() { return m_id; };
private:
	int m_id;
};
