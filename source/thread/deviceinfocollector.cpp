#include "deviceinfocollector.h"
#include "source/globaldef/EnumDefine.h"

void DeviceInfoCollectWorker::onReceive()
{
    QByteArray rcvBuffer;
    QHostAddress sender;
    quint16 senderPort;
    StPacket * rPacketData;
    DeviceInfoDto deviceInfoDto;

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
    mpSocket = new QUdpSocket(this);
    mpSocket->bind(mPort, QUdpSocket::ShareAddress);

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
    close();
}

DeviceInfoCollectWorker::~DeviceInfoCollectWorker()
{
    close();
}
