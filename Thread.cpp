// Thread.cpp: implementation of the CThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringGridctrl.h"
#include "Thread.h"
#include "StringGridctrlDlg.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BOOL CThread::exitCode=false;
int CThread::TaskCount=0;
bool CThread::bPause=false;
//CString CThread::TCDPortName="COM1";
CString CThread::readerPortName="COM3";
CString CThread::m_windowname="";

//HANDLE m_hMutex = CreateMutex(NULL, FALSE, NULL);
CRITICAL_SECTION m_cs;

CStringArray  array;

DWORD ret;
BYTE COM;
DWORD atrLength;
BYTE atr[20];
DWORD search_mask;
sCARD_SearchExt SearchExt;

CThread::CThread()
{
    hThread=NULL;
  
   InitializeCriticalSection(&m_cs);
    	
}

CThread::~CThread()
{
    if(hThread!=NULL)
	{
		
		CloseHandle(hThread);
		hThread=NULL;
		
	}
	if(exitCode!=false)
	{
		
		this->Stop();
	}
    DeleteCriticalSection(&m_cs);
}

BOOL CThread::Start()
{
    
   
	EnterCriticalSection(&m_cs);

	CThread::exitCode=false; 
	hThread=CreateThread(NULL,0,ThreadProc,NULL,0,NULL);
    LeaveCriticalSection(&m_cs);
    return hThread!=NULL;

}

DWORD WINAPI CThread::ThreadProc(LPVOID lpParam)
{  
    
	//std::string strport=TCDPortName;

   HWND hWnd = AfxGetMainWnd()->m_hWnd;
   CString strReadPort=readerPortName;
   if(false==connectReader(strReadPort))
   {
      std::string str="无法打开读卡器端口";
      MessageBox(hWnd,str.c_str(),m_windowname,MB_OK|MB_APPLMODAL|MB_ICONWARNING);
       //tcd.Close();
	  PostMessage(hWnd,WM_USERMESSAGE,0,0); 
      return -1; 
   }
     while(!exitCode)
    {
	  
     	if((false==GetTask())||(true==bPause))
        {
            Sleep(300);
            continue;
        }
        if(0==readWrite())
		{
           TaskResult();
		}
//
	    Sleep(200);   
	 }
	
     CSC_Close();
    //PostMessage(hWnd,WM_USERMESSAGE,0,0);
  
  return 0;
}

BOOL CThread::Stop()
{
	//WaitForSingleObject(m_hMutex,INFINITE);
    EnterCriticalSection(&m_cs);
    if(hThread!=NULL)
	{
       exitCode=true;
	   //Sleep(200);
       //ReleaseMutex(m_hMutex);
	   CloseHandle(hThread);
	   LeaveCriticalSection(&m_cs);
	   return true;
	}
	//ReleaseMutex(m_hMutex);
	LeaveCriticalSection(&m_cs);
    return FALSE;
}

int CThread::AddTask(int addTaskCount)
{
	// WaitForSingleObject(m_hMutex,INFINITE);
    EnterCriticalSection(&m_cs);
     TaskCount+=addTaskCount;
    // ReleaseMutex(m_hMutex);
	 LeaveCriticalSection(&m_cs);
	 return TaskCount;
}

BOOL CThread::GetTask()
{
     //WaitForSingleObject(m_hMutex,INFINITE);
	EnterCriticalSection(&m_cs);
     if(bPause==true||TaskCount<=0)
     {
        // ReleaseMutex(m_hMutex);
		 LeaveCriticalSection(&m_cs);
		 return false;
	 }
     //ReleaseMutex(m_hMutex);
	 LeaveCriticalSection(&m_cs);
	 return true;

}

void CThread::PauseTask()
{
     //WaitForSingleObject(m_hMutex,INFINITE);
	EnterCriticalSection(&m_cs);
	 bPause=true;
	 //ReleaseMutex(m_hMutex);
	 LeaveCriticalSection(&m_cs);
}

void CThread::ResumeTask()
{
    // WaitForSingleObject(m_hMutex,INFINITE); 
	EnterCriticalSection(&m_cs);
     bPause=false;
    // ReleaseMutex(m_hMutex);
	 LeaveCriticalSection(&m_cs);
}

