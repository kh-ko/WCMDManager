#ifndef PANELMDCHECKREPORTROWMODEL_H
#define PANELMDCHECKREPORTROWMODEL_H

#include <QObject>
#include <QDebug>
#include "source/service/coreservice.h"

class PanelMDCheckReportRowModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsRemoved  READ getIsRemoved NOTIFY signalEventChangedIsRemoved );
    Q_PROPERTY(QString mPno        READ getPno       NOTIFY signalEventChangedPno       );
    Q_PROPERTY(QString mPName      READ getPName     NOTIFY signalEventChangedPName     );
    Q_PROPERTY(QString mLimitFe    READ getLimitFe   NOTIFY signalEventChangedLimitFe   );
    Q_PROPERTY(QString mLimitSus   READ getLimitSus  NOTIFY signalEventChangedLimitSus  );
    Q_PROPERTY(QString mCheckTime  READ getCheckTime NOTIFY signalEventChangedCheckTime );
    Q_PROPERTY(QString mFe01       READ getFe01      NOTIFY signalEventChangedFe01      );
    Q_PROPERTY(QString mFe02       READ getFe02      NOTIFY signalEventChangedFe02      );
    Q_PROPERTY(QString mFe03       READ getFe03      NOTIFY signalEventChangedFe03      );
    Q_PROPERTY(QString mSus01      READ getSus01     NOTIFY signalEventChangedSus01     );
    Q_PROPERTY(QString mSus02      READ getSus02     NOTIFY signalEventChangedSus02     );
    Q_PROPERTY(QString mSus03      READ getSus03     NOTIFY signalEventChangedSus03     );
    Q_PROPERTY(QString mComment    READ getComment   NOTIFY signalEventChangedComment   );

public:

    bool    mIsRemoved  = true ;
    QString mPno        = ""   ;
    QString mPName      = ""   ;
    QString mLimitFe    = "";
    QString mLimitSus   = "";
    QString mCheckTime  = "";
    QString mFe01       = "";
    QString mFe02       = "";
    QString mFe03       = "";
    QString mSus01      = "";
    QString mSus02      = "";
    QString mSus03      = "";
    QString mComment    = "";

    bool    getIsRemoved(){ return mIsRemoved; }
    QString getPno      (){ return mPno      ; }
    QString getPName    (){ return mPName    ; }
    QString getLimitFe  (){ return mLimitFe  ; }
    QString getLimitSus (){ return mLimitSus ; }
    QString getCheckTime(){ return mCheckTime; }
    QString getFe01     (){ return mFe01     ; }
    QString getFe02     (){ return mFe02     ; }
    QString getFe03     (){ return mFe03     ; }
    QString getSus01    (){ return mSus01    ; }
    QString getSus02    (){ return mSus02    ; }
    QString getSus03    (){ return mSus03    ; }
    QString getComment  (){ return mComment  ; }

    void setIsRemoved(bool    value){ if( mIsRemoved == value ) return; mIsRemoved = value; emit signalEventChangedIsRemoved(mIsRemoved); }
    void setPno      (QString value){ if( mPno       == value ) return; mPno       = value; emit signalEventChangedPno      (mPno      ); }
    void setPName    (QString value){ if( mPName     == value ) return; mPName     = value; emit signalEventChangedPName    (mPName    ); }
    void setLimitFe  (QString value){ if(mLimitFe    == value ) return; mLimitFe   = value; emit signalEventChangedLimitFe  (mLimitFe  ); }
    void setLimitSus (QString value){ if(mLimitSus   == value ) return; mLimitSus  = value; emit signalEventChangedLimitSus (mLimitSus ); }
    void setCheckTime(QString value){ if(mCheckTime  == value ) return; mCheckTime = value; emit signalEventChangedCheckTime(mCheckTime); }
    void setFe01     (QString value){ if(mFe01       == value ) return; mFe01      = value; emit signalEventChangedFe01     (mFe01     ); }
    void setFe02     (QString value){ if(mFe02       == value ) return; mFe02      = value; emit signalEventChangedFe02     (mFe02     ); }
    void setFe03     (QString value){ if(mFe03       == value ) return; mFe03      = value; emit signalEventChangedFe03     (mFe03     ); }
    void setSus01    (QString value){ if(mSus01      == value ) return; mSus01     = value; emit signalEventChangedSus01    (mSus01    ); }
    void setSus02    (QString value){ if(mSus02      == value ) return; mSus02     = value; emit signalEventChangedSus02    (mSus02    ); }
    void setSus03    (QString value){ if(mSus03      == value ) return; mSus03     = value; emit signalEventChangedSus03    (mSus03    ); }
    void setComment  (QString value){ if(mComment    == value ) return; mComment   = value; emit signalEventChangedComment  (mComment  ); }

public slots:
    Q_INVOKABLE void onCommandSetIsRemoved(bool    value){ setIsRemoved(value); }
    Q_INVOKABLE void onCommandSetPno      (QString value){ setPno      (value); }
    Q_INVOKABLE void onCommandSetPName    (QString value){ setPName    (value); }
    Q_INVOKABLE void onCommandSetLimitFe  (QString value){ setLimitFe  (value); }
    Q_INVOKABLE void onCommandSetLimitSus (QString value){ setLimitSus (value); }
    Q_INVOKABLE void onCommandSetCheckTime(QString value){ setCheckTime(value); }
    Q_INVOKABLE void onCommandSetFe01     (QString value){ setFe01     (value); }
    Q_INVOKABLE void onCommandSetFe02     (QString value){ setFe02     (value); }
    Q_INVOKABLE void onCommandSetFe03     (QString value){ setFe03     (value); }
    Q_INVOKABLE void onCommandSetSus01    (QString value){ setSus01    (value); }
    Q_INVOKABLE void onCommandSetSus02    (QString value){ setSus02    (value); }
    Q_INVOKABLE void onCommandSetSus03    (QString value){ setSus03    (value); }
    Q_INVOKABLE void onCommandSetComment  (QString value){ setComment  (value); }

signals:
    void signalEventChangedIsRemoved (bool    value);
    void signalEventChangedPno       (QString value);
    void signalEventChangedPName     (QString value);
    void signalEventChangedLimitFe   (QString value);
    void signalEventChangedLimitSus  (QString value);
    void signalEventChangedCheckTime (QString value);
    void signalEventChangedFe01      (QString value);
    void signalEventChangedFe02      (QString value);
    void signalEventChangedFe03      (QString value);
    void signalEventChangedSus01     (QString value);
    void signalEventChangedSus02     (QString value);
    void signalEventChangedSus03     (QString value);
    void signalEventChangedComment   (QString value);

public:
    explicit PanelMDCheckReportRowModel(QObject *parent = nullptr):QObject(parent)
    {
    }

    PanelMDCheckReportRowModel(QString value, QObject *parent = nullptr):QObject(parent)
    {

    }
};
#endif // PANELMDCHECKREPORTROWMODEL_H
