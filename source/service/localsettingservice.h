#ifndef LOCALSETTINGSERVICE_H
#define LOCALSETTINGSERVICE_H

#include <QObject>
#include <QSettings>

#include "source/globaldef/EnumDefine.h"
#include "source/model/managersettingmodel.h"
#include "source/model/metaldetectorsettingmodel.h"
#include "source/model/signsettingmodel.h"

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
    ManagerSettingModel       mManagerSettingModel  ;
    MetalDetectorSettingModel mMDSettingModel       ;
    SignSettingModel          mSignSettingModel     ;

    void setLanguage(int value);
    void setPassword(QString value);
    void setMoniteringRefreshCycle(int value);
    void setSelectDate(int year, int month, int day);
    void setDeviceNumber(int value);
    void setManagerSetting(QString company, QString department, QString position, QString name);
    void setMetalDetectorSetting(QString limitCriteriaFe, QString limitCriteriaSus, QString haccp, QString checkupCycle);
    void setSignSetting(bool isCheckWrite, bool isCheckReview, bool isCheckApproved);

signals:
    void signalEventChangedLanguage();
    void signalEventChangedPassword();
    void signalEventChangedMoniteringRefreshCycle();
    void signalEventChangedSelectDate();
    void signalEventChangedDeviceNumber();
    void signalEventChangedManagerSetting();
    void signalEventChangedMetalDetectorSetting();
    void signalEventChangedSignSetting();
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
public:
    explicit LocalSettingService(QObject *parent = nullptr);

};

#endif // LOCALSETTINGSERVICE_H
