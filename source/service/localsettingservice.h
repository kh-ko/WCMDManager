#ifndef LOCALSETTINGSERVICE_H
#define LOCALSETTINGSERVICE_H

#include <QObject>
#include <QSettings>

#include "source/globaldef/EnumDefine.h"
#include "source/model/managersettingmodel.h"
#include "source/model/metaldetectorsettingmodel.h"
#include "source/model/signsettingmodel.h"
#include "source/model/deviceinfolistmodel.h"

class LocalSettingService : public QObject
{
    Q_OBJECT
public:
    int                       mLanguage             ;
    QString                   mPassword             ;
    int                       mMoniteringRefreshCycle;
    int                       mSelectedYear         ;
    int                       mSelectedMonth        ;
    int                       mSelectedDay          ;
    int                       mDeviceNumber         ;
    quint64                   mWCProductSeq         = 0;
    ManagerSettingModel       mManagerSettingModel  ;
    MetalDetectorSettingModel mMDSettingModel       ;
    SignSettingModel          mSignSettingModel     ;
    DeviceInfoListModel       mDeviceListModel      ;

    void setLanguage(int value);
    void setPassword(QString value);
    void setMoniteringRefreshCycle(int value);
    void setSelectDate(int year, int month, int day);
    void setDeviceNumber(int value);
    void setWCProductSeq(quint64 value);
    void setManagerSetting(QString company, QString department, QString position, QString name);
    void setMetalDetectorSetting(QString limitCriteriaFe, QString limitCriteriaSus, QString haccp, QString checkupCycle);
    void setSignSetting(bool isCheckWrite, bool isCheckReview, bool isCheckApproved);
    void addDeviceInfo(int num);
    void setDeviceInfo(int num, QString name);

signals:
    void signalEventChangedLanguage();
    void signalEventChangedPassword();
    void signalEventChangedMoniteringRefreshCycle();
    void signalEventChangedSelectDate();
    void signalEventChangedDeviceNumber();
    void signalEventChangedWCProductSeq();
    void signalEventChangedManagerSetting();
    void signalEventChangedMetalDetectorSetting();
    void signalEventChangedSignSetting();
    void signalEventAddedDeviceInfo(int num, QString name);
    void signalEventUpdateDeviceInfo(int num, QString name);

private:
    QSettings* mpSettings;

    void loadLanguage();
    void loadPassword();
    void loadMoniteringRefreshCycle();
    void loadSelectDate();
    void loadDeviceNumber();
    void loadManagerSetting();
    void loadMetalDetectorSetting();
    void loadSignSetting();
    void loadDeviceInfoList();
public:
    explicit LocalSettingService(QObject *parent = nullptr);

};

#endif // LOCALSETTINGSERVICE_H
