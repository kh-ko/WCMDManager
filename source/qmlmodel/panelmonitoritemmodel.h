#ifndef PANELMONITORITEMMODEL_H
#define PANELMONITORITEMMODEL_H

#include <QObject>
#include <QDebug>
#include <QUdpSocket>

#include "source/remote/strpacket.h"
#include "source/remote/dto/enum/remoteenumdef.h"
#include "source/service/coreservice.h"

class PanelMonitorItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsDetail            READ getIsDetail            NOTIFY signalEventChangedIsDetail           );
    Q_PROPERTY(int     mConnectState        READ getConnectState        NOTIFY signalEventChangedConnectState       );
    Q_PROPERTY(bool    mIsRun               READ getIsRun               NOTIFY signalEventChangedIsRun              );
    Q_PROPERTY(bool    mIsComm              READ getIsComm              NOTIFY signalEventChangedIsComm             );
    Q_PROPERTY(bool    mIsAlarm             READ getIsAlarm             NOTIFY signalEventChangedIsAlarm            );
    Q_PROPERTY(int     mDeviceNum           READ getDeviceNum           NOTIFY signalEventChangedDeviceNum          );
    Q_PROPERTY(QString mDeviceName          READ getDeviceName          NOTIFY signalEventChangedDeviceName         );
    Q_PROPERTY(quint16 mProductNo           READ getProductNo           NOTIFY signalEventChangedProductNo          );
    Q_PROPERTY(QString mProductName         READ getProductName         NOTIFY signalEventChangedProductName        );
    Q_PROPERTY(quint16 mMdSignal            READ getMdSignal            NOTIFY signalEventChangedMdSignal           );
    Q_PROPERTY(quint16 mWcEventType         READ getWcEventType         NOTIFY signalEventChangedWcEventType        );
    Q_PROPERTY(quint32 mCurrWeight          READ getCurrWeight          NOTIFY signalEventChangedCurrWeight         );
    Q_PROPERTY(quint32 mMdSenstivity        READ getMdSenstivity        NOTIFY signalEventChangedMdSenstivity       );
    Q_PROPERTY(quint32 mTareWeight          READ getTareWeight          NOTIFY signalEventChangedTareWeight         );
    Q_PROPERTY(quint32 mUnderWeight         READ getUnderWeight         NOTIFY signalEventChangedUnderWeight        );
    Q_PROPERTY(quint32 mUnderWaringWeight   READ getUnderWaringWeight   NOTIFY signalEventChangedUnderWaringWeight  );
    Q_PROPERTY(quint32 mNormalWeight        READ getNormalWeight        NOTIFY signalEventChangedNormalWeight       );
    Q_PROPERTY(quint32 mOverWaringWeight    READ getOverWaringWeight    NOTIFY signalEventChangedOverWaringWeight   );
    Q_PROPERTY(quint32 mOverWeight          READ getOverWeight          NOTIFY signalEventChangedOverWeight         );
    Q_PROPERTY(int     mMDNgCnt             READ getMDNgCnt             NOTIFY signalEventChangedMDNgCnt            );
    Q_PROPERTY(int     mWCUnderNGCnt        READ getWCUnderNGCnt        NOTIFY signalEventChangedWCUnderNGCnt       );
    Q_PROPERTY(int     mWCUnderWaringNGCnt  READ getWCUnderWaringNGCnt  NOTIFY signalEventChangedWCUnderWaringNGCnt );
    Q_PROPERTY(int     mWCNoramlCnt         READ getWCNoramlCnt         NOTIFY signalEventChangedWCNoramlCnt        );
    Q_PROPERTY(int     mWCOverWaringCnt     READ getWCOverWaringCnt     NOTIFY signalEventChangedWCOverWaringCnt    );
    Q_PROPERTY(int     mWCOverCnt           READ getWCOverCnt           NOTIFY signalEventChangedWCOverCnt          );
    Q_PROPERTY(int     mWCEtcErrCnt         READ getWCEtcErrCnt         NOTIFY signalEventChangedWCEtcErrCnt        );
    Q_PROPERTY(int     mWCEtcMDErrCnt       READ getWCEtcMDErrCnt       NOTIFY signalEventChangedWCEtcMDErrCnt      );
    Q_PROPERTY(int     mWCNGCnt             READ getWCNGCnt             NOTIFY signalEventChangedWCNGCnt            );
    Q_PROPERTY(int     mTotalcnt            READ getTotalcnt            NOTIFY signalEventChangedTotalcnt           );
    Q_PROPERTY(quint64 mTradeTotalWeight    READ getTradeTotalWeight    NOTIFY signalEventChangedTradeTotalWeight   );

