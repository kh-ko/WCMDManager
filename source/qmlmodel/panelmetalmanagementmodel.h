#ifndef PANELMETALMANAGEMENTMODEL_H
#define PANELMETALMANAGEMENTMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"
#include "source/service/devinfoservice.h"
#include "source/service/util/svcconnectutil.h"

class PanelMetalManagementInfoModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mDNum           READ getDNum           NOTIFY signalEventChangedDNum          );
    Q_PROPERTY(QString mDName          READ getDName          NOTIFY signalEventChangedDName         );
    Q_PROPERTY(QString mCompany        READ getCompany        NOTIFY signalEventChangedCompany       );
    Q_PROPERTY(QString mDepartment     READ getDepartment     NOTIFY signalEventChangedDepartment    );
    Q_PROPERTY(QString mPosition       READ getPosition       NOTIFY signalEventChangedPosition      );
    Q_PROPERTY(QString mName           READ getName           NOTIFY signalEventChangedName          );
    Q_PROPERTY(QString mLimCriteriaFe  READ getLimCriteriaFe  NOTIFY signalEventChangedLimCriteriaFe );
    Q_PROPERTY(QString mLimCriteriaSus READ getLimCriteriaSus NOTIFY signalEventChangedLimCriteriaSus);
    Q_PROPERTY(QString mHACCP          READ getHACCP          NOTIFY signalEventChangedHACCP         );
    Q_PROPERTY(QString mMDCheckupCycle READ getMDCheckupCycle NOTIFY signalEventChangedMDCheckupCycle);

private:
    CoreService * mpCoreService;

    int     mDNum          ;
    QString mDName         ;
    QString mCompany       ;
    QString mDepartment    ;
    QString mPosition      ;
    QString mName          ;
    QString mLimCriteriaFe ;
    QString mLimCriteriaSus;
    QString mHACCP         ;
    QString mMDCheckupCycle;

    int     getDNum          (){ return mDNum          ; }
    QString getDName         (){ return mDName         ; }
    QString getCompany       (){ return mCompany       ; }
    QString getDepartment    (){ return mDepartment    ; }
    QString getPosition      (){ return mPosition      ; }
    QString getName          (){ return mName          ; }
    QString getLimCriteriaFe (){ return mLimCriteriaFe ; }
    QString getLimCriteriaSus(){ return mLimCriteriaSus; }
    QString getHACCP         (){ return mHACCP         ; }
    QString getMDCheckupCycle(){ return mMDCheckupCycle; }

    void setDNum          (int     value){ if(mDNum           == value) return; mDNum           = value; emit signalEventChangedDNum          (mDNum          );}
    void setDName         (QString value){ if(mDName          == value) return; mDName          = value; emit signalEventChangedDName         (mDName         );}
    void setCompany       (QString value){ if(mCompany        == value) return; mCompany        = value; emit signalEventChangedCompany       (mCompany       );}
    void setDepartment    (QString value){ if(mDepartment     == value) return; mDepartment     = value; emit signalEventChangedDepartment    (mDepartment    );}
    void setPosition      (QString value){ if(mPosition       == value) return; mPosition       = value; emit signalEventChangedPosition      (mPosition      );}
    void setName          (QString value){ if(mName           == value) return; mName           = value; emit signalEventChangedName          (mName          );}
    void setLimCriteriaFe (QString value){ if(mLimCriteriaFe  == value) return; mLimCriteriaFe  = value; emit signalEventChangedLimCriteriaFe (mLimCriteriaFe );}
    void setLimCriteriaSus(QString value){ if(mLimCriteriaSus == value) return; mLimCriteriaSus = value; emit signalEventChangedLimCriteriaSus(mLimCriteriaSus);}
    void setHACCP         (QString value){ if(mHACCP          == value) return; mHACCP          = value; emit signalEventChangedHACCP         (mHACCP         );}
    void setMDCheckupCycle(QString value){ if(mMDCheckupCycle == value) return; mMDCheckupCycle = value; emit signalEventChangedMDCheckupCycle(mMDCheckupCycle);}

signals:
    void signalEventChangedDNum          (int     value);
    void signalEventChangedDName         (QString value);
    void signalEventChangedCompany       (QString value);
    void signalEventChangedDepartment    (QString value);
    void signalEventChangedPosition      (QString value);
    void signalEventChangedName          (QString value);
    void signalEventChangedLimCriteriaFe (QString value);
    void signalEventChangedLimCriteriaSus(QString value);
    void signalEventChangedHACCP         (QString value);
    void signalEventChangedMDCheckupCycle(QString value);

public slots:
    Q_INVOKABLE void    onCommandDlistRefresh()   { pDevInfoSvc->refreshList();         }
    Q_INVOKABLE int     onCommandGetDListSize()   { return pDevInfoSvc->mDevList.size();}
    Q_INVOKABLE int     onCommandGetDNum(int idx) { return pDevInfoSvc->mDevList[idx].mNumber;}
    Q_INVOKABLE QString onCommandGetDName(int idx){ return pDevInfoSvc->mDevList[idx].mName;}
    Q_INVOKABLE void    onCommandSetManagementInfo(QString dNum, QString dName, QString company, QString department, QString position, QString name, QString haccp, QString checkupcycle)
    {
        pDevInfoSvc->editDevInfo(dNum.toInt(), dName);
        pLSettingSvc->setDeviceNumber(dNum.toInt());
        pLSettingSvc->setMDManagerSetting(company, department, position, name);
        pLSettingSvc->setMetalDetectorSetting(haccp, checkupcycle);
    }
public slots:
    void onChangedDeviceNumber()
    {
        pDevInfoSvc->refreshList();

        setDNum(pLSettingSvc->mDeviceNumber);

        DevInfoDto devInfo = pDevInfoSvc->findDevInfo(pLSettingSvc->mDeviceNumber);
        setDName(devInfo.mName);
    }
    void onChangedManagerSetting()
    {
        setCompany   (pLSettingSvc->mManagerSettingModel.mCompany      );
        setDepartment(pLSettingSvc->mManagerSettingModel.mMDDepartment );
        setPosition  (pLSettingSvc->mManagerSettingModel.mMDPosition   );
        setName      (pLSettingSvc->mManagerSettingModel.mMDName       );
    }
    void onChangedMetalDetectorSetting()
    {
        setLimCriteriaFe (pLSettingSvc->mMDSettingModel.mLimitCriteriaFe );
        setLimCriteriaSus(pLSettingSvc->mMDSettingModel.mLimitCriteriaSus);
        setHACCP         (pLSettingSvc->mMDSettingModel.mHACCP           );
        setMDCheckupCycle(pLSettingSvc->mMDSettingModel.mCheckupCycle    );
    }

public:
    explicit PanelMetalManagementInfoModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        ENABLE_SLOT_LSETTING_CHANGED_SEL_DEV;
        ENABLE_SLOT_LSETTING_CHANGED_MAN_SETTING;
        ENABLE_SLOT_LSETTING_CHANGED_MD_SETTING;

        onChangedDeviceNumber        ();
        onChangedManagerSetting      ();
        onChangedMetalDetectorSetting();
    }
};

#endif // PANELMETALMANAGEMENTMODEL_H
