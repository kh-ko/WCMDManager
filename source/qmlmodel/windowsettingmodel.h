#ifndef WINDOWSETTINGMODEL_H
#define WINDOWSETTINGMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"
#include "source/helper/languagehelper.h"

class WindowSettingModel : public QObject
{
    Q_OBJECT

private:
    CoreService *          mpCoreService;
    //DeviceInfoCollector *  mpDeviceInfoCollector;

    int     mLanguage;
    QString mPassword;
    int     mRefreshCycle;
signals:

public slots:
    Q_INVOKABLE int onCommandGetLanguage()
    {
        return pLSettingSvc->mLanguage;
    }
    Q_INVOKABLE QString onCommandGetPassword()
    {
        return pLSettingSvc->mPassword;
    }
    Q_INVOKABLE int onCommandGetRefreshCycle()
    {
        return pLSettingSvc->mMoniteringRefreshCycle;
    }
    /*Q_INVOKABLE int onCommandGetDeviceCnt()
    {
        return mpDeviceInfoCollector->mListDeviceInfo.size();
    }
    Q_INVOKABLE int onCommandGetDeviceNum(int idx)
    {
        return mpDeviceInfoCollector->mListDeviceInfo[idx]->mDeviceNum;
    }
    Q_INVOKABLE QString onCommandGetDeviceName(int idx)
    {
        return mpDeviceInfoCollector->mListDeviceInfo[idx]->mDeviceName;
    }
    Q_INVOKABLE QString onCommandGetDeviceIP(int idx)
    {
        return mpDeviceInfoCollector->mListDeviceInfo[idx]->mIp;
    }*/
    Q_INVOKABLE void onCommandSetSetting(int lang, QString pwd, QString cycle)
    {
        float fcycle = cycle.toFloat();
        int   nCycle = qRound(fcycle * 1000);

        if(nCycle < 100)
            return;

        if(pwd.length() < 1)
            return;

        LanguageHelper::getInstance()->loadLanguage((EnumDefine::Language)lang);
        pLSettingSvc->setLanguage(lang);
        pLSettingSvc->setPassword(pwd);
        pLSettingSvc->setMoniteringRefreshCycle(nCycle);
    }
    /*Q_INVOKABLE void onCommandSetDeviceInfo(bool isNew, QString dNum, QString dName, QString dIP)
    {

        int   deviceNum = dNum.toInt();

        if(deviceNum < 1)
            return;

        if(isNew)
        {
            mpDeviceInfoCollector->addDeviceInfo(deviceNum, dIP, dName);
        }
        else
        {
            mpDeviceInfoCollector->setDeviceInfo(deviceNum, dIP, dName);
        }

    }*/

public:
    explicit WindowSettingModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();
        //mpDeviceInfoCollector = &mpCoreService->mDeviceInfoCollector;
    }
};
#endif // WINDOWSETTINGMODEL_H
