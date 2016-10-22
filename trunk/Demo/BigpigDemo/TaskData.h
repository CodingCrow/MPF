#pragma once

#include "UIHelp.h"
#include <string>

//��������
enum eTaskType
{
	TaskType_None = 0,
	TaskType_1,
	TaskType_2,
	TaskType_3,
	TaskType_4,
	TaskType_5,
	TaskType_6,
	TaskType_7,
	TaskType_8
};

//����״̬
enum eTaskState
{
	TaskState_Home = 0,			//��ʼ״̬
	TaskState_Running,			//����ִ��
	TaskState_Waiting,			//�ȴ�����ȷ��
	TaskState_Input,			//������ɣ�������Ϣ
	TaskState_Finish,			//��д��Ϣ���
	TaskState_Error				//ʧ����
};

//Info1
#define INFO1_SAMSUNG "Samsung"
#define INFO1_APPLE "Apple"
#define INFO1_HUAWEI "Huawei"

//Info3
#define INFO3_Android "Android"
#define INFO3_Ios "IOS"
#define INFO3_WM "wm"


class CListboxItemData : public NotifyPropChanged
{
public:
	BeginMember(CListboxItemData, NotifyPropChanged)
		MemberInt(ID)
		MemberInt(TaskType)
		MemberInt(TaskState)
		MemberInt(Percent)
		MemberString(Info1)
		MemberString(Info2)
		MemberString(Info3)
		MemberString(OwnerType)
		MemberString(OwnerName)
		MemberString(OwnerNum)
		MemberString(OwnerPhone)
		MemberInt(EventCode)
		MemberString(EventStr)
		MemberString(EventMore)
		MemberInt(ErrCode)
		MemberString(ErrStr)
	EndMember()

	CListboxItemData()
	{
		_TaskType = TaskType_None;
		_TaskState = TaskState_Home;
		_Percent = 0;
		_OwnerType = "01";
	}
	~CListboxItemData()
	{
	}

	void Reset()
	{
		SetOwnerType("01");
		SetOwnerName("");
		SetOwnerNum("");
		SetOwnerPhone("");
		SetEventCode(0);
		SetEventStr("");
		SetErrCode(0);
		SetErrStr("");
		SetEventMore("");
	}

	DeclarInt(ID)			//�ֻ�ID
	DeclarInt(TaskType)		//�������� eTaskType
	DeclarInt(TaskState)	//����״̬ eTaskState
	DeclarInt(Percent)		//�������
	DeclarString(Info1)		//չʾ��Ϣ
	DeclarString(Info2)		//չʾ��Ϣ
	DeclarString(Info3)		//չʾ��Ϣ
	DeclarString(OwnerType)	//����������
	DeclarString(OwnerName) //����������
	DeclarString(OwnerNum)	//������֤������
	DeclarString(OwnerPhone)//�����ֻ���
	DeclarInt(EventCode)	//������ʾ
	DeclarString(EventStr)	//������ʾ
	DeclarString(EventMore) //������ϸ��ʾ
	DeclarInt(ErrCode)		//������Ϣ
	DeclarString(ErrStr)	//������Ϣ

};

struct CTaskData
{
	int				m_nID;
	std::string		m_strInfo1;
	std::string		m_strInfo2;
	std::string		m_strInfo3;
	int				m_eventType;
	std::string		m_eventStr;
	std::string		m_eventMore;
	int				m_errCode;
	std::string		m_errStr;
	int				m_total;
	int				m_get;

	CTaskData()
		:m_nID(0)
		,m_eventType(0)
		,m_errCode(0)
		,m_get(-1)
		,m_total(-1)
	{
	}
};