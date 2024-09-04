#ifndef MODBUSMASTERINTERFACE_H
#define MODBUSMASTERINTERFACE_H
#include <vector>
#define MODBUS_MASTER_SHARED
#define MODBUS_MASTER_EXPORTS
#ifdef _WINDOWS
    #ifdef MODBUS_MASTER_EXPORTS
    #  define MODBUS_MASTER_EXPORT __declspec(dllexport)
    #else
    #  define MODBUS_MASTER_EXPORT __declspec(dllimport)
    #endif
#else
    #    define Q_DECL_EXPORT     __attribute__((visibility("default")))
    #    define Q_DECL_IMPORT     __attribute__((visibility("default")))
    #    define Q_DECL_HIDDEN     __attribute__((visibility("hidden")))
    #ifdef MODBUS_MASTER_SHARED
        #ifdef MODBUS_MASTER_EXPORTS
        #    define MODBUS_MASTER_EXPORT Q_DECL_EXPORT
        #else
        #    define MODBUS_MASTER_EXPORT Q_DECL_IMPORT
        #endif
    #else
        #  define MODBUS_MASTER_EXPORT
    #endif

#endif
enum _CommunicationType{
    _MODEL_ASCII,
    _MODEL_RTU,
    _MODEL_TCP,
};
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))

class Modbus_Communication{
public:
    virtual ~Modbus_Communication() = default;
    virtual bool Send(unsigned char* lpData,int nLength) = 0;
    virtual bool OnReceive(unsigned char* lpData,int nLength) = 0;
};

class modbus_masterInterface{
public:
    virtual ~modbus_masterInterface() = default;
    virtual bool Modbus_Read_01(WORD nStartAddressIndex,WORD nSize) = 0;
    //DI离散输入寄存器
    virtual bool Modbus_Read_02(WORD nStartAddressIndex,WORD nSize) = 0;
    //HR保持寄存器
    virtual bool Modbus_Read_03(WORD nStartAddressIndex,WORD nSize) = 0;
    //AR输入寄存器
    virtual bool Modbus_Read_04(WORD nStartAddressIndex,WORD nSize) = 0;
    //07号命令（读不正常状态）
    virtual bool Modbus_Read_07() = 0;
    //诊断
    virtual bool Modbus_Read_08(WORD nStartAddressIndex,WORD nData) = 0;
    //通讯事件计数器
    virtual bool Modbus_Read_0B() = 0;
    //通讯事件计数器
    virtual bool Modbus_Read_0C() = 0;
    //通讯事件记录
    virtual bool Modbus_Read_0D() = 0;
    //扩展寄存器//0x14 //读取输入寄存器
    virtual bool Modbus_Read_14(WORD nFileId) = 0;
    //FIFO
    virtual bool Modbus_Read_18(WORD nStartAddressIndex,WORD nSize) = 0;
    //true( ON ff00) false( OFF 0000)
    virtual bool Modbus_Write_05(WORD nStartAddressIndex,bool bStatus = false) = 0;
    virtual bool Modbus_Write_06(WORD nStartAddressIndex,WORD nData) = 0;

    virtual bool Modbus_Write_0F(WORD nStartAddressIndex,WORD nSize,std::vector<BYTE> vecData) = 0;
    virtual bool Modbus_Write_10(WORD nStartAddressIndex,WORD nSize,std::vector<WORD> vecData) = 0;

    virtual bool Modbus_AnalyzeMessage(BYTE *pData,int nLength,
                                       BYTE &nFunc,std::vector<BYTE> &vecData) = 0;


};

extern "C"
{
   MODBUS_MASTER_EXPORT modbus_masterInterface* createUaInterface(Modbus_Communication *pCommunication,
                                                                  _CommunicationType nModel,
                                                                  int nSlaveAddress,
                                                                  bool bLittle_Endian);
   MODBUS_MASTER_EXPORT void deleteUaInterface(modbus_masterInterface* pInterface);
}
#endif // MODBUSMASTERINTERFACE_H
