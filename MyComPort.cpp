// Thread.cpp: implementation of the CThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringGridctrl.h"

//---------------------------------------------------------------------------
#include "MyComPort.h"
#include <assert.h>
#include <ctype.h>
#include <WINSPOOL.H>

//---------------------------------------------------------------------------

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyComPort::CMyComPort(std::string PortName,DWORD dwBaudRate)
{
    this->Port = PortName;
    this->BaudRate = dwBaudRate;
    this->InputBufferSize = 4096;
    this->OutputBufferSize = 4096;
    this->Parity = NOPARITY;
    this->StopBits = ONESTOPBIT;
    this->ByteSize = 8;
    TimeOuts.ReadIntervalTimeout = 100;
    TimeOuts.ReadTotalTimeoutMultiplier = 0;
    TimeOuts.ReadTotalTimeoutConstant = 20000;
    TimeOuts.WriteTotalTimeoutConstant = 0;
    TimeOuts.WriteTotalTimeoutMultiplier = 0;
    hComm = NULL;
}

bool CMyComPort::Open()
{
    if (IsConnected()) this->Close();
    std::string portName = "\\\\.\\" + Port;
    hComm = CreateFile(portName.c_str(),GENERIC_READ | GENERIC_WRITE,
                            0, NULL, OPEN_EXISTING, 0, 0);
    if (hComm == INVALID_HANDLE_VALUE)// The Port does not opened success.
    {
        hComm = NULL;
        return false ;
    }
    if (!UpdateCommPara())//set the baudrate ,parity ,stopbits go into effect
    {
        CloseHandle(hComm);
        hComm = NULL;
        return false;
    }
    if (!UpdateBufferSize())//set buffer sizes go into effect
    {
        CloseHandle(hComm);
        hComm = NULL;
        return false;
    }
    if (!UpdateTimeoutsPara())//set timeouts parameter go into effect
    {
        CloseHandle(hComm);
        hComm = NULL;
        return false;
    }
    return true;
}



bool CMyComPort::UpdateCommPara()
{
	//if the connection hasn't set up ,return faile directly.
	if (!IsConnected())return false;
    DCB dcb;
    assert(GetCommState(hComm ,&dcb));
    dcb.BaudRate = this->BaudRate;
    dcb.Parity = this->Parity;
    dcb.StopBits = this->StopBits;
    dcb.ByteSize = this->ByteSize;
    if (!SetCommState(hComm ,&dcb))
        return false;
    return true;
}

bool CMyComPort::UpdateBufferSize()
{
	//if the connection hasn't set up ,return faile directly.
	if (!IsConnected())return false;
    if (!SetupComm(hComm ,InputBufferSize ,OutputBufferSize))
        return false;
    return true;
}

bool CMyComPort::UpdateTimeoutsPara()
{
	//if the connection hasn't set up ,return faile directly.
	if (!IsConnected())return false;
    if (!SetCommTimeouts(hComm, &TimeOuts))
        return false;
    return true;
}

bool CMyComPort::IsConnected()
{
    return (NULL != hComm);
}

void CMyComPort::Close()
{
    if (NULL != hComm)
    {
        CloseHandle(hComm);
        hComm = NULL;
    }
}

CMyComPort::~CMyComPort()
{
    if (this->IsConnected()) this->Close();
}

int CMyComPort::Read(void * lpBufferOut, DWORD Length)
{
	if (!this->IsConnected()) return -1;
    DWORD lengthOut = 0;
    ReadFile(hComm,lpBufferOut,Length,&lengthOut,NULL);
    return lengthOut;
}

int CMyComPort::Write(const void * lpBufferIn, DWORD Length)
{
	if (!this->IsConnected()) return -1;
    DWORD lengthOut = 0;
    WriteFile(hComm,lpBufferIn,Length,&lengthOut,NULL);
    return lengthOut;
}

int CMyComPort::ClearBuffer(bool InputBuffer, bool OutBuffer)
{
    if (!this->IsConnected()) return -1;
    DWORD flags  = 0;
    if (InputBuffer) flags |= (PURGE_RXCLEAR|PURGE_RXABORT);
    if (OutBuffer) flags |= (PURGE_TXCLEAR|PURGE_TXABORT);
    PurgeComm(hComm ,flags);
    return 0;
}
bool CMyComPort::UpdataSetCommMask()
{
   if(!IsConnected()) return false;
   if(!SetCommMask(hComm,EV_CTS))
      return false;
   return true;
}
bool CMyComPort::UpdataWaitCommEvent()
{
   if(!IsConnected()) return false;
   DWORD dwEvtMask;
   if(!WaitCommEvent(hComm,&dwEvtMask,0))   return false;
   if(dwEvtMask!=EV_CTS)   return false;
      return true;
}
bool CMyComPort::UpdataEscapeCommSET()
{
  if(!IsConnected()) return false;
  if(!EscapeCommFunction(hComm,SETRTS))
     return false;
  return true;
}
bool CMyComPort::UpdataEscapeCommCLR()
{
   if(!IsConnected()) return false;
   if(!EscapeCommFunction(hComm,CLRRTS))
     return false;
   return true;

}
bool CMyComPort::UpdataSetCommRetset()
{
 
  if(!IsConnected()) return false;
  if(!EscapeCommFunction(hComm,0))
     return false;
  return true;

}
bool CMyComPort::UpdataGetCommModemStat()
{
  if(!IsConnected()) return false;
  DWORD ModemStat;
  GetCommModemStatus(hComm,&ModemStat);
  if(ModemStat!=MS_CTS_ON)
     return  false ;
  return true;

}
