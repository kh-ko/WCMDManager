#ifndef LOCALSETTINGSERVICE_H
#define LOCALSETTINGSERVICE_H

#include <QObject>
#include <QSettings>
#include <QDateTime>
#include <QDebug>

#include "source/history/def/datetimeform.h"
#include "source/globaldef/EnumDefine.h"
#include "source/model/managersettingmodel.h"
#include "source/model/metaldetectorsettingmodel.h"
#include "source/model/signsettingmodel.h"
#include "source/model/deviceinfolistmodel.h"

#define pLSettingSvc LocalSettingService::getInstance()

class LocalSettingService : public QObject
{
    Q_OBJECT
public:
    static LocalSettingService * getInstance()
    {
        static LocalSettingService  *pSelf = nullptr;

        if(pSelf == nullptr)
        {
            pSelf = new LocalSettingService();
        }

        return pSelf;
    }

    QString                   mOldVersion           ;
    QString                   mVersion              = "1.0.7";
    int                       mLanguage             ;
    QString                   mPassword             ;
    int                       mMoniteringRefreshCycle;
    QDate                     mSelectedDate         ;
    int                       mDeviceNumber         ;
    quint64                   mWCProductSeq         = 0;
    ManagerSettingModel       mManagerSettingModel  ;
    MetalDetectorSettingModel mMDSettingModel       ;
    SignSettingModel          mSignSettingModel     ;

    LocalSettingService(QObject *parent = nullptr) : QObject(parent)
    {
        qDebug() << "[LocalSettingService] create instance";

        mpSettings = new QSettings("novasen","WCMDManager", this);
    }

    void start()
    {
        QString mOldVersion  = mpSettings->value("build/version" , "0.0.1").toString();
        mpSettings->setValue("build/version", mVersion);
        loadLanguage();
        loadPassword();
        loadMoniteringRefreshCycle();
        loadSelectDate();
        loadDeviceNumber();
        loadManagerSetting();
        loadMetalDetectorSetting();
        loadSignSetting();
    }

    void stop()
    {
    }

    void setLanguage(int value)
    {
        mLanguage = value;

        mpSettings->setValue("language/language" , value );
        emit signalEventChangedLanguage();
    }

    void setPassword(QString value)
    {
        mPassword = value;

        mpSettings->setValue("security/password" , value );
        emit signalEventChangedPassword();
    }

    void setMoniteringRefreshCycle(int value)
    {
        mMoniteringRefreshCycle = value;

        mpSettings->setValue("network/monitering_refreshcycle" , value );
        emit signalEventChangedMoniteringRefreshCycle();
    }

    void setSelectDate(QDate selDate)
    {
        mSelectedDate = selDate;

        mpSettings->setValue("selectdate/date" , mSelectedDate.toString(DATE_FILE_NAME_FMT) );

        emit signalEventChangedSelectDate();
    }

    void setDeviceNumber(int value)
    {
        mDeviceNumber = value;

        mpSettings->setValue("device/device_number" , value );

        emit signalEventChangedDeviceNumber();
    }

    void setWCProductSeq(quint64 value)
    {
        mWCProductSeq = value;

        emit signalEventChangedWCProductSeq();
    }
    void setMDManagerSetting(QString company, QString mdDepartment, QString mdPosition, QString mdName)
    {
        mManagerSettingModel.setCompany     (company     );
        mManagerSettingModel.setMDDepartment(mdDepartment);
        mManagerSettingModel.setMDPosition  (mdPosition  );
        mManagerSettingModel.setMDName      (mdName      );

        mpSettings->setValue("manager/company"     , company   );
        mpSettings->setValue("manager/department"  , mdDepartment);
        mpSettings->setValue("manager/position"    , mdPosition  );
        mpSettings->setValue("manager/name"        , mdName      );

        emit signalEventChangedManagerSetting();
    }

    void setWCManagerSetting(QString company, QString wcDepartment, QString wcPosition, QString wcName)
    {
        mManagerSettingModel.setCompany     (company     );
        mManagerSettingModel.setWCDepartment(wcDepartment);
        mManagerSettingModel.setWCPosition  (wcPosition  );
        mManagerSettingModel.setWCName      (wcName      );

        mpSettings->setValue("manager/company"     , company   );
        mpSettings->setValue("manager/wcdepartment", wcDepartment);
        mpSettings->setValue("manager/wcposition"  , wcPosition  );
        mpSettings->setValue("manager/wcname"      , wcName      );

        emit signalEventChangedManagerSetting();
    }

