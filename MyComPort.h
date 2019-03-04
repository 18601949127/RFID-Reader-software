// MyComPort.h: interface for the CMyComPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MyComPortH_H__F70E8C35_EE3A_48C2_9524_A17A0F765B68__INCLUDED_)
#define AFX_MyComPortH_H__F70E8C35_EE3A_48C2_9524_A17A0F765B68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <windows.h>
#include <vector>

class CMyComPort  
{
public:
    CMyComPort(std::string PortName="COM1"  ,DWORD dwBaudRate=9600);
    virtual ~CMyComPort();
public:
    std::string Port;
    DWORD BaudRate;
    DWORD InputBufferSize;
    DWORD OutputBufferSize;
    COMMTIMEOUTS TimeOuts;
    BYTE ByteSize;
    BYTE Parity;
    BYTE StopBits;
public:
    
    bool Open();
    void Close();
    bool IsConnected();
    int Write(const void * lpBufferIn, DWORD Length);
    int ClearBuffer(bool InputBuffer, bool OutBuffer);
    int Read(void * lpBufferOut, DWORD Length);
public:
    bool UpdateCommPara();
    bool UpdateBufferSize();
    bool UpdateTimeoutsPara();
    bool UpdataSetCommMask();
    bool UpdataWaitCommEvent();
    bool UpdataEscapeCommSET();
    bool UpdataEscapeCommCLR();
    bool UpdataSetCommRetset();
    bool UpdataGetCommModemStat();
protected:
    HANDLE hComm;

};


#endif // !defined(AFX_THREAD_H__F70E8C35_EE3A_48C2_9524_A17A0F765B68__INCLUDED_)
