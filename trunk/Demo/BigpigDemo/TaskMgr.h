#pragma once
#include "TaskData.h"
#include <map>

using namespace std;

class CTaskMgr
{
public:
	static CTaskMgr* GetInstance();
	~CTaskMgr(void);

	void Init();

	int AddTask(CTaskData* pData);

	void RunTask(int nID,int nType);

	void CancelTask(int nID);

	void RemoveTask(int nID);

	void ClickOK(int nID);

private:
	CTaskMgr(void);

	// �߳�����listbox������
	static DWORD WINAPI CreatTaskThread(LPVOID lpParameter);

	// �߳���ɾlistbox��ʱ����
	static DWORD WINAPI RemoveTaskThread(LPVOID lpParameter);

	// �߳�ִ������
	static DWORD WINAPI RunTaskThread(LPVOID lpParameter);

	struct CTaskInfo
	{
		int				m_nID;
		int				m_nType;	//1:���� 2:����ʾ 3:�����
		bool			m_bRun;
		bool			m_bCancel;
		CTaskInfo()
			:m_nID(0)
			,m_nType(0)
			,m_bRun(false)
			,m_bCancel(false)
		{}
	};
	map<int,CTaskInfo*>		m_mapTaskInfos;
};

