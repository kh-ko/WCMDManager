#ifndef MANAGERMODEL_H
#define MANAGERMODEL_H

#include <QObject>

class ManagerSettingModel : QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mCompany      READ getCompany      NOTIFY signalEventChangedCompany     )
    Q_PROPERTY(QString mMDDepartment READ getMDDepartment NOTIFY signalEventChangedMDDepartment)
    Q_PROPERTY(QString mMDPosition   READ getMDPosition   NOTIFY signalEventChangedMDPosition  )
    Q_PROPERTY(QString mMDName       READ getMDName       NOTIFY signalEventChangedMDName      )
    Q_PROPERTY(QString mWCDepartment READ getWCDepartment NOTIFY signalEventChangedWCDepartment)
    Q_PROPERTY(QString mWCPosition   READ getWCPosition   NOTIFY signalEventChangedWCPosition  )
    Q_PROPERTY(QString mWCName       READ getWCName       NOTIFY signalEventChangedWCName      )

public:
    QString mCompany      ;
    QString mMDDepartment ;
    QString mMDPosition   ;
    QString mMDName       ;
    QString mWCDepartment ;
    QString mWCPosition   ;
    QString mWCName       ;

    QString getCompany     (){return mCompany     ;}
    QString getMDDepartment(){return mMDDepartment;}
    QString getMDPosition  (){return mMDPosition  ;}
    QString getMDName      (){return mMDName      ;}
    QString getWCDepartment(){return mWCDepartment;}
    QString getWCPosition  (){return mWCPosition  ;}
    QString getWCName      (){return mWCName      ;}

    void setCompany     (QString value){ if( mCompany      == value ) return; mCompany      = value; emit signalEventChangedCompany     (mCompany     ); }
    void setMDDepartment(QString value){ if( mMDDepartment == value ) return; mMDDepartment = value; emit signalEventChangedMDDepartment(mMDDepartment); }
    void setMDPosition  (QString value){ if( mMDPosition   == value ) return; mMDPosition   = value; emit signalEventChangedMDPosition  (mMDPosition  ); }
    void setMDName      (QString value){ if( mMDName       == value ) return; mMDName       = value; emit signalEventChangedMDName      (mMDName      ); }
    void setWCDepartment(QString value){ if( mWCDepartment == value ) return; mWCDepartment = value; emit signalEventChangedWCDepartment(mWCDepartment); }
    void setWCPosition  (QString value){ if( mWCPosition   == value ) return; mWCPosition   = value; emit signalEventChangedWCPosition  (mWCPosition  ); }
    void setWCName      (QString value){ if( mWCName       == value ) return; mWCName       = value; emit signalEventChangedWCName      (mWCName      ); }


signals:
    void signalEventChangedCompany     (QString value);
    void signalEventChangedMDDepartment(QString value);
    void signalEventChangedMDPosition  (QString value);
    void signalEventChangedMDName      (QString value);
    void signalEventChangedWCDepartment(QString value);
    void signalEventChangedWCPosition  (QString value);
    void signalEventChangedWCName      (QString value);

public:
    explicit ManagerSettingModel(QObject *parent = nullptr):QObject(parent){}
    ManagerSettingModel(QString company, QString mdDepartment, QString mdPosition, QString mdName, QString wcDepartment, QString wcPosition, QString wcName,QObject *parent = nullptr):QObject(parent)
    {
        setCompany     (company     );
        setMDDepartment(mdDepartment);
        setMDPosition  (mdPosition  );
        setMDName      (mdName      );
        setWCDepartment(wcDepartment);
        setWCPosition  (wcPosition  );
        setWCName      (wcName      );
    }
    ManagerSettingModel& operator=(ManagerSettingModel other)
    {
        setCompany     (other.mCompany     );
        setMDDepartment(other.mMDDepartment);
        setMDPosition  (other.mMDPosition  );
        setMDName      (other.mMDName      );
        setWCDepartment(other.mWCDepartment);
        setWCPosition  (other.mWCPosition  );
        setWCName      (other.mWCName      );

        return *this;
    }
};
#endif // MANAGERMODEL_H
