#ifndef PANELWEIGHTMANAGEMENTINFOMODEL_H
#define PANELWEIGHTMANAGEMENTINFOMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/util/svcconnectutil.h"
#include "source/service/devinfoservice.h"
#include "source/service/coreservice.h"

class PanelWeightManagementInfoModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mDNum           READ getDNum           NOTIFY signalEventChangedDNum          );
    Q_PROPERTY(QString mDName          READ getDName          NOTIFY signalEventChangedDName         );
    Q_PROPERTY(QString mCompany        READ getCompany        NOTIFY signalEventChangedCompany       );
    Q_PROPERTY(QString mDepartment     READ getDepartment     NOTIFY signalEventChangedDepartment    );
    Q_PROPERTY(QString mPosition       READ getPosition       NOTIFY signalEventChangedPosition      );
    Q_PROPERTY(QString mName           READ getName           NOTIFY signalEventChangedName          );

private:
    CoreService * mpCoreService;

    int     mDNum          ;
    QString mDName         ;
    QString mCompany       ;
    QString mDepartment    ;
    QString mPosition      ;
    QString mName          ;

    int     getDNum          (){ return mDNum          ; }
    QString getDName         (){ return mDName         ; }
    QString getCompany       (){ return mCompany       ; }
    QString getDepartment    (){ return mDepartment    ; }
    QString getPosition      (){ return mPosition      ; }
    QString getName          (){ return mName          ; }

    void setDNum          (int     value){ if(mDNum           == value) return; mDNum           = value; emit signalEventChangedDNum          (mDNum          );}
    void setDName         (QString value){ if(mDName          == value) return; mDName          = value; emit signalEventChangedDName         (mDName         );}
    void setCompany       (QString value){ if(mCompany        == value) return; mCompany        = value; emit signalEventChangedCompany       (mCompany       );}
    void setDepartment    (QString value){ if(mDepartment     == value) return; mDepartment     = value; emit signalEventChangedDepartment    (mDepartment    );}
    void setPosition      (QString value){ if(mPosition       == value) return; mPosition       = value; emit signalEventChangedPosition      (mPosition      );}
    void setName          (QString value){ if(mName           == value) return; mName           = value; emit signalEventChangedName          (mName          );}

signals:
    void signalEventChangedDNum          (int     value);
    void signalEventChangedDName         (QString value);
    void signalEventChangedCompany       (QString value);
    void signalEventChangedDepartment    (QString value);
    void signalEventChangedPosition      (QString value);
    void signalEventChangedName          (QString value);

public slots:
    Q_INVOKABLE int     onCommandDlistRefresh()   { pDevInfoSvc->refreshList();         }
    Q_INVOKABLE int     onCommandGetDListSize(){ return pDevInfoSvc->mDevList.size();}
    Q_INVOKABLE int     onCommandGetDNum(int idx){ return pDevInfoSvc->mDevList[idx].mNumber;}
    Q_INVOKABLE QString onCommandGetDName(int idx){ return pDevInfoSvc->mDevList[idx].mName;}
    Q_INVOKABLE void    onCommandSetManagementInfo(QString dNum, QString dName, QString company, QString department, QString position, QString name)
    {
        pDevInfoSvc->editDevInfo(dNum.toInt(), dName);
        pLSettingSvc->setDeviceNumber(dNum.toInt());
        pLSettingSvc->setWCManagerSetting(company, department, position, name);
    }
public slots:
    void onChangedDeviceNumber()
    {
        setDNum(pLSettingSvc->mDeviceNumber);

        pDevInfoSvc->refreshList();
        DevInfoDto devInfo = pDevInfoSvc->findDevInfo(pLSettingSvc->mDeviceNumber);
        setDName(devInfo.mName);
    }
    void onChangedManagerSetting()
    {
        setCompany   (pLSettingSvc->mManagerSettingModel.mCompany     );
        setDepartment(pLSettingSvc->mManagerSettingModel.mWCDepartment);
        setPosition  (pLSettingSvc->mManagerSettingModel.mWCPosition  );
        setName      (pLSettingSvc->mManagerSettingModel.mWCName      );
    }

public:
    explicit PanelWeightManagementInfoModel(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[PanelWeightManagementInfoModel] create instance";

        ENABLE_SLOT_LSETTING_CHANGED_MAN_SETTING;
        ENABLE_SLOT_LSETTING_CHANGED_SEL_DEV;

        onChangedDeviceNumber        ();
        onChangedManagerSetting      ();
    }
};
#endif // PANELWEIGHTMANAGEMENTINFOMODEL_H
