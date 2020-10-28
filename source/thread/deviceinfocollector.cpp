#include "deviceinfocollector.h"

#include <QNetworkInterface>

#include "source/globaldef/EnumDefine.h"

void DeviceInfoCollectWorker::onReceive()
{
    QByteArray rcvBuffer;
    QHostAddress sender;
    quint16 senderPort;
    StPacket * rPacketData;
    DeviceInfoDto deviceInfoDto;

    qDebug()<< "[debug] onReceive ";

    if(mpSocket->hasPendingDatagrams() == false)
    {
        return;
    }

    if(mpSocket->pendingDatagramSize() != sizeof(StPacket))
    {
        close();
        open();
        return;
    }

    rcvBuffer.resize(mpSocket->pendingDatagramSize());
    mpSocket->readDatagram(rcvBuffer.data(), rcvBuffer.size(), &sender, &senderPort);
    rPacketData = (StPacket *)rcvBuffer.data();

    if(rPacketData->mFuncCode != EnumDefine::FuncCode::FUNC_CODE_INFO)
    {
        close();
        open();
        return;
    }

    qDebug()<< "[debug] onReceive ip : " << sender.toString();

    int splitIdx = sender.toString().lastIndexOf(":");

    deviceInfoDto.mIPv4Address = sender.toIPv4Address();
    deviceInfoDto.mIp = sender.toString().mid(splitIdx + 1);
    deviceInfoDto.mDeviceNum = rPacketData->mDeviceNum;

    emit signalEventReceive(deviceInfoDto);
}

void DeviceInfoCollectWorker::onSockError(QAbstractSocket::SocketError error)
{
    qDebug() << "[SOCKET ERROR]" << error;
    close();
    open();
}

void DeviceInfoCollectWorker::onStart()
{
    qDebug() << "[DeviceInfoCollectWorker::onStart]";
    open();
}


void DeviceInfoCollectWorker::open()
{
    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();

    mpSocket = new QUdpSocket(this);

    mpSocket->bind(QHostAddress::AnyIPv4, mPort, QUdpSocket::ShareAddress);

    for(int idx = 0; idx < interfaceList.size(); idx ++)
    {
        QNetworkInterface iface = interfaceList.at(idx);
        //qDebug() << "[debug]" << iface.name();
        //qDebug() << "[debug]flags" << iface.flags();
        //qDebug() << "[debug]isValid" << iface.isValid();
        //qDebug() << "[debug]type" << iface.type();

        //for(int i = 0; i < iface.addressEntries().size(); i ++)
        //{
        //    qDebug() << "[debug]protocol" << iface.addressEntries().at(i).ip().protocol();
        //    qDebug() << "[debug]ip" << iface.addressEntries().at(i).ip().toString();
        //}

        //qDebug() << "[debug]IsRunning" << iface.flags() & QNetworkInterface::InterfaceFlag::IsRunning);
        //qDebug() << "[debug]IsLoopBack" << iface.flags() & QNetworkInterface::InterfaceFlag::IsLoopBack);
        //qDebug() << "[debug]IsLoopBack" << (iface.);
        //if(iface.flags() & QNetworkInterface::InterfaceFlag::CanBroadcast)
        //{
        //    mpSocket->setMulticastInterface(iface);
        //    qDebug() << "[debug] iface" << iface.name();
        //    break;
        //}
    }

    qDebug() << "[debug]join = " << mpSocket->joinMulticastGroup(mGroupAddress, interfaceList.at(1));

    connect(mpSocket, &QUdpSocket::readyRead, this, &DeviceInfoCollectWorker::onReceive);
    connect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));
}

void DeviceInfoCollectWorker::close()
{
    if(mpSocket == nullptr)
        return;

    mpSocket->close();
    mpSocket->deleteLater();
    mpSocket = nullptr;
}

DeviceInfoCollectWorker::DeviceInfoCollectWorker(QObject *parent) : QObject(parent)
{
    mGroupAddress.setAddress("239.168.0.21");
    close();
}

DeviceInfoCollectWorker::~DeviceInfoCollectWorker()
{
    close();
}
