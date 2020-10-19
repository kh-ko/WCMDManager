#ifndef MANAGERMODEL_H
#define MANAGERMODEL_H

#include <QObject>

class ManagerSettingModel : QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mCompany    READ getCompany    NOTIFY signalEventChangedCompany   )
    Q_PROPERTY(QString mDepartment READ getDepartment NOTIFY signalEventChangedDepartment)
    Q_PROPERTY(QString mPosition   READ getPosition   NOTIFY signalEventChangedPosition  )
    Q_PROPERTY(QString mName       READ getName       NOTIFY signalEventChangedName      )

public:
    QString mCompany    ;
    QString mDepartment ;
    QString mPosition   ;
    QString mName       ;

    QString getCompany   (){return mCompany   ;}
    QString getDepartment(){return mDepartment;}
    QString getPosition  (){return mPosition  ;}
    QString getName      (){return mName      ;}

    void setCompany   (QString value){ if( mCompany    == value ) return; mCompany    = value; emit signalEventChangedCompany   (mCompany   ); }
    void setDepartment(QString value){ if( mDepartment == value ) return; mDepartment = value; emit signalEventChangedDepartment(mDepartment); }
    void setPosition  (QString value){ if( mPosition   == value ) return; mPosition   = value; emit signalEventChangedPosition  (mPosition  ); }
    void setName      (QString value){ if( mName       == value ) return; mName       = value; emit signalEventChangedName      (mName      ); }

signals:
    void signalEventChangedCompany   (QString value);
    void signalEventChangedDepartment(QString value);
    void signalEventChangedPosition  (QString value);
    void signalEventChangedName      (QString value);

public:
    explicit ManagerSettingModel(QObject *parent = nullptr):QObject(parent){}
    ManagerSettingModel(QString company, QString department, QString position, QString name, QObject *parent = nullptr):QObject(parent)
    {
        setCompany   (company   );
        setDepartment(department);
        setPosition  (position  );
        setName      (name      );
    }
    ManagerSettingModel& operator=(ManagerSettingModel other)
    {
        setCompany   (other.mCompany   );
        setDepartment(other.mDepartment);
        setPosition  (other.mPosition  );
        setName      (other.mName      );

        return *this;
    }
};
#endif // MANAGERMODEL_H