public:
    CoreService *  mpCoreService;
    QString        mIp   ="";
    QHostAddress   mHostAddr;
    QUdpSocket *   mpSock = nullptr;
    int            mSentChecker = 0;

    bool           mIsDetail            = false;
    int            mConnectState        = EnumDefine::ConnectState::CONN_STATE_DISCONNECT;
    bool           mIsRun               = false;
    bool           mIsComm              = false;
    bool           mIsAlarm             = false;
    int            mDeviceNum           = 0;
    QString        mDeviceName          = "";
    quint16        mProductNo           = 0;
    QString        mProductName         = "";
    quint16        mMdSignal            = 0;
    quint16        mWcEventType         = EnumDefine::EVENT_TYPE_WEIGHT_NORMAL;
    quint32        mCurrWeight          = 0;
    quint32        mMdSenstivity        = 0;
    quint32        mTareWeight          = 0;
    quint32        mUnderWeight         = 0;
    quint32        mUnderWaringWeight   = 0;
    quint32        mNormalWeight        = 0;
    quint32        mOverWaringWeight    = 0;
    quint32        mOverWeight          = 0;
    int            mMDNgCnt             = 0;
    int            mWCUnderNGCnt        = 0;
    int            mWCUnderWaringNGCnt  = 0;
    int            mWCNoramlCnt         = 0;
    int            mWCOverWaringCnt     = 0;
    int            mWCOverCnt           = 0;
    int            mWCEtcErrCnt         = 0;
    int            mWCEtcMDErrCnt       = 0;
    int            mWCNGCnt             = 0;
    int            mTotalcnt            = 0;
    quint64        mTradeTotalWeight    = 0;

    bool    getIsDetail           (){ return mIsDetail           ; }
    int     getConnectState       (){ return mConnectState       ; }
    bool    getIsRun              (){ return mIsRun              ; }
    bool    getIsComm             (){ return mIsComm             ; }
    bool    getIsAlarm            (){ return mIsAlarm            ; }
    int     getDeviceNum          (){ return mDeviceNum          ; }
    QString getDeviceName         (){ return mDeviceName         ; }
    quint16 getProductNo          (){ return mProductNo          ; }
    QString getProductName        (){ return mProductName        ; }
    quint16 getMdSignal           (){ return mMdSignal           ; }
    quint16 getWcEventType        (){ return mWcEventType        ; }
    quint32 getCurrWeight         (){ return mCurrWeight         ; }
    quint32 getMdSenstivity       (){ return mMdSenstivity       ; }
    quint32 getTareWeight         (){ return mTareWeight         ; }
    quint32 getUnderWeight        (){ return mUnderWeight        ; }
    quint32 getUnderWaringWeight  (){ return mUnderWaringWeight  ; }
    quint32 getNormalWeight       (){ return mNormalWeight       ; }
    quint32 getOverWaringWeight   (){ return mOverWaringWeight   ; }
    quint32 getOverWeight         (){ return mOverWeight         ; }
    int     getMDNgCnt            (){ return mMDNgCnt            ; }
    int     getWCUnderNGCnt       (){ return mWCUnderNGCnt       ; }
    int     getWCUnderWaringNGCnt (){ return mWCUnderWaringNGCnt ; }
    int     getWCNoramlCnt        (){ return mWCNoramlCnt        ; }
    int     getWCOverWaringCnt    (){ return mWCOverWaringCnt    ; }
    int     getWCOverCnt          (){ return mWCOverCnt          ; }
    int     getWCEtcErrCnt        (){ return mWCEtcErrCnt        ; }
    int     getWCEtcMDErrCnt      (){ return mWCEtcMDErrCnt      ; }
    int     getWCNGCnt            (){ return mWCNGCnt            ; }
    int     getTotalcnt           (){ return mTotalcnt           ; }
    quint64 getTradeTotalWeight   (){ return mTradeTotalWeight   ; }

    void setIsDetail           (bool    value){ if(mIsDetail            == value) return; mIsDetail            = value; emit signalEventChangedIsDetail           (mIsDetail           );}
    void setConnectState       (int     value){ if(mConnectState        == value) return; mConnectState        = value; emit signalEventChangedConnectState       (mConnectState       );}
    void setIsRun              (bool    value){ if(mIsRun               == value) return; mIsRun               = value; emit signalEventChangedIsRun              (mIsRun              );}
    void setIsComm             (bool    value){ if(mIsComm              == value) return; mIsComm              = value; emit signalEventChangedIsComm             (mIsComm             );}
    void setIsAlarm            (bool    value){ if(mIsAlarm             == value) return; mIsAlarm             = value; emit signalEventChangedIsAlarm            (mIsAlarm            );}
    void setDeviceNum          (int     value){ if(mDeviceNum           == value) return; mDeviceNum           = value; emit signalEventChangedDeviceNum          (mDeviceNum          );}
    void setDeviceName         (QString value){ if(mDeviceName          == value) return; mDeviceName          = value; emit signalEventChangedDeviceName         (mDeviceName         );}
    void setProductNo          (quint16 value){ if(mProductNo           == value) return; mProductNo           = value; emit signalEventChangedProductNo          (mProductNo          );}
    void setProductName        (QString value){ if(mProductName         == value) return; mProductName         = value; emit signalEventChangedProductName        (mProductName        );}
    void setMdSignal           (quint16 value){ if(mMdSignal            == value) return; mMdSignal            = value; emit signalEventChangedMdSignal           (mMdSignal           );}
    void setWcEventType        (quint16 value){ if(mWcEventType         == value) return; mWcEventType         = value; emit signalEventChangedWcEventType        (mWcEventType        );}
    void setCurrWeight         (quint32 value){ if(mCurrWeight          == value) return; mCurrWeight          = value; emit signalEventChangedCurrWeight         (mCurrWeight         );}
    void setMdSenstivity       (quint32 value){ if(mMdSenstivity        == value) return; mMdSenstivity        = value; emit signalEventChangedMdSenstivity       (mMdSenstivity       );}
    void setTareWeight         (quint32 value){ if(mTareWeight          == value) return; mTareWeight          = value; emit signalEventChangedTareWeight         (mTareWeight         );}
    void setUnderWeight        (quint32 value){ if(mUnderWeight         == value) return; mUnderWeight         = value; emit signalEventChangedUnderWeight        (mUnderWeight        );}
    void setUnderWaringWeight  (quint32 value){ if(mUnderWaringWeight   == value) return; mUnderWaringWeight   = value; emit signalEventChangedUnderWaringWeight  (mUnderWaringWeight  );}
    void setNormalWeight       (quint32 value){ if(mNormalWeight        == value) return; mNormalWeight        = value; emit signalEventChangedNormalWeight       (mNormalWeight       );}
    void setOverWaringWeight   (quint32 value){ if(mOverWaringWeight    == value) return; mOverWaringWeight    = value; emit signalEventChangedOverWaringWeight   (mOverWaringWeight   );}
    void setOverWeight         (quint32 value){ if(mOverWeight          == value) return; mOverWeight          = value; emit signalEventChangedOverWeight         (mOverWeight         );}
    void setMDNgCnt            (int     value){ if(mMDNgCnt             == value) return; mMDNgCnt             = value; emit signalEventChangedMDNgCnt            (mMDNgCnt            );}
    void setWCUnderNGCnt       (int     value){ if(mWCUnderNGCnt        == value) return; mWCUnderNGCnt        = value; emit signalEventChangedWCUnderNGCnt       (mWCUnderNGCnt       );}
    void setWCUnderWaringNGCnt (int     value){ if(mWCUnderWaringNGCnt  == value) return; mWCUnderWaringNGCnt  = value; emit signalEventChangedWCUnderWaringNGCnt (mWCUnderWaringNGCnt );}
    void setWCNoramlCnt        (int     value){ if(mWCNoramlCnt         == value) return; mWCNoramlCnt         = value; emit signalEventChangedWCNoramlCnt        (mWCNoramlCnt        );}
    void setWCOverWaringCnt    (int     value){ if(mWCOverWaringCnt     == value) return; mWCOverWaringCnt     = value; emit signalEventChangedWCOverWaringCnt    (mWCOverWaringCnt    );}
    void setWCOverCnt          (int     value){ if(mWCOverCnt           == value) return; mWCOverCnt           = value; emit signalEventChangedWCOverCnt          (mWCOverCnt          );}
    void setWCEtcErrCnt        (int     value){ if(mWCEtcErrCnt         == value) return; mWCEtcErrCnt         = value; emit signalEventChangedWCEtcErrCnt        (mWCEtcErrCnt        );}
    void setWCEtcMDErrCnt      (int     value){ if(mWCEtcMDErrCnt       == value) return; mWCEtcMDErrCnt       = value; emit signalEventChangedWCEtcMDErrCnt      (mWCEtcMDErrCnt      );}
    void setWCNGCnt            (int     value){ if(mWCNGCnt             == value) return; mWCNGCnt             = value; emit signalEventChangedWCNGCnt            (mWCNGCnt            );}
    void setTotalcnt           (int     value){ if(mTotalcnt            == value) return; mTotalcnt            = value; emit signalEventChangedTotalcnt           (mTotalcnt           );}
    void setTradeTotalWeight   (quint64 value){ if(mTradeTotalWeight    == value) return; mTradeTotalWeight    = value; emit signalEventChangedTradeTotalWeight   (mTradeTotalWeight   );}

