// Thread.cpp: implementation of the CThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringGridctrl.h"

#include "TCDModule.h"
#include"stdafx.h"

//---------------------------------------------------------------------------
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTCD::CTCD(std::string portName)
{
    this->SetPortName(portName);
    MyTCDPort.BaudRate = 9600;
   // ���ַ��������10ms�����ж�
    MyTCDPort.TimeOuts.ReadIntervalTimeout =10;
   // ��ȡ�ܹ��ȴ���ʱ�䲻����300ms���ȴ�ʱ�䲻�ܽ��յ����ݴ�С��Ӱ��
    MyTCDPort.TimeOuts.ReadTotalTimeoutConstant = 300;
    MyTCDPort.TimeOuts.ReadTotalTimeoutMultiplier = 0;
    MyTCDPort.TimeOuts.WriteTotalTimeoutConstant = 1000;
    MyTCDPort.TimeOuts.WriteTotalTimeoutMultiplier = 1;
}
CTCD::~CTCD()
{
    this->Close();
}

void CTCD::SetPortName(std::string portName)
{
    MyTCDPort.Port = portName;
}

bool CTCD::Open()
{
    return MyTCDPort.Open();
}

void CTCD::Close()
{
    if ( MyTCDPort.IsConnected() )
        MyTCDPort.Close();
}



int CTCD::SendData(const void * pData, int length)
{
    if ( false == MyTCDPort.IsConnected() )
    {
        MessageBox(0 ,"��δ���Ӷ˿ڣ�","���棺",MB_OK);
        return 0;
    }
    return MyTCDPort.Write(pData ,length);
}

int CTCD::ReceiveData(void* pDataOut,int WantLength)
{
    if ( false == MyTCDPort.IsConnected() )
    {
        MessageBox(0 ,"��δ���Ӷ˿ڣ�","���棺",MB_OK);
        return 0;
    }
    return MyTCDPort.Read(pDataOut , WantLength);
}

void CTCD::ClearBuffer(bool input, bool output)
{
    MyTCDPort.ClearBuffer(input,output);
}

BYTE CTCD::CalCheckSum(void* pData ,int Length)
{
	unsigned char *pchar = (unsigned char *)pData;
    unsigned char tem=0;
    for (int i=0;i < Length;i++)
    {
    	tem = tem ^ pchar[i];
    }
	return tem;
}

DWORD CTCD::CheckFrame(void* pData ,int Length)
{
	unsigned char *pchar = (unsigned char *)pData;
    if (Length <=0) return RTCD_FRAMEEMPTY;
	if (8 != Length) return RTCD_FRAMEERR;
    if (0X02!= pchar[0]) return RTCD_FRAMEERR;
    if (0x53 != pchar[1]) return RTCD_FRAMEERR;
    if (0x46 != pchar[2]) return RTCD_FRAMEERR;
    if (0x03 != pchar[6]) return RTCD_FRAMEERR;

    unsigned char tem;
    tem = CalCheckSum(pchar,7);

    if (tem != pchar[7]) return RTCD_FRAMEERR;
    else return RTCD_OK;
}

#define	ACK		0x06
#define	NAK		0x15
#define	ENQ		0x05
DWORD CTCD::CMD_SendCMD(DWORD cmdCode ,int MaxRetry)
{
	DWORD retCode = 0xFFFFFFFF;
    BYTE sendData[5]={0x02,0,0,0x03,0};
    sendData[1] = (cmdCode>>8) & 0xFF;
    sendData[2] = cmdCode & 0xFF;
    sendData[4] = this->CalCheckSum(sendData,4);
	BYTE dataENQ = ENQ;
    BYTE receiveData[10];
    int receiveLength;
	for (int i=0; i < MaxRetry ;i++)
    {
    	this->ClearBuffer(true,true);
        this->SendData(sendData,5);
        receiveLength = this->ReceiveData(receiveData,1);
        if (0 == receiveLength)
        {
        	retCode = RTCD_TIMEOUT;
            continue;
        }
        switch (receiveData[0])
        {
        case ACK://���������ȷ����ִ��
        	//���ʼִ������
        	this->SendData(&dataENQ,1);
            retCode	= RTCD_OK;
            return retCode;
        case NAK://���������ȷ��������ִ��
        	//����ִ������
            retCode	= RTCD_NAK;
            return retCode;
        default:
        	//�޷�ʶ�����Ϣ
            retCode	= RTCD_ACKERROR;
            Sleep(10);//�ӳ�һ��ʱ���ٳ���
            break;
        }
    }

    return retCode;
}

DWORD CTCD::CMD_PayOut(int MaxRetry)
{
    return this->CMD_SendCMD(0x4443,MaxRetry);
}

DWORD CTCD::CMD_CallBack(int MaxRetry)
{
    return this->CMD_SendCMD(0x4350,MaxRetry);
}

DWORD CTCD::CMD_GetStatus(DWORD &statusCode ,int MaxRetry)
{
	statusCode = 0xFFFFFFFF;
	DWORD retCode = 0xFFFFFFFF;
    BYTE receiveData[10];
    int receiveLength;
	for (int i=0; i < MaxRetry ;i++)
    {
    	retCode = this->CMD_SendCMD(0x5246,1);
        if (RTCD_OK != retCode)continue;

        receiveLength = this->ReceiveData(receiveData,8);
        retCode = this->CheckFrame(receiveData ,receiveLength);
        //���δ�յ���Ч��״̬��Ϣ���������
        if (RTCD_OK != retCode)continue;
        //�յ���Ч��״̬��Ϣ�󷵻�״̬���벢����ѭ��
        statusCode = 0;
        for (int i=0;i < 3;i++)
        {
        	statusCode = (statusCode<<8) | BYTE(receiveData[i+3]-'0');
        }
        return RTCD_OK;
    }

    return retCode;

}

DWORD CTCD::CMD_Reset(int MaxRetry)
{
    return this->CMD_SendCMD(0x5354,MaxRetry);
}

