// Thread.h: interface for the CThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCDModuleH_H__F70E8C35_EE3A_48C2_9524_A17A0F765B68__INCLUDED_)
#define AFX_CDModuleH_H__F70E8C35_EE3A_48C2_9524_A17A0F765B68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <vector>
#include <string>
#include "MyComPort.h"



class CTCD  
{

public:
	CTCD(std::string portName= "COM1");
	virtual ~CTCD();
	bool Open(); 	//�����ӵĶ˿�
    void Close();   //�ر����ӵĶ˿�
public://�������Ӷ˿����ԣ�����֮ǰ�������÷�����Ч��
    void SetPortName(std::string portName);  //�������Ӷ˿ڵ�����
public://�ײ�ͨѶ�շ�����
	//��ָ����С�����ݴӶ˿ڷ��ͳ�ȥ
    int SendData(const void * pData, int length);	//�����ӵĶ˿ڷ�������
    int ReceiveData(void* pDataOut,int WantLength);	//�����ӵĶ˿ڽ���ָ�����ȵ����ݣ�����ʵ�ʽ��յ����ݳ���
    void ClearBuffer(bool input, bool output);		//���������
    BYTE CalCheckSum(void* pData ,int Length);		//����У��ͣ������ֽڰ�λ���
    DWORD CheckFrame(void* pData ,int Length);		//���һ֡�����Ƿ�Ϸ�
	DWORD CMD_SendCMD(DWORD cmdCode ,int MaxRetry = 2);	//���ͷ������������ӡ�����������ʹ�ã���������ʧ�ܺ�ೢ�Լ���
public://TCD API
	DWORD CMD_PayOut(int MaxRetry = 2); 			//�������ʹ��Ԥ������ģʽʱ��Ҫ�ȷ��͸���������ڶ���λ�ã�Ȼ���ٷ��͸������³���
	DWORD CMD_CallBack(int MaxRetry = 2);			//���տ�Ƭ
    DWORD CMD_GetStatus(DWORD &statusCode ,int MaxRetry = 2);	//��ȡ������״̬�����������״̬��

	DWORD CMD_Reset(int MaxRetry = 2);	//���������λ

private:
	CMyComPort MyTCDPort;
};
#define RTCD_OK			0  	//������������
#define RTCD_NAK		1   //�������ܾ���������
#define RTCD_FRAMEERR	2   //�����������Ľ������������һ�����ص����ݳ���
#define RTCD_FRAMEEMPTY	3   //�������������������Ӧ�����ؽ�һ��������޷���
#define RTCD_ACKERROR	4 	//������������һ�������������ִ���
#define RTCD_TIMEOUT	5   //��������ʱδ���������ź�

//���������ص�״̬��
#define TCDSC_PAYOUTING		0x080000	//���ڷ�����
#define TCDSC_CALLBACKING	0x040000	//���ڻ��տ�Ƭ
#define TCDSC_PAYERROR		0x020000    //����ʧ��
#define TCDSC_BACKDEPOTFULL	0x010000    //���ղ���
#define TCDSC_UNKNOW1		0x000800
#define TCDSC_UNKNOW2		0x000400
#define TCDSC_JAM			0x000200    //��Ƭ����
#define TCDSC_DEPOTLOW		0x000100    //�����ֿ�Ƭ��
#define TCDSC_DEPOTEMPTY	0x000008    //�����ֿ�
#define TCDSC_WAITPICK		0x000004    //�ȴ�ȡ�����������ʽ��
#define TCDSC_WAITREAD		0x000002    //��Ƭ�ѵ�������λ�ã��ȴ���������
#define TCDSC_PRENOTREADY	0x000001    //��Ƭ��δ�ӷ������͵�����ͷ
#define TCDSC_READY			0x000000    //��Ƭ�Ѵӷ������͵�����ͷ




#endif // !defined(AFX_THREAD_H__F70E8C35_EE3A_48C2_9524_A17A0F765B68__INCLUDED_)





