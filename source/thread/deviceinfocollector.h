#ifndef DEVICEINFOCOLLECTOR_H
#define DEVICEINFOCOLLECTOR_H


#include <QObject>
#include <QTimer>
#include <QThread>
#include <QMap>
#include <QUdpSocket>
#include <QSettings>

#include "source/thread/dto/deviceinfodto.h"
#include "source/thread/dto/devicesocketdto.h"

class DeviceInfoCollectWorker : public QObject
{
    Q_OBJECT
public:
    QUdpSocket * mpSocket = nullptr;
    quint16      mPort    = 10022;
    QHostAddress mHostAddr;

public slots:
    void onReceive();
    void onSockError(QAbstractSocket::SocketError error);

signals:
    void signalEventReceive (DeviceInfoDto value);

public:
    void onStart();
    explicit DeviceInfoCollectWorker(QObject *parent = nullptr);
    ~DeviceInfoCollectWorker();

private:
    void open();
    void close();
};

class DeviceInfoCollector : public QObject
{
    Q_OBJECT
public:
    DeviceInfoCollectWorker * mpWoker;
    QThread mThread;
    QSettings *mpSettings;

    QList<DeviceInfoDto *> mListDeviceInfo;

    explicit DeviceInfoCollector(QObject *parent = nullptr) : QObject(parent)
    {
        mpSettings = new QSettings("novasen","WCMDManager-DeviceInfo", this);
        mpWoker = new DeviceInfoCollectWorker;
        mpWoker->moveToThread(&mThread);

        connect(&mThread, &QThread::finished, mpWoker, &QObject::deleteLater);
        connect(&mThread, &QThread::started,  mpWoker, &DeviceInfoCollectWorker::onStart);

        connect(mpWoker, SIGNAL(signalEventReceive (DeviceInfoDto)), this, SLOT(onSignalEventReceive (DeviceInfoDto)));

        QStringList listDevice = mpSettings->allKeys();

        for(int i = 0; i < listDevice.size(); i ++)
        {
            QStringList listValue  = mpSettings->value(listDevice[i], "").toString().split(":");

            int dNum = listDevice[i].split("/")[1].toInt();

            if(listValue.size() < 2)
            {
                addDeviceInfo(dNum, "", "");
            }
            else
            {
                addDeviceInfo(dNum, listValue[0], listValue[1]);
            }
        }

        mThread.start();
    }
    ~DeviceInfoCollector()
    {
        for(int i = 0; i < mListDeviceInfo.size(); i ++)
        {
            delete mListDeviceInfo[i];
        }
        mListDeviceInfo.clear();

        mThread.quit();
        mThread.wait();
    }

    void addDeviceInfo(int dNum, QString ip, QString name)
    {
        QHostAddress hostAddr;
        hostAddr.setAddress(ip);
        quint32 ipv4 = hostAddr.toIPv4Address();

        DeviceInfoDto * pExistInfo = findDeviceInfo(dNum);
        DeviceInfoDto * pSameIpInfo = findDeviceInfoByIPv4Address(ipv4);

        if(pExistInfo == nullptr)
        {
            if(pSameIpInfo != nullptr && pSameIpInfo->mDeviceNum != dNum)
            {
                pSameIpInfo->mIPv4Address = 0;
                pSameIpInfo->mIp = "";
                mpSettings->setValue(QString("deviceinfo/%1").arg(pSameIpInfo->mDeviceNum), QString("%1:%2").arg(pSameIpInfo->mIp).arg(pSameIpInfo->mDeviceName));
                emit signalEventUpdateDeviceInfo(*pSameIpInfo);
            }

            mpSettings->setValue(QString("deviceinfo/%1").arg(dNum), QString("%1:%2").arg(ip).arg(name));
            DeviceInfoDto * newInfo = new DeviceInfoDto(dNum, ip, name);
            newInfo->mIPv4Address = ipv4;
            addToList(newInfo);
            emit signalEventAddedDeviceInfo(*newInfo);
        }
    }

    void addDeviceNumber(int deviceNum)
    {
        DeviceInfoDto * pExistInfo = findDeviceInfo(deviceNum);

        if(pExistInfo == nullptr)
        {
            mpSettings->setValue(QString("deviceinfo/%1").arg(deviceNum), QString("%1:%2").arg("").arg(""));
            DeviceInfoDto * newInfo = new DeviceInfoDto(deviceNum, "", "");
            addToList(newInfo);
            emit signalEventAddedDeviceInfo(*newInfo);
        }
    }

