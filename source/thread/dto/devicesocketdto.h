#ifndef DEVICESOCKETDTO_H
#define DEVICESOCKETDTO_H

#include <QObject>
#pragma pack(push, 1)
struct StPacket{
    char mSeq;
    int  mDeviceNum;
    int  mFuncCode;
    int  mSize;
    char mData[0];
};

struct StPacketRSyncInitRes{
    StPacket mHeader;
    quint64 mTotalByte;
};

struct StPacketRStatusRes{
    StPacket mHeader            ;
    bool     mIsRun             ;
    bool     mIsComm            ;
    bool     mIsAlarm           ;
    quint16  mProductNo         ;
    char     mProductName[50]   ;
    quint16  mMdSignal          ;
    quint16  mWcEventType       ;
    quint32  mCurrWeight        ;

    quint32  mMdSenstivity      ;
    quint32  mTareWeight        ;
    quint32  mUnderWeight       ;
    quint32  mUnderWaringWeight ;
    quint32  mNormalWeight      ;
    quint32  mOverWaringWeight  ;
    quint32  mOverWeight        ;

    int      mMDNgCnt           ;
    int      mWCUnderCnt        ;
    int      mWCUnderWaringCnt  ;
    int      mWCNoramlCnt       ;
    int      mWCOverWaringCnt   ;
    int      mWCOverCnt         ;
    int      mWCEtcErrCnt       ;
    int      mmWCEtcMDErrCnt    ;

    quint64  mTradeTotalWeight  ;
};

#pragma pack(pop)
#endif // DEVICESOCKETDTO_H
