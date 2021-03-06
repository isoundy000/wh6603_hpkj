#ifndef WH_THREAD_HEAD_FILE
#define WH_THREAD_HEAD_FILE

#pragma once

#include "ServiceCoreHead.h"

//////////////////////////////////////////////////////////////////////////

//资源锁定
class SERVICE_CORE_CLASS CWHThreadLock
{
	//变量定义
private:
	INT								m_nLockCount;					//锁定计数
	CCriticalSection &				m_CriticalSection;				//锁定对象

	//函数定义
public:
	//构造函数
	CWHThreadLock(CCriticalSection & CriticalSection, bool bLockAtOnce=true);
	//析构函数
	virtual ~CWHThreadLock();

	//操作函数
public:
	//锁定函数
	VOID Lock();
	//解锁函数 
	VOID UnLock();

	//状态函数
public:
	//锁定次数
	inline INT GetLockCount() { return m_nLockCount; }
};

//////////////////////////////////////////////////////////////////////////////////

//线程对象
class SERVICE_CORE_CLASS CWHThread
{
	//状态变量
private:
	volatile bool					m_bRun;								//运行标志

	//线程变量
private:
	UINT							m_uThreadID;						//线程标识
	HANDLE							m_hThreadHandle;					//线程句柄

	//函数定义
protected:
	//构造函数
	CWHThread();
	//析构函数
	virtual ~CWHThread();

	//接口函数
public:
	//获取状态
	virtual bool IsRuning();
	//启动线程
	virtual bool StartThread();
	//终止线程
	virtual bool ConcludeThread(DWORD dwMillSeconds);

	//功能函数
public:
	//线程标识
	UINT GetThreadID() { return m_uThreadID; }
	//线程句柄
	HANDLE GetThreadHandle() { return m_hThreadHandle; }
	//投递消息
	LRESULT PostThreadMessage(UINT uMessage, WPARAM wParam, LPARAM lParam);

	//事件函数
protected:
	//运行事件
	virtual bool OnEventThreadRun() { return true; }
	//开始事件
	virtual bool OnEventThreadStrat() { return true; }
	//终止事件
	virtual bool OnEventThreadConclude() { return true; }

	//内部函数
private:
	//线程函数
	static unsigned __stdcall ThreadFunction(LPVOID pThreadData);
};

//////////////////////////////////////////////////////////////////////////////////

#endif