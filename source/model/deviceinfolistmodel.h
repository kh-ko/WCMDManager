#ifndef DEVICEINFOLISTMODEL_H
#define DEVICEINFOLISTMODEL_H

#include <QObject>
#include <QSettings>

#include "source/model/deviceinfomodel.h"

class DeviceInfoListModel : QObject
{
    Q_OBJECT

public:
    QSettings * mpSettings;
    QList<DeviceInfoModel *>  mDeviceList;

public:
    void addDeviceInfo(int num, QString name)
    {
        DeviceInfoModel * pDInfo = findDeviceInfo(num);

        if(pDInfo != nullptr)
        {
            return;
        }

        pDInfo = new DeviceInfoModel(this);
        pDInfo->mNumber = num;
        pDInfo->mName = name;

        mpSettings->setValue(QString("deviceinfo/%1").arg(num), name);

        addToList(pDInfo);
    }

    void setDeviceInfo(int num, QString name)
    {
        DeviceInfoModel * pDInfo = findDeviceInfo(num);

        if(pDInfo == nullptr)
        {
            return;
        }

        pDInfo->mName = name;

        mpSettings->setValue(QString("deviceinfo/%1").arg(num), name);
    }

    DeviceInfoModel * at(int idx)
    {
        return mDeviceList[idx];
    }
    int size()
    {
        return mDeviceList.size();
    }
    DeviceInfoModel * findDeviceInfo(int num)
    {
        foreach(DeviceInfoModel * pInfo, mDeviceList)
        {
            if(pInfo->mNumber == num)
                return pInfo;
        }
        return nullptr;
    }
    explicit DeviceInfoListModel(QObject *parent = nullptr):QObject(parent)
    {
        mpSettings = new QSettings("novasen","WCMDManager-DeviceInfo", this);

        QStringList listDevice = mpSettings->allKeys();

        for(int i = 0; i < listDevice.size(); i ++)
        {
            QString dName  = mpSettings->value(listDevice[i], "-").toString();

            int dNum = listDevice[i].split("/")[1].toInt();

            DeviceInfoModel * pNew = new DeviceInfoModel(this);
            pNew->mNumber = dNum;
            pNew->mName = dName;

            addToList(pNew);
        }
    }

    ~DeviceInfoListModel()
    {
        foreach(DeviceInfoModel * pInfo, mDeviceList)
        {
            delete pInfo;
        }

        mDeviceList.clear();
    }
private:


    void addToList(DeviceInfoModel * pInfo)
    {
        for(int i = 0; i < mDeviceList.size(); i ++)
        {
            if(mDeviceList[i]->mNumber > pInfo->mNumber)
            {
                mDeviceList.insert(i, pInfo);
                return;
            }
        }

        mDeviceList.append(pInfo);
    }

};
#endif // DEVICEINFOLISTMODEL_H