void CThread::TaskResult()
{
  //WaitForSingleObject(m_hMutex,INFINITE); 
	EnterCriticalSection(&m_cs);
	if(TaskCount>0)
	{
       TaskCount--;
	}
	
 // ReleaseMutex(m_hMutex);
    LeaveCriticalSection(&m_cs);
}
void CThread::CancelTask()
{
    EnterCriticalSection(&m_cs);
    CThread::TaskCount=0;
    LeaveCriticalSection(&m_cs);
}
bool CThread::connectReader(CString str)
{
    //WaitForSingleObject(m_hMutex,INFINITE);
     SearchExt.CONT=0x00;
     SearchExt.ISOB=0x02;
     SearchExt.ISOA=0x01;
     SearchExt.TICK=0x00;
     SearchExt.INNO=0x00;
     SearchExt.MIFARE=0x03;
     SearchExt.MV4k=0x00;
     SearchExt.MV5k=0x00;
     SearchExt.MONO=0x00;
     search_mask=SEARCH_MASK_ISOA;
     HWND hWnd = AfxGetMainWnd()->m_hWnd;
	 char * port=new char[10];
	 memcpy(port,str,10);
	 if(RCSC_Ok!=CSC_Open(port))
		{
            
			return false;
		}
        CSC_ResetCSC();
		delete  port;
  // ReleaseMutex(m_hMutex);

	 return true;
}

int CThread::readWrite()
{
    //WaitForSingleObject(m_hMutex,INFINITE);
     HWND hWnd = AfxGetMainWnd()->m_hWnd;
     ret=CSC_SearchCardExt(&SearchExt,search_mask,0x01,0x44,&COM,&atrLength,atr);
	 if(ret!=RCSC_Ok)
	{
        //ReleaseMutex(m_hMutex);
		return -1;
	}
     if(ret!=RCSC_Ok||0x08!=COM)
	{
       CSC_Switch_Led_Buz(CSC_CPU_LED1);
	   //ReleaseMutex(m_hMutex);
	   return 1;
	}
	 ////////////////////////////////////////////////////
	BYTE Result[20];//改为字符数组
	for (int i = 0;i < 7;i++)
	{
	  	Result[i] = atr[i + 2];
	}
	

    CString str=ByteCString(Result,7);
	CString s;
	for(int j=0;j<array.GetSize();j++)
	{
	 if(str==array.GetAt(j))
	 {
		//Sleep(100);
        SendMessage(hWnd,WM_SHOWNOTE,0,0);//////////////////////////////////
		return 2;//记录已经存在
	 }
	}
	//Sleep(200);
	 ////////////////////////////////////////////////////////
	BYTE status;
	BYTE dataRead[4];
	BYTE dataToWrite[4]={0x66,0x00,0x00,0x00};

	ret=CTx512x_Write(12,4,dataToWrite,dataRead,&status);///ctx512x_write 有问题
	//if(ret!=RCSC_Ok||memcmp(dataRead,dataToWrite,4))
	//{
		//MessageBox(hWnd,"------","错误!!!!!!",MB_OK|MB_APPLMODAL|MB_ICONWARNING);
		//Sleep(2000);
       // ret=CTx512x_Write(12,4,dataToWrite,dataRead,&status);//写函数执行2次
	//}
   
    if(ret!=RCSC_Ok||memcmp(dataRead,dataToWrite,4))
	{ 
         
         MessageBox(hWnd,"------OTP初始化没写成功。------","错误!!!!!!",MB_OK|MB_APPLMODAL|MB_ICONWARNING);
		 return 1;
	}	
	CSC_Switch_Led_Buz(CSC_CPU_LED1);
	BYTE otp[4];

	BYTE OTP[4]={0x66,0x00,0x00,0x00};
	ret=CTx512x_Read(12,4,otp,&status);

   

	if(ret!=RCSC_Ok||memcmp(otp,OTP,4))
	{
       // ReleaseMutex(m_hMutex);
		MessageBox(hWnd,"------OTP验证不通过，请放到回收盒。------","警告!!!!!!",MB_OK|MB_APPLMODAL|MB_ICONWARNING);
        return 1;
	}

	
	if(RCSC_Ok!=CSC_CardEnd())
	{
		MessageBox(hWnd,"------读卡器与卡片连接关闭失败。------","警告!!!!!!",MB_OK|MB_APPLMODAL|MB_ICONWARNING);
        //MessageBox("读卡器与卡片连接关闭失败!");
	}
   // BYTE* Result = new BYTE[20];
	memcpy(&Result[7], otp, 4);//6
	Sleep(100);
    SendMessage(hWnd,WM_SHOWDATA,(unsigned int)Result,0);
    CSC_Switch_Led_Buz(CSC_CPU_LED1|CSC_CPU_LED2|CSC_CPU_LED3);
	Sleep(50);
    CSC_Switch_Led_Buz(CSC_CPU_LED1);
    //MessageBox(0,str,str,MB_OK);
	array.Add(str);
	return 0;

}


CString CThread::ByteCString(void *lpData, int Length)
{
    BYTE *lpByte=(BYTE *)lpData;
	CString str="";
	const char hexCode[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(int i=0;i<Length;i++)
	{
        str=str+hexCode[(*lpByte)>>4];
		str=str+hexCode[(*lpByte)&0x0F];
		lpByte++;
	}

	return str;
}