signals:
    void signalEventChangedIsDetail           (bool    value);
    void signalEventChangedConnectState       (int     value);
    void signalEventChangedIsRun              (bool    value);
    void signalEventChangedIsComm             (bool    value);
    void signalEventChangedIsAlarm            (bool    value);
    void signalEventChangedDeviceNum          (int     value);
    void signalEventChangedDeviceName         (QString value);
    void signalEventChangedProductNo          (quint16 value);
    void signalEventChangedProductName        (QString value);
    void signalEventChangedMdSignal           (quint16 value);
    void signalEventChangedWcEventType        (quint16 value);
    void signalEventChangedCurrWeight         (quint32 value);
    void signalEventChangedMdSenstivity       (quint32 value);
    void signalEventChangedTareWeight         (quint32 value);
    void signalEventChangedUnderWeight        (quint32 value);
    void signalEventChangedUnderWaringWeight  (quint32 value);
    void signalEventChangedNormalWeight       (quint32 value);
    void signalEventChangedOverWaringWeight   (quint32 value);
    void signalEventChangedOverWeight         (quint32 value);
    void signalEventChangedMDNgCnt            (int     value);
    void signalEventChangedWCUnderNGCnt       (int     value);
    void signalEventChangedWCUnderWaringNGCnt (int     value);
    void signalEventChangedWCNoramlCnt        (int     value);
    void signalEventChangedWCOverWaringCnt    (int     value);
    void signalEventChangedWCOverCnt          (int     value);
    void signalEventChangedWCEtcErrCnt        (int     value);
    void signalEventChangedWCEtcMDErrCnt      (int     value);
    void signalEventChangedWCNGCnt            (int     value);
    void signalEventChangedTotalcnt           (int     value);
    void signalEventChangedTradeTotalWeight   (quint64 value);

