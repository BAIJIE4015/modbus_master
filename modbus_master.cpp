#include "modbus_master.h"
MODBUS_MASTER_EXPORT modbus_masterInterface* createUaInterface(Modbus_Communication *pCommunication,
                                                               _CommunicationType nModel,
                                                               int nSlaveAddress,
                                                               bool bLittle_Endian)
{
    return new Modbus_master(pCommunication,nModel,nSlaveAddress,bLittle_Endian);
}
MODBUS_MASTER_EXPORT void deleteUaInterface(modbus_masterInterface* pInterface)
{
    delete pInterface;
}
Modbus_master::Modbus_master(Modbus_Communication *pCommunication,
                             _CommunicationType nModel,
                             int nSlaveAddress,
                             bool bHIBeHind):m_nModel(nModel),
    m_nDevAddress(nSlaveAddress),
    m_bHIBeHind(bHIBeHind),
    m_pCommunication(pCommunication)

{
    m_wTCP_Task = 1;
}
bool Modbus_master::Modbus_Read_01(WORD  nStartAddressIndex,WORD nSize)
{
    BYTE szBuffer[64] = {0};
    int nLength = 0;
    JonitReadBuffer(szBuffer,nLength,0x01,nStartAddressIndex,nSize);
    bool bIsSend = SendData(szBuffer,nLength);
    return bIsSend;
}
bool Modbus_master::Modbus_Read_02(WORD nStartAddressIndex,WORD nSize)
{
    BYTE szBuffer[64] = {0};
    int nLength = 0;
    JonitReadBuffer(szBuffer,nLength,0x02,nStartAddressIndex,nSize);
    bool bIsSend = SendData(szBuffer,nLength);
    return bIsSend;
}
bool Modbus_master::Modbus_Read_03(WORD nStartAddressIndex,WORD nSize)
{
    BYTE szBuffer[64] = {0};
    int nLength = 0;
    JonitReadBuffer(szBuffer,nLength,0x03,nStartAddressIndex,nSize);
    bool bIsSend = SendData(szBuffer,nLength);
    return bIsSend;
}
bool Modbus_master::Modbus_Read_04(WORD nStartAddressIndex,WORD nSize)
{
    BYTE szBuffer[64] = {0};
    int nLength = 0;
    JonitReadBuffer(szBuffer,nLength,0x04,nStartAddressIndex,nSize);
    bool bIsSend = SendData(szBuffer,nLength);
    return bIsSend;
}
bool Modbus_master::Modbus_Read_07()
{
    BYTE szBuffer[64] = {0};
    int nLength = 0;
    szBuffer[nLength++] = m_nDevAddress;
    szBuffer[nLength++] = 0x07;
    bool bIsSend = SendData(szBuffer,nLength);
    return bIsSend;
}

bool Modbus_master::Modbus_Read_08(WORD nStartAddressIndex,WORD nData)
{
    BYTE szBuffer[64] = {0};
    int nLength = 0;
    JonitReadBuffer(szBuffer,nLength,0x08,nStartAddressIndex,nData);
    bool bIsSend = SendData(szBuffer,nLength);
    return bIsSend;
}

bool Modbus_master::Modbus_Read_0B()
{
    BYTE szBuffer[64] = {0};
    int nLength = 0;
    szBuffer[nLength++] = m_nDevAddress;
    szBuffer[nLength++] = 0x0b;
    bool bIsSend = SendData(szBuffer,nLength);
    return bIsSend;
}

bool Modbus_master::Modbus_Read_0C()
{
    BYTE szBuffer[64] = {0};
    int nLength = 0;
    szBuffer[nLength++] = m_nDevAddress;
    szBuffer[nLength++] = 0x0c;
    bool bIsSend = SendData(szBuffer,nLength);
    return bIsSend;
}

bool Modbus_master::Modbus_Read_0D()
{
    BYTE szBuffer[64] = {0};
    int nLength = 0;
    szBuffer[nLength++] = m_nDevAddress;
    szBuffer[nLength++] = 0x0d;
    bool bIsSend = SendData(szBuffer,nLength);
    return bIsSend;
}

