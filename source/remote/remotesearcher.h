#ifndef REMOTESEARCHER_H
#define REMOTESEARCHER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QUdpSocket>
#include <QNetworkInterface>

#include "source/remote/dto/enum/remoteenumdef.h"
#include "source/remote/dto/devinfodto.h"
#include "source/remote/strpacket.h"

class RemoteSearcher : public QObject
{
    Q_OBJECT
private:
    const quint16      PORT    = 31072;

public:
    QHostAddress mGroupAddress     ;
    QTimer       mTimer            ;
    QUdpSocket * mpSocket = nullptr;

    QList<DevInfoDto> mDevInfoList;

    RemoteSearcher(QObject *parent = nullptr) : QObject(parent)
    {
        qDebug() << "[RemoteSearcher] create instance";

        mTimer.setInterval(3000);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        //open();
    }
    ~RemoteSearcher()
    {
        close();
        mTimer.stop();
    }

    void search()
    {
        mDevInfoList.clear();

        open();

        mTimer.stop();
        mTimer.start();
    }

signals:
    void signalEventCompletedSearch();

public slots:
    void onTimeout()
    {
        searchComplete();
        close();
    }
    void onReceive()
    {
        QByteArray rcvBuffer;
        QHostAddress sender;
        quint16 senderPort;
        StRPacket * rPacketData;


        if(mpSocket->hasPendingDatagrams() == false)
        {
            return;
        }

        rcvBuffer.resize(mpSocket->pendingDatagramSize());
        mpSocket->readDatagram(rcvBuffer.data(), rcvBuffer.size(), &sender, &senderPort);
        rPacketData = (StRPacket *)rcvBuffer.data();

        if(rcvBuffer.size() != sizeof(StRPacket))
        {
            return;
        }

        if(rPacketData->mFuncCode != RemoteEnumDef::RFUNC_CODE_INFO)
        {
            return;
        }

        int splitIdx = sender.toString().lastIndexOf(":");

        addDevInfo(rPacketData->mDeviceNum, sender.toString().mid(splitIdx + 1));
    }
    void onSockError(QAbstractSocket::SocketError error)
    {
        qDebug() << "[DspSearchService::onSockError]" << error << ",err string = " << (mpSocket != nullptr ? mpSocket->errorString() : "");

        searchComplete();

        open();
    }

public:

private:
    void searchComplete()
    {
        mTimer.stop();
        emit signalEventCompletedSearch();
    }

    void open()
    {
        close();

        QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();

        mpSocket = new QUdpSocket(this);


        mpSocket->bind(QHostAddress::AnyIPv4, PORT, QUdpSocket::ShareAddress);

        mGroupAddress.setAddress("239.168.0.21");

        for(int idx = 0; idx < interfaceList.size(); idx ++)
        {
            QNetworkInterface iface = interfaceList.at(idx);

            if(iface.flags().testFlag(QNetworkInterface::InterfaceFlag::CanBroadcast)        &&
               iface.flags().testFlag(QNetworkInterface::InterfaceFlag::IsLoopBack) == false )
            {
                mpSocket->joinMulticastGroup(mGroupAddress, iface);
            }
        }
        connect(mpSocket, &QUdpSocket::readyRead, this, &RemoteSearcher::onReceive);
        connect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));
    }

    void close()
    {
        if(mpSocket != nullptr)
        {
            disconnect(mpSocket, &QUdpSocket::readyRead, this, &RemoteSearcher::onReceive);
            disconnect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));

            QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();

            for(int idx = 0; idx < interfaceList.size(); idx ++)
            {
                QNetworkInterface iface = interfaceList.at(idx);

                if(iface.flags().testFlag(QNetworkInterface::InterfaceFlag::CanBroadcast)        &&
                   iface.flags().testFlag(QNetworkInterface::InterfaceFlag::IsLoopBack) == false )
                {
                    mpSocket->leaveMulticastGroup(mGroupAddress, iface);
                }
            }
            mpSocket->close();
            mpSocket->deleteLater();
            mpSocket = nullptr;
        }
    }

    void addDevInfo(int num, QString ip)
    {
        foreach(DevInfoDto devInfo, mDevInfoList)
        {
            if(devInfo.mNumber == num)
            {
                devInfo.mIp = ip;
                return;
            }
        }

        DevInfoDto newDevInfo;

        newDevInfo.mNumber = num;
        newDevInfo.mIp     = ip;

        mDevInfoList.append(newDevInfo);
    }
};

#endif // REMOTESEARCHER_H
