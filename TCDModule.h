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
	bool Open(); 	//打开连接的端口
    void Close();   //关闭连接的端口
public://设置连接端口属性（连接之前进行设置方能生效）
    void SetPortName(std::string portName);  //设置连接端口的名称
public://底层通讯收发操作
	//将指定大小的数据从端口发送出去
    int SendData(const void * pData, int length);	//向连接的端口发送数据
    int ReceiveData(void* pDataOut,int WantLength);	//从连接的端口接收指定长度的数据，返回实际接收的数据长度
    void ClearBuffer(bool input, bool output);		//清除缓存器
    BYTE CalCheckSum(void* pData ,int Length);		//计算校验和（所有字节按位异或）
    DWORD CheckFrame(void* pData ,int Length);		//检查一帧数据是否合法
	DWORD CMD_SendCMD(DWORD cmdCode ,int MaxRetry = 2);	//发送发卡机命令，供添加、测试新命令使用，可以命令失败后多尝试几次
public://TCD API
	DWORD CMD_PayOut(int MaxRetry = 2); 			//发卡命令，使用预读发卡模式时需要先发送该命令将卡置于读卡位置，然后再发送该命令吐出卡
	DWORD CMD_CallBack(int MaxRetry = 2);			//回收卡片
    DWORD CMD_GetStatus(DWORD &statusCode ,int MaxRetry = 2);	//获取发卡机状态，详见发卡机状态码

	DWORD CMD_Reset(int MaxRetry = 2);	//命令发卡机复位

private:
	CMyComPort MyTCDPort;
};
#define RTCD_OK			0  	//命令正常发送
#define RTCD_NAK		1   //发卡机拒绝接收命令
#define RTCD_FRAMEERR	2   //发卡机正常的接收了命令，但进一步返回的数据出错
#define RTCD_FRAMEEMPTY	3   //发卡机正常接收了命令，应当返回进一步结果但无返回
#define RTCD_ACKERROR	4 	//发卡机返回了一个不正常的握手代码
#define RTCD_TIMEOUT	5   //发卡机超时未返回握手信号

//发卡机返回的状态码
#define TCDSC_PAYOUTING		0x080000	//正在发卡中
#define TCDSC_CALLBACKING	0x040000	//正在回收卡片
#define TCDSC_PAYERROR		0x020000    //发卡失败
#define TCDSC_BACKDEPOTFULL	0x010000    //回收仓满
#define TCDSC_UNKNOW1		0x000800
#define TCDSC_UNKNOW2		0x000400
#define TCDSC_JAM			0x000200    //卡片堵塞
#define TCDSC_DEPOTLOW		0x000100    //发卡仓卡片少
#define TCDSC_DEPOTEMPTY	0x000008    //发卡仓空
#define TCDSC_WAITPICK		0x000004    //等待取卡（半出卡方式）
#define TCDSC_WAITREAD		0x000002    //卡片已到读卡器位置，等待读卡操作
#define TCDSC_PRENOTREADY	0x000001    //卡片尚未从发卡仓送到导轨头
#define TCDSC_READY			0x000000    //卡片已从发卡仓送到导轨头




#endif // !defined(AFX_THREAD_H__F70E8C35_EE3A_48C2_9524_A17A0F765B68__INCLUDED_)





