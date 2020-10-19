#include "localsettingservice.h"

#include <QDate>

void LocalSettingService::setLanguage(int value)
{
    mLanguage = value;

    mpSettings->setValue("language/language" , value );
    emit signalEventChangedLanguage();
}

void LocalSettingService::setPassword(QString value)
{
    mPassword = value;

    mpSettings->setValue("security/password" , value );
    emit signalEventChangedPassword();
}

void LocalSettingService::setMoniteringRefreshCycle(int value)
{
    mMoniteringRefreshCycle = value;

    mpSettings->setValue("network/monitering_refreshcycle" , value );
    emit signalEventChangedMoniteringRefreshCycle();
}

void LocalSettingService::setSelectDate(int year, int month, int day)
{
    mSelectedYear  = year ;
    mSelectedMonth = month;
    mSelectedDay   = day  ;

    mpSettings->setValue("selectdate/year" , year );
    mpSettings->setValue("selectdate/month", month);
    mpSettings->setValue("selectdate/day"  , day  );

    emit signalEventChangedSelectDate();
}

void LocalSettingService::setDeviceNumber(int value)
{
    mDeviceNumber = value;

    mpSettings->setValue("device/device_number" , value );

    emit signalEventChangedDeviceNumber();
}
void LocalSettingService::setManagerSetting(QString company, QString department, QString position, QString name)
{
    mManagerSettingModel.setCompany   (company   );
    mManagerSettingModel.setDepartment(department);
    mManagerSettingModel.setPosition  (position  );
    mManagerSettingModel.setName      (name      );

    mpSettings->setValue("manager/company"   , company   );
    mpSettings->setValue("manager/department", department);
    mpSettings->setValue("manager/position"  , position  );
    mpSettings->setValue("manager/name"      , name      );

    emit signalEventChangedManagerSetting();
}
void LocalSettingService::setMetalDetectorSetting(QString limitCriteriaFe, QString limitCriteriaSus, QString haccp, QString checkupCycle)
{
    mMDSettingModel.setLimitCriteriaFe (limitCriteriaFe );
    mMDSettingModel.setLimitCriteriaSus(limitCriteriaSus);
    mMDSettingModel.setHACCP           (haccp           );
    mMDSettingModel.setCheckupCycle    (checkupCycle    );

    mpSettings->setValue("metaldetector/limit_criteria_fe" , limitCriteriaFe );
    mpSettings->setValue("metaldetector/limit_criteria_sus", limitCriteriaSus);
    mpSettings->setValue("metaldetector/haccp"             , haccp           );
    mpSettings->setValue("metaldetector/checkup_cycle"     , checkupCycle    );

    emit signalEventChangedMetalDetectorSetting();
}

void LocalSettingService::setSignSetting(bool isCheckWrite, bool isCheckReview, bool isCheckApproved)
{
    mSignSettingModel.setIsCheckWrite   (isCheckWrite);
    mSignSettingModel.setIsCheckReview  (isCheckReview);
    mSignSettingModel.setIsCheckApproved(isCheckApproved);

    mpSettings->setValue("sign/write"   , isCheckWrite   );
    mpSettings->setValue("sign/review"  , isCheckReview  );
    mpSettings->setValue("sign/approved", isCheckApproved);

    emit signalEventChangedSignSetting();
}

void LocalSettingService::loadLanguage()
{
    int language  = mpSettings->value("language/language" , EnumDefine::Language::LANG_ENG).toInt();

    setLanguage(language);
}
void LocalSettingService::loadPassword()
{
    QString pwd  = mpSettings->value("security/password" , "1111").toString();

    setPassword(pwd);
}
void LocalSettingService::loadMoniteringRefreshCycle()
{
    int cycle  = mpSettings->value("network/monitering_refreshcycle" , 1000).toInt();

    setMoniteringRefreshCycle(cycle);
}

void LocalSettingService::loadSelectDate()
{
    int year  = mpSettings->value("selectdate/year" , -1).toInt();
    int month = mpSettings->value("selectdate/month", -1).toInt();
    int day   = mpSettings->value("selectdate/day"  , -1).toInt();

    if(year == -1 || month == -1 || day == -1)
    {
        year  = QDate::currentDate().year();
        month = QDate::currentDate().month();
        day   = QDate::currentDate().day();
    }

    setSelectDate(year, month, day);
}
void LocalSettingService::loadDeviceNumber()
{
    int dNumber  = mpSettings->value("device/device_number" , 0).toInt();

    setDeviceNumber(dNumber);
}
void LocalSettingService::loadManagerSetting()
{
    QString company    = mpSettings->value("manager/company"   , "-").toString();
    QString department = mpSettings->value("manager/department", "-").toString();
    QString position   = mpSettings->value("manager/position"  , "-").toString();
    QString name       = mpSettings->value("manager/name"      , "-").toString();

    setManagerSetting(company, department, position, name);
}
void LocalSettingService::loadMetalDetectorSetting()
{
    QString limitCriteriaFe  =  mpSettings->value("metaldetector/limit_criteria_fe" , "2.5").toString();
    QString limitCriteriaSus =  mpSettings->value("metaldetector/limit_criteria_sus", "2.5").toString();
    QString haccp            =  mpSettings->value("metaldetector/haccp"             , "CCP - 2P").toString();
    QString checkupCycle     =  mpSettings->value("metaldetector/checkup_cycle"     , "매 운전시 마다").toString();

    setMetalDetectorSetting(limitCriteriaFe, limitCriteriaSus, haccp, checkupCycle);
}

void LocalSettingService::loadSignSetting()
{
    bool isCheckWrite    = mpSettings->value("sign/write"   , true).toBool();
    bool isCheckReview   = mpSettings->value("sign/review"  , true).toBool();
    bool isCheckApproved = mpSettings->value("sign/approved", true).toBool();

    setSignSetting(isCheckWrite, isCheckReview, isCheckApproved);
}

LocalSettingService::LocalSettingService(QObject *parent) : QObject(parent)
{
    mpSettings = new QSettings("novasen","WCMDManager", this);

    loadLanguage();
    loadPassword();
    loadMoniteringRefreshCycle();
    loadSelectDate();
    loadDeviceNumber();
    loadManagerSetting();
    loadMetalDetectorSetting();
    loadSignSetting();
}