bool Modbus_master::Modbus_Read_14(WORD nFileId)
{
    //14 07 06 00 01 00 02 00 02
    BYTE szBuffer[64] = {0};
    int nLength = 0;
    szBuffer[nLength++] = m_nDevAddress;
    szBuffer[nLength++] = 0x14;
    szBuffer[nLength++] = 0x07;//字节计数
    szBuffer[nLength++] = 0x06;//引用类型
    if(m_bHIBeHind)
    {
        szBuffer[nLength++] = LOBYTE(nFileId);
        szBuffer[nLength++] = HIBYTE(nFileId);

    }else
    {
        szBuffer[nLength++] = HIBYTE(nFileId);
        szBuffer[nLength++] = LOBYTE(nFileId);
    }
    bool bIsSend = SendData(szBuffer,nLength);
    return bIsSend;
}

bool Modbus_master::Modbus_Read_18(WORD nStartAddressIndex,WORD nSize)
{
    BYTE szBuffer[64] = {0};
    int nLength = 0;
    JonitReadBuffer(szBuffer,nLength,0x18,nStartAddressIndex,nSize);
    bool bIsSend = SendData(szBuffer,nLength);
    return bIsSend;
}
bool Modbus_master::Modbus_Write_05(WORD nStartAddressIndex,bool bStatus)
{
    BYTE lpData[64] = {0};
    int nLength = 0;
    lpData[nLength++] = m_nDevAddress;
    lpData[nLength++] = 05;
    if(m_bHIBeHind)
    {
        lpData[nLength++] = LOBYTE(nStartAddressIndex);
        lpData[nLength++] = HIBYTE(nStartAddressIndex);
        if(bStatus)
        {
            lpData[nLength++] = LOBYTE(0x00);
            lpData[nLength++] = HIBYTE(0xFF);
        }
        else
        {
            lpData[nLength++] = LOBYTE(0x00);
            lpData[nLength++] = HIBYTE(0x00);
        }
    }else
    {
        lpData[nLength++] = HIBYTE(nStartAddressIndex);
        lpData[nLength++] = LOBYTE(nStartAddressIndex);

        if(bStatus)
        {
            lpData[nLength++] = HIBYTE(0xFF);
            lpData[nLength++] = LOBYTE(0x00);
        }else
        {
            lpData[nLength++] = HIBYTE(0x00);
            lpData[nLength++] = LOBYTE(0x00);
        }
    }
    bool bIsSend = SendData(lpData,nLength);
    return bIsSend;
}
bool Modbus_master::Modbus_Write_06(WORD nStartAddressIndex,WORD nData)
{
    BYTE szBuffer[64] = {0};
    int nLength = 0;
    JonitReadBuffer(szBuffer,nLength,0x06,nStartAddressIndex,nData);
    bool bIsSend = SendData(szBuffer,nLength);
    return bIsSend;
}
bool Modbus_master::Modbus_Write_0F(WORD nStartAddressIndex,WORD nSize,std::vector<BYTE> vecData)
{
    BYTE lpData[64] = {0};
    int nLength = 0;
    lpData[nLength++] = m_nDevAddress;
    lpData[nLength++] = 0x0f;
    BYTE nByteSize = vecData.size();
    if(m_bHIBeHind)
    {
        lpData[nLength++] = LOBYTE(nStartAddressIndex);
        lpData[nLength++] = HIBYTE(nStartAddressIndex);

        lpData[nLength++] = LOBYTE(nSize);
        lpData[nLength++] = HIBYTE(nSize);
    }else
    {
        lpData[nLength++] = HIBYTE(nStartAddressIndex);
        lpData[nLength++] = LOBYTE(nStartAddressIndex);

        lpData[nLength++] = HIBYTE(nSize);
        lpData[nLength++] = LOBYTE(nSize);
    }
    lpData[nLength++] = nByteSize;
    for(int i = 0;i<nByteSize;i++)
    {
        lpData[nLength++] = vecData[i];
    }
    bool bIsSend = SendData(lpData,nLength);
    return bIsSend;
}
bool Modbus_master::Modbus_Write_10(WORD nStartAddressIndex,WORD nSize,std::vector<WORD> vecData)
{
    BYTE lpData[64] = {0};
    int nLength = 0;
    lpData[nLength++] = m_nDevAddress;
    lpData[nLength++] = 0x10;
    BYTE nByteSize = vecData.size();
    if(m_bHIBeHind)
    {
        lpData[nLength++] = LOBYTE(nStartAddressIndex);
        lpData[nLength++] = HIBYTE(nStartAddressIndex);

        lpData[nLength++] = LOBYTE(nSize);
        lpData[nLength++] = HIBYTE(nSize);
    }else
    {
        lpData[nLength++] = HIBYTE(nStartAddressIndex);
        lpData[nLength++] = LOBYTE(nStartAddressIndex);

        lpData[nLength++] = HIBYTE(nSize);
        lpData[nLength++] = LOBYTE(nSize);
    }
    lpData[nLength++] = nByteSize * 2;
    for(int i = 0;i<nByteSize;i++)
    {
        if(m_bHIBeHind)
        {
            lpData[nLength++] = LOBYTE(vecData[i]);
            lpData[nLength++] = HIBYTE(vecData[i]);
        }else
        {
            lpData[nLength++] = HIBYTE(vecData[i]);
            lpData[nLength++] = LOBYTE(vecData[i]);
        }
    }
    bool bIsSend = SendData(lpData,nLength);
    return bIsSend;
}
bool Modbus_master::JonitReadBuffer(BYTE* lpData,int &nLength,WORD nFunc,WORD nStartAddressIndex,WORD nSize)
{
    lpData[nLength++] = m_nDevAddress;
    lpData[nLength++] = nFunc;
    if(m_bHIBeHind)
    {
        lpData[nLength++] = LOBYTE(nStartAddressIndex);
        lpData[nLength++] = HIBYTE(nStartAddressIndex);

        lpData[nLength++] = LOBYTE(nSize);
        lpData[nLength++] = HIBYTE(nSize);
    }else
    {
        lpData[nLength++] = HIBYTE(nStartAddressIndex);
        lpData[nLength++] = LOBYTE(nStartAddressIndex);

        lpData[nLength++] = HIBYTE(nSize);
        lpData[nLength++] = LOBYTE(nSize);
    }
    return true;
}
bool Modbus_master::SendData(BYTE*lpData,int nLength)
{
    bool bRet = false;
    switch(m_nModel)
    {
        case _MODEL_ASCII:
        {
            std::string strBuffer = RTUtoASCII((char*)lpData,nLength);
            int nSize = strBuffer.length();
            char *szData = new char[nSize+10];
            memset(szData,0,nSize+10);
            memcpy(szData,strBuffer.c_str(),nSize);
            BYTE check = GetLRC((BYTE*)szData,nSize);
            szData[nSize++] = check;
            szData[nSize++] = 0x0d;
            szData[nSize++] = 0x0a;
            bRet = Send((BYTE*)szData,nLength);
            delete []szData;
        }
        break;
        case _MODEL_RTU:
        {
            WORD check = GetCRC(lpData,nLength);
            char *szData = new char[nLength+10];
            memset(szData,0,nLength+10);
            memcpy(szData,lpData,nLength);
            if(m_bHIBeHind)
            {
                szData[nLength++] = LOBYTE(check);
                szData[nLength++] = HIBYTE(check);
            }else
            {
                szData[nLength++] = HIBYTE(check);
                szData[nLength++] = LOBYTE(check);
            }
            bRet = Send((BYTE*)szData,nLength);
            delete []szData;
        }
            break;
        case _MODEL_TCP:
        {

            char *szData = new char[nLength+10];
            memset(szData,0,nLength+10);
            if(m_bHIBeHind)
            {
                szData[0] = LOBYTE(m_wTCP_Task);
                szData[1] = HIBYTE(m_wTCP_Task);
                szData[4] = LOBYTE(nLength);
                szData[5] = HIBYTE(nLength);
            }else
            {
                szData[0] = HIBYTE(m_wTCP_Task);
                szData[1] = LOBYTE(m_wTCP_Task);
                szData[4] = HIBYTE(nLength);
                szData[5] = LOBYTE(nLength);
            }
            m_wTCP_Task++;
            memcpy(szData+6,lpData,nLength);
            nLength += 6;
            bRet = Send((BYTE*)szData,nLength);
            delete []szData;
        }
        break;
    }
    return bRet;
}
bool Modbus_master::Send(BYTE*lpData,int nLength)
{
    if(m_pCommunication)
    {
        m_pCommunication->Send(lpData,nLength);
    }
    return true;
}
BYTE Modbus_master::GetLRC(BYTE*lpData,int nLength)
{
    BYTE bCheck = 0;
    int i;
    int nNum;
    char bufTemp[4];
    for(i = 1; i <= nLength; i+=2)
    {
        bufTemp[0] = lpData[i];
        bufTemp[1] = lpData[i+1];
        bufTemp[2] = '\0';
        sscanf(bufTemp,"%x",&nNum);
        bCheck+=nNum;
    }
    bCheck = ~bCheck;
    bCheck++;
    return bCheck;

}
WORD Modbus_master::GetCRC(BYTE*lpData,int nLength)
{
    WORD crc= (unsigned short)(0xffff);
    for(int i = 0; i <= nLength; i++)
    {
        crc^=(unsigned char)(BYTE(lpData[i]));
        for(int j = 0; j < 8; j++)
        {
            if(crc&1)
            {
                crc>>=1;
                crc^=0xA001;
            }
            else
                crc>>=1;
        }
    }
    return int(crc);
}
bool Modbus_master::Modbus_AnalyzeMessage(BYTE *pData,int nLength,
                                   BYTE &nFunc,std::vector<BYTE> &vecData)
{
    bool bRet = false;
    if(_MODEL_ASCII == m_nModel)
    {
        char* chTempData = new char[nLength + 50];
        memset(chTempData,0,nLength + 50);
        memcpy(chTempData, pData, nLength);
        ASCIItoRTU(chTempData,nLength);
        bRet = OnParseResponseRTU((BYTE*)chTempData,nLength,nFunc,vecData);
        delete []chTempData;
    }else
    {
        bRet = OnParseResponseRTU(pData,nLength,nFunc,vecData);
    }
    return bRet;
}
bool Modbus_master::OnParseResponseRTU(BYTE* chResponse, int nResponLen,BYTE &nFunc,std::vector<BYTE> &vecData)
{
    if(nResponLen < 5)
    {
        return false;
    }
    int nHead = -1;
    for(int i = 0;i<nResponLen;i++)
    {
        if(chResponse[i] == m_nDevAddress)
        {
            nHead = i;
        }
    }
    if(nHead == -1)
    {
        return false;
    }
    int nLength = nResponLen - nHead -3;
    BYTE *pData = chResponse;
    pData += nHead;
    nFunc = pData[1];
    switch(nFunc)
    {
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x14:
        {
            BYTE nByteCount = pData[2];
            if(nLength < nByteCount)
            {
                return false;
            }
            for(int i = 3;i < nByteCount;i++)
            {
                vecData.push_back(pData[i]);
            }
        }
        break;
        case 0x05:
        case 0x06:
        {
//            BYTE hiAddress = pData[2];
//            BYTE loAddress = pData[3];
//            BYTE hiValue = pData[4];
//            BYTE loValue = pData[5];
        }
        break;
        case 0x0B:
        {
    //            BYTE histatus = pData[2];
    //            BYTE lostatus = pData[3];
    //            BYTE hievent = pData[4];
    //            BYTE loevent = pData[5];
        }
        break;
        case 0x0C:
        {
            BYTE nByteCount = pData[2];
            if(nLength < nByteCount)
            {
                return false;
            }
            for(int i = 3;i < nByteCount;i++)
            {
                vecData.push_back(pData[i]);
            }
        }
        break;
        case 0x0F:
        case 0x10:
        {
        //            BYTE hiAddress = pData[2];
        //            BYTE loAddress = pData[3];
        //            BYTE hisize = pData[4];
        //            BYTE losize = pData[5];
        }
        break;
        case 0x18:
        {
            WORD nCount = MAKEWORD(pData[3],pData[2]);
            if(nLength < nCount)
            {
                return false;
            }
            for(int i = 3;i < nCount;i++)
            {
                vecData.push_back(pData[i]);
            }
        }
        break;
    }
    return true;
}
void Modbus_master::ASCIItoRTU(char* chResponse,int &nResponLen)
{
    BYTE bChar;
    for(int i=0;i<nResponLen/2;i++)
    {
        bChar = chResponse[1+(i<<1)] & 0x0F;
        if(chResponse[1+(i<<1)] > 0x40)
            bChar += 9;
        chResponse[i] = (bChar<<4);
        bChar = chResponse[2+(i<<1)] & 0x0F;
        if(chResponse[2+(i<<1)] > 0x40)
            bChar += 9;
        chResponse[i] |= bChar;
    }
    nResponLen = (nResponLen -3) / 2;
    //nResponLen = (nResponLen -3)/2+1;
}
std::string Modbus_master::RTUtoASCII(const char* rtuResponse, int rtuLength)
{
    std::stringstream asciiStream;
    asciiStream << ':';
    for (int i = 0; i < rtuLength; ++i)
    {
        asciiStream << std::setw(2) << std::setfill('0') << std::hex << (unsigned int)rtuResponse[i];
    }
    //asciiStream << '\r' << '\n';
    return asciiStream.str();
}