    void setMetalDetectorSetting(QString haccp, QString checkupCycle)
    {
        //mMDSettingModel.setLimitCriteriaFe (limitCriteriaFe );
        //mMDSettingModel.setLimitCriteriaSus(limitCriteriaSus);
        mMDSettingModel.setHACCP           (haccp           );
        mMDSettingModel.setCheckupCycle    (checkupCycle    );

        //mpSettings->setValue("metaldetector/limit_criteria_fe" , limitCriteriaFe );
        //mpSettings->setValue("metaldetector/limit_criteria_sus", limitCriteriaSus);
        mpSettings->setValue("metaldetector/haccp"             , haccp           );
        mpSettings->setValue("metaldetector/checkup_cycle"     , checkupCycle    );

        emit signalEventChangedMetalDetectorSetting();
    }

    void setSignSetting(bool isCheckWrite, bool isCheckReview, bool isCheckApproved)
    {
        mSignSettingModel.setIsCheckWrite   (isCheckWrite);
        mSignSettingModel.setIsCheckReview  (isCheckReview);
        mSignSettingModel.setIsCheckApproved(isCheckApproved);

        mpSettings->setValue("sign/write"   , isCheckWrite   );
        mpSettings->setValue("sign/review"  , isCheckReview  );
        mpSettings->setValue("sign/approved", isCheckApproved);

        emit signalEventChangedSignSetting();
    }

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

private:
    QSettings* mpSettings;

    void loadLanguage()
    {
        int language  = mpSettings->value("language/language" , EnumDefine::Language::LANG_ENG).toInt();

        setLanguage(language);
    }
    void loadPassword()
    {
        QString pwd  = mpSettings->value("security/password" , "1111").toString();

        setPassword(pwd);
    }
    void loadMoniteringRefreshCycle()
    {
        int cycle  = mpSettings->value("network/monitering_refreshcycle" , 1000).toInt();

        setMoniteringRefreshCycle(cycle);
    }

    void loadSelectDate()
    {
        QString strDate = mpSettings->value("selectdate/date" , QDate::currentDate()).toString();

        QDate date = QDate::fromString(strDate, DATE_FILE_NAME_FMT);

        setSelectDate(date);
    }
    void loadDeviceNumber()
    {
        int dNumber  = mpSettings->value("device/device_number" , 0).toInt();

        setDeviceNumber(dNumber);
    }
    void loadManagerSetting()
    {
        QString company    = mpSettings->value("manager/company"   , "-").toString();
        QString mddepartment = mpSettings->value("manager/department", "-").toString();
        QString mdposition   = mpSettings->value("manager/position"  , "-").toString();
        QString mdname       = mpSettings->value("manager/name"      , "-").toString();
        QString wcdepartment = mpSettings->value("manager/wcdepartment", "-").toString();
        QString wcposition   = mpSettings->value("manager/wcposition"  , "-").toString();
        QString wcname       = mpSettings->value("manager/wcname"      , "-").toString();

        setMDManagerSetting(company, mddepartment, mdposition, mdname);
        setWCManagerSetting(company, wcdepartment, wcposition, wcname);
    }
    void loadMetalDetectorSetting()
    {
        QString limitCriteriaFe  =  mpSettings->value("metaldetector/limit_criteria_fe" , "2.5").toString();
        QString limitCriteriaSus =  mpSettings->value("metaldetector/limit_criteria_sus", "2.5").toString();
        QString haccp            =  mpSettings->value("metaldetector/haccp"             , "CCP - 2P").toString();
        QString checkupCycle     =  mpSettings->value("metaldetector/checkup_cycle"     , "매 운전시 마다").toString();

        setMetalDetectorSetting(haccp, checkupCycle);
    }

    void loadSignSetting()
    {
        bool isCheckWrite    = mpSettings->value("sign/write"   , true).toBool();
        bool isCheckReview   = mpSettings->value("sign/review"  , true).toBool();
        bool isCheckApproved = mpSettings->value("sign/approved", true).toBool();

        setSignSetting(isCheckWrite, isCheckReview, isCheckApproved);
    }
};

#endif // LOCALSETTINGSERVICE_H