    void setDeviceInfo(int dNum, QString ip, QString name)
    {
        QHostAddress hostAddr;
        hostAddr.setAddress(ip);
        quint32 ipv4 = hostAddr.toIPv4Address();

        DeviceInfoDto * pExistInfo = findDeviceInfo(dNum);

        if(pExistInfo == nullptr)
        {
            return;
        }

        DeviceInfoDto * pSameIpInfo = findDeviceInfoByIPv4Address(ipv4);

        if(pSameIpInfo != nullptr && pSameIpInfo->mDeviceNum != dNum)
        {
            pSameIpInfo->mIPv4Address = 0;
            pSameIpInfo->mIp = "";
            mpSettings->setValue(QString("deviceinfo/%1").arg(pSameIpInfo->mDeviceNum), QString("%1:%2").arg(pSameIpInfo->mIp).arg(pSameIpInfo->mDeviceName));

            emit signalEventUpdateDeviceInfo(*pSameIpInfo);
        }

        pExistInfo->mDeviceNum = dNum;
        pExistInfo->mDeviceName = name;
        pExistInfo->mIp         = ip;
        pExistInfo->mIPv4Address = ipv4;
        mpSettings->setValue(QString("deviceinfo/%1").arg(dNum), QString("%1:%2").arg(ip).arg(name));

        emit signalEventUpdateDeviceInfo(*pExistInfo);
    }

    void setDeviceName(int deviceNum, QString deviceName)
    {
        DeviceInfoDto * pExistInfo = findDeviceInfo(deviceNum);

        if(pExistInfo == nullptr)
        {
            return;
        }

        pExistInfo->mDeviceName = deviceName;

        mpSettings->setValue(QString("deviceinfo/%1").arg(deviceNum), QString("%1:%2").arg(pExistInfo->mIp).arg(deviceName));

        emit signalEventUpdateDeviceInfo(*pExistInfo);
    }

    void setDeviceIp(int deviceNum, QString deviceIp)
    {
        QHostAddress hostAddr;
        hostAddr.setAddress(deviceIp);
        quint32 ipv4 = hostAddr.toIPv4Address();

        DeviceInfoDto * pExistInfo = findDeviceInfo(deviceNum);
        DeviceInfoDto * pSameIPInfo = findDeviceInfoByIPv4Address(ipv4);

        if(pSameIPInfo != nullptr && pSameIPInfo->mDeviceNum != deviceNum)
        {
            pSameIPInfo->mIPv4Address = 0;
            pSameIPInfo->mIp = "";
            mpSettings->setValue(QString("deviceinfo/%1").arg(pSameIPInfo->mDeviceNum), QString("%1:%2").arg(pSameIPInfo->mIp).arg(pSameIPInfo->mDeviceName));

            emit signalEventUpdateDeviceInfo(*pSameIPInfo);
        }

        if(pExistInfo == nullptr)
        {
            pExistInfo = new DeviceInfoDto(deviceNum, deviceIp, "");
            pExistInfo->mIPv4Address = ipv4;
            addToList(pExistInfo);

            mpSettings->setValue(QString("deviceinfo/%1").arg(deviceNum), QString("%1:%2").arg(deviceIp).arg(""));

            emit signalEventAddedDeviceInfo(*pExistInfo);

            return;
        }

        if(pExistInfo->mIPv4Address == ipv4)
            return;

        pExistInfo->mIp = deviceIp;
        pExistInfo->mIPv4Address = ipv4;
        mpSettings->setValue(QString("deviceinfo/%1").arg(deviceNum), QString("%1:%2").arg(deviceIp).arg(pExistInfo->mDeviceName));

        emit signalEventUpdateDeviceInfo(*pExistInfo);
    }

    void addToList(DeviceInfoDto * pInfo)
    {
        for(int i = 0; i < mListDeviceInfo.size(); i ++)
        {
            if(mListDeviceInfo[i]->mDeviceNum > pInfo->mDeviceNum)
            {
                mListDeviceInfo.insert(i, pInfo);
                return;
            }
        }

        mListDeviceInfo.append(pInfo);
    }

    DeviceInfoDto * findDeviceInfo(int dNum)
    {
        for(int i = 0; i < mListDeviceInfo.size(); i ++)
        {
            if(mListDeviceInfo[i]->mDeviceNum == dNum)
                return mListDeviceInfo[i];
        }
        return nullptr;
    }

    DeviceInfoDto * findDeviceInfoByIPv4Address(quint32 ipv4addr)
    {
        for(int i = 0; i < mListDeviceInfo.size(); i ++)
        {
            if(mListDeviceInfo[i]->mIPv4Address == ipv4addr)
                return mListDeviceInfo[i];
        }
        return nullptr;
    }

    DeviceInfoDto * findDeviceInfoByIP(QString ip)
    {
        for(int i = 0; i < mListDeviceInfo.size(); i ++)
        {
            if(mListDeviceInfo[i]->mIp == ip)
                return mListDeviceInfo[i];
        }
        return nullptr;
    }


signals:
    void signalEventAddedDeviceInfo(DeviceInfoDto value);
    void signalEventUpdateDeviceInfo(DeviceInfoDto value);

public slots:
    void onSignalEventReceive (DeviceInfoDto value)
    {
        setDeviceIp(value.mDeviceNum, value.mIp);
    }
};


#endif // DEVICEINFOCOLLECTOR_H
