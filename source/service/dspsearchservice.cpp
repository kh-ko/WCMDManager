#include "dspsearchservice.h"

#include <QNetworkInterface>
#include "source/service/coreservice.h"

#define MUTI_RCVER
void DspSearchService::onTimeout()
{
    searchComplete();
}
void DspSearchService::onReceive()
{
    QByteArray rcvBuffer;
    QHostAddress sender;
    quint16 senderPort;
    StPacket * rPacketData;


    if(mpSocket->hasPendingDatagrams() == false)
    {
        return;
    }

    rcvBuffer.resize(mpSocket->pendingDatagramSize());
    mpSocket->readDatagram(rcvBuffer.data(), rcvBuffer.size(), &sender, &senderPort);
    rPacketData = (StPacket *)rcvBuffer.data();

    if(rcvBuffer.size() != sizeof(StPacket))
    {
        return;
    }

    if(rPacketData->mFuncCode != EnumDefine::FuncCode::FUNC_CODE_INFO)
    {
        return;
    }

    int splitIdx = sender.toString().lastIndexOf(":");

    DeviceInfoModel * pModel = findDeviceInfo(rPacketData->mDeviceNum);

    if(pModel == nullptr)
        addDeviceInfo(rPacketData->mDeviceNum, "Unknow", sender.toString().mid(splitIdx + 1));
    else
    {
        pModel->mNumber = rPacketData->mDeviceNum;
        pModel->mIp = sender.toString().mid(splitIdx + 1);
    }

}
void DspSearchService::onSockError(QAbstractSocket::SocketError error)
{
    qDebug() << "[DspSearchService::onSockError]" << error;

    searchComplete();

    open();
}

void DspSearchService::search()
{
    StPacket packet;
    CoreService * pCoreService = CoreService::getInstance();

    if(mIsSearch)
        return;

    clear();

    for(int i = 0; i < pCoreService->mLSettingService.mDeviceListModel.size(); i ++)
    {
        DeviceInfoModel * pDInfo = pCoreService->mLSettingService.mDeviceListModel.at(i);
        addDeviceInfo(pDInfo->mNumber, pDInfo->mName, "");
    }

    mTimer.start();
    mIsSearch = true;

    packet.mFuncCode = EnumDefine::FuncCode::FUNC_CODE_INFO;
    packet.mSize = 0;
}

void DspSearchService::searchComplete()
{
    mTimer.stop();
    mIsSearch = false;

    emit signalEventCompletedSearch();
}

void DspSearchService::open()
{
    close();

    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();

    mpSocket = new QUdpSocket(this);

    mpSocket->bind(QHostAddress::AnyIPv4, mPort, QUdpSocket::ShareAddress);

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

    connect(mpSocket, &QUdpSocket::readyRead, this, &DspSearchService::onReceive);
    connect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));
}

void DspSearchService::close()
{
    if(mpSocket != nullptr)
    {
        disconnect(mpSocket, &QUdpSocket::readyRead, this, &DspSearchService::onReceive);
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
void DspSearchService::clear()
{
    foreach(DeviceInfoModel * pDInfo, mListDeviceInfo)
    {
        delete pDInfo;
    }
    mListDeviceInfo.clear();
}
DeviceInfoModel * DspSearchService::findDeviceInfo(int dNum)
{
    foreach(DeviceInfoModel * pDInfo, mListDeviceInfo)
    {
        if(pDInfo->mNumber == dNum)
            return pDInfo;
    }
    return nullptr;
}

void DspSearchService::addDeviceInfo(int dNum, QString name, QString ip)
{
    DeviceInfoModel * pNew = new DeviceInfoModel(this);
    pNew->mNumber = dNum;
    pNew->mIp = ip;
    pNew->mName = name;

    for(int i = 0; i < mListDeviceInfo.size(); i ++)
    {
        if(mListDeviceInfo[i]->mNumber > dNum)
        {

            mListDeviceInfo.insert(i, pNew);
            return;
        }
    }

    mListDeviceInfo.append(pNew);
    return;
}

DspSearchService::DspSearchService(QObject *parent) : QObject(parent)
{
    mTimer.setInterval(3000);
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    open();
}
DspSearchService::~DspSearchService()
{
    mListDeviceInfo.clear();

    clear();
    searchComplete();
}