public slots:
    Q_INVOKABLE void onCommandToggleDetail()
    {
        setIsDetail(!getIsDetail());
    }
    void onSockError(QAbstractSocket::SocketError error)
    {
        qDebug() << "[PanelMonitorItemModel::onSockError] " << error;
        connectDevice();
    }
    void onReceive()
    {
        QByteArray rcvBuffer;
        QHostAddress sender;
        quint16 senderPort;
        StPacketRStatusRes *rPacketData;

        if(mpSock == nullptr)
        {
            qDebug() << "[PanelMonitorItemModel::onRecevie]sock is null";
            return;
        }

        if(mpSock->hasPendingDatagrams() == false)
        {
            return;
        }

        rcvBuffer.resize(mpSock->pendingDatagramSize());
        mpSock->readDatagram(rcvBuffer.data(), rcvBuffer.size(), &sender, &senderPort);
        rPacketData = (StPacketRStatusRes *)rcvBuffer.data();

        if(rcvBuffer.size() != (int)sizeof(StPacketRStatusRes))
        {
            qDebug() << "[PanelMonitorItemModel::onRecevie]packet error size";
            qDebug() << "[PanelMonitorItemModel::onRecevie]ERROR PACKET : "<< rcvBuffer.toHex();
            return;
        }

        if(rPacketData->mHeader.mFuncCode != EnumDefine::FuncCode::FUNC_CODE_MONITOR_STATUS)
        {
            qDebug() << "[PanelMonitorItemModel::onRecevie]packet funccode error";
            qDebug() << "[PanelMonitorItemModel::onRecevie]ERROR PACKET : "<< rcvBuffer.toHex();
            return;
        }

        mSentChecker = 0;
        setConnectState(EnumDefine::ConnectState::CONN_STATE_CONNECT);
        setIsRun              (rPacketData->mIsRun);
        setIsComm             (rPacketData->mIsComm);
        setIsAlarm            (rPacketData->mIsAlarm);
        setProductNo          (rPacketData->mProductNo);
        setProductName        (QString::fromUtf8(rPacketData->mProductName, 50));
        setMdSignal           (rPacketData->mMdSignal);
        setWcEventType        (rPacketData->mWcEventType);
        setCurrWeight         (rPacketData->mCurrWeight);
        setMdSenstivity       (rPacketData->mMdSenstivity);
        setTareWeight         (rPacketData->mTareWeight);
        setUnderWeight        (rPacketData->mUnderWaringWeight);
        setUnderWaringWeight  (rPacketData->mUnderWeight);
        setNormalWeight       (rPacketData->mNormalWeight);
        setOverWaringWeight   (rPacketData->mOverWaringWeight);
        setOverWeight         (rPacketData->mOverWeight);
        setMDNgCnt            (rPacketData->mMDNgCnt);
        setWCUnderNGCnt       (rPacketData->mWCUnderCnt);
        setWCUnderWaringNGCnt (rPacketData->mWCUnderWaringCnt);
        setWCNoramlCnt        (rPacketData->mWCNoramlCnt);
        setWCOverWaringCnt    (rPacketData->mWCOverWaringCnt);
        setWCOverCnt          (rPacketData->mWCOverCnt);
        setWCEtcErrCnt        (rPacketData->mWCEtcErrCnt);
        setWCEtcMDErrCnt      (rPacketData->mmWCEtcMDErrCnt);
        setWCNGCnt            (rPacketData->mWCUnderCnt + rPacketData->mWCOverCnt + rPacketData->mWCEtcErrCnt);
        setTotalcnt           (rPacketData->mWCUnderCnt + rPacketData->mWCOverCnt + rPacketData->mWCEtcErrCnt + rPacketData->mWCOverWaringCnt + rPacketData->mWCUnderWaringCnt + rPacketData->mWCNoramlCnt);
        setTradeTotalWeight   (rPacketData->mTradeTotalWeight);
    }
