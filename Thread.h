// Thread.h: interface for the CThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREAD_H__F70E8C35_EE3A_48C2_9524_A17A0F765B68__INCLUDED_)
#define AFX_THREAD_H__F70E8C35_EE3A_48C2_9524_A17A0F765B68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "TCDModule.h"	// Added by ClassView
#include "askcsc.h"

class CThread  
{
public:
	static CString m_windowname;
	static CString readerPortName;
	//static CString TCDPortName;
	static int readWrite();
	static bool connectReader(CString str);
	static void TaskResult();
	static void ResumeTask();
	static void PauseTask();
	static void CancelTask();
	static BOOL GetTask();
	static int AddTask(int addTaskCount);
	static bool bPause;
	static int TaskCount;
	BOOL Stop();
	static DWORD WINAPI ThreadProc( LPVOID lpParam);
    static CString ByteCString(void *lpData, int Length);

	 BOOL Start();
	 CThread();
	virtual ~CThread();
    static BOOL exitCode;
private:
	
	HANDLE hThread;
};
// 

#endif // !defined(AFX_THREAD_H__F70E8C35_EE3A_48C2_9524_A17A0F765B68__INCLUDED_)
