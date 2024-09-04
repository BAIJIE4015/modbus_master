#ifndef MODBUS_MASTER_H
#define MODBUS_MASTER_H

//#include "modbus_master_global.h"
#include <iostream>
#include <iomanip>
#include <sstream>

#include <string.h>
#include <stdio.h>
#include "ModbusMasterInterface.h"


class MODBUS_MASTER_EXPORT Modbus_master:public modbus_masterInterface
{
public:
    Modbus_master(Modbus_Communication *pCommunication,
                  _CommunicationType nModel,
                  int nSlaveAddress,
                  bool bHIBeHind);
    //DO离散输出寄存器
    virtual bool Modbus_Read_01(WORD nStartAddressIndex,WORD nSize);
    //DI离散输入寄存器
    virtual bool Modbus_Read_02(WORD nStartAddressIndex,WORD nSize);
    //HR保持寄存器
    virtual bool Modbus_Read_03(WORD nStartAddressIndex,WORD nSize);
    //AR输入寄存器
    virtual bool Modbus_Read_04(WORD nStartAddressIndex,WORD nSize);
    //07号命令（读不正常状态）
    virtual bool Modbus_Read_07();
    //诊断
    virtual bool Modbus_Read_08(WORD nStartAddressIndex,WORD nData);
    //通讯事件计数器
    virtual bool Modbus_Read_0B();
    //通讯事件计数器
    virtual bool Modbus_Read_0C();
    //通讯事件记录
    virtual bool Modbus_Read_0D();
    //扩展寄存器//0x14 //读取输入寄存器
    virtual bool Modbus_Read_14(WORD nFileId);
    //FIFO
    virtual bool Modbus_Read_18(WORD nStartAddressIndex,WORD nSize);
    //true( ON ff00) false( OFF 0000)
    virtual bool Modbus_Write_05(WORD nStartAddressIndex,bool bStatus = false);
    virtual bool Modbus_Write_06(WORD nStartAddressIndex,WORD nData);

    virtual bool Modbus_Write_0F(WORD nStartAddressIndex,WORD nSize,std::vector<BYTE> vecData);
    virtual bool Modbus_Write_10(WORD nStartAddressIndex,WORD nSize,std::vector<WORD> vecData);

    virtual bool Modbus_AnalyzeMessage(BYTE *pData,int nLength,
                                       BYTE &nFunc,std::vector<BYTE> &vecData);

private:
    bool Send(BYTE*lpData,int nLength);
    bool JonitReadBuffer(BYTE* lpData,int &nLength,WORD nFunc,WORD nStartAddressIndex,WORD nSize);
    bool SendData(BYTE*lpData,int nLength);
    BYTE GetLRC(BYTE*lpData,int nLength);
    WORD GetCRC(BYTE*lpData,int nLength);

    void ASCIItoRTU(char* chResponse,int &nResponLen);
    std::string RTUtoASCII(const char* rtuResponse, int rtuLength);
    bool OnParseResponseRTU(BYTE* chResponse, int nResponLen,BYTE &nFunc,std::vector<BYTE> &vecData);
private:
    int m_nModel;
    int m_nDevAddress;
    bool m_bHIBeHind;
    WORD m_wTCP_Task;
    Modbus_Communication *m_pCommunication;
};

#endif // MODBUS_MASTER_H