public:
    void reqRStatus()
    {
        if(mSentChecker == 0)
        {
            if(mpSock == nullptr)
            {
                connectDevice();
                return;
            }

            StRPacket packet;

            packet.mFuncCode = RemoteEnumDef::RFUNC_CODE_MONITOR_STATUS;
            packet.mSize     = 0;

            mpSock->writeDatagram((char *)&packet, sizeof(StRPacket), mHostAddr, 10026);
        }
        else if(mSentChecker > 3)
        {
            connectDevice();
            return;
        }

        mSentChecker++;
    }

    explicit PanelMonitorItemModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();
    }

    PanelMonitorItemModel(int dNum, QString dName, QString ip, QObject *parent):QObject(parent)
    {
        mIp = ip;
        setDeviceNum(dNum);
        setDeviceName(dName);
        mpCoreService = CoreService::getInstance();
    }
    ~PanelMonitorItemModel()
    {
        disconnectDevice();
    }

private:
    void connectDevice()
    {
        disconnectDevice();
        mSentChecker = 0;

        if(mIp.length() < 2)
            return;

        mHostAddr.setAddress(mIp);
        mpSock = new QUdpSocket();
        mpSock->connectToHost(mHostAddr, 10026);
        connect(mpSock, SIGNAL(readyRead()), this, SLOT(onReceive()));
        connect(mpSock,SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));
    }

    void disconnectDevice()
    {
        setConnectState(EnumDefine::ConnectState::CONN_STATE_DISCONNECT);

        if(mpSock != nullptr)
        {
            disconnect(mpSock, SIGNAL(readyRead()), this, SLOT(onReceive  ()));
            disconnect(mpSock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));

            qDebug() << "[PanelMonitorItemModel::disconnectDevice]state = " << mpSock->state();

            if(mpSock->state() != QAbstractSocket::SocketState::UnconnectedState)
            {
                mpSock->disconnectFromHost();
                mpSock->waitForDisconnected(1000);
            }
            mpSock->close();
            mpSock->deleteLater();
            mpSock = nullptr;
        }
    }
};
#endif // PANELMONITORITEMMODEL_H
