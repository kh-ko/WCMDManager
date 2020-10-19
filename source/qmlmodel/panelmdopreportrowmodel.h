#ifndef PANELMDOPREPORTROWMODEL_H
#define PANELMDOPREPORTROWMODEL_H

#include <QObject>
#include <QDebug>
#include "source/service/coreservice.h"

class PanelMDOPReportRowModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsRemoved  READ getIsRemoved NOTIFY signalEventChangedIsRemoved );
    Q_PROPERTY(QString mPno        READ getPno       NOTIFY signalEventChangedPno       );
    Q_PROPERTY(QString mPName      READ getPName     NOTIFY signalEventChangedPName     );
    Q_PROPERTY(QString mTotalCnt   READ getTotalCnt  NOTIFY signalEventChangedTotalCnt  );
    Q_PROPERTY(QString mNGCnt      READ getNGCnt     NOTIFY signalEventChangedNGCnt     );
    Q_PROPERTY(QString mNGRate     READ getNGRate    NOTIFY signalEventChangedNGRate    );
    Q_PROPERTY(QString mLimitFe    READ getLimitFe   NOTIFY signalEventChangedLimitFe   );
    Q_PROPERTY(QString mLimitSus   READ getLimitSus  NOTIFY signalEventChangedLimitSus  );

public:

    bool    mIsRemoved  = true ;
    QString mPno        = ""    ;
    QString mPName      = ""    ;
    QString mTotalCnt   = ""    ;
    QString mNGCnt      = ""    ;
    QString mNGRate     = ""    ;
    QString mLimitFe    = "";
    QString mLimitSus   = "";

    bool    getIsRemoved(){ return mIsRemoved; }
    QString getPno      (){ return mPno      ; }
    QString getPName    (){ return mPName    ; }
    QString getTotalCnt (){ return mTotalCnt ; }
    QString getNGCnt    (){ return mNGCnt    ; }
    QString getNGRate   (){ return mNGRate   ; }
    QString getLimitFe  (){ return mLimitFe  ; }
    QString getLimitSus (){ return mLimitSus ; }

    void setIsRemoved(bool    value){ if( mIsRemoved == value ) return; mIsRemoved = value; emit signalEventChangedIsRemoved(mIsRemoved); }
    void setPno      (QString value){ if( mPno       == value ) return; mPno       = value; emit signalEventChangedPno      (mPno      ); }
    void setPName    (QString value){ if( mPName     == value ) return; mPName     = value; emit signalEventChangedPName    (mPName    ); }
    void setTotalCnt (QString value){ if( mTotalCnt  == value ) return; mTotalCnt  = value; emit signalEventChangedTotalCnt (mTotalCnt ); }
    void setNGCnt    (QString value){ if( mNGCnt     == value ) return; mNGCnt     = value; emit signalEventChangedNGCnt    (mNGCnt    ); }
    void setNGRate   (QString value){ if( mNGRate    == value ) return; mNGRate    = value; emit signalEventChangedNGRate   (mNGRate   ); }
    void setLimitFe  (QString value){ if(mLimitFe    == value ) return; mLimitFe   = value; emit signalEventChangedLimitFe  (mLimitFe  ); }
    void setLimitSus (QString value){ if(mLimitSus   == value ) return; mLimitSus  = value; emit signalEventChangedLimitSus (mLimitSus ); }

public slots:
    Q_INVOKABLE void onCommandSetIsRemoved(bool    value){ setIsRemoved(value); }
    Q_INVOKABLE void onCommandSetPno      (QString value){ setPno      (value); }
    Q_INVOKABLE void onCommandSetPName    (QString value){ setPName    (value); }
    Q_INVOKABLE void onCommandSetTotalCnt (QString value){ setTotalCnt (value); }
    Q_INVOKABLE void onCommandSetNGCnt    (QString value){ setNGCnt    (value); }
    Q_INVOKABLE void onCommandSetNGRate   (QString value){ setNGRate   (value); }
    Q_INVOKABLE void onCommandSetLimitFe  (QString value){ setLimitFe  (value); }
    Q_INVOKABLE void onCommandSetLimitSus (QString value){ setLimitSus (value); }

signals:
    void signalEventChangedIsRemoved (bool    value);
    void signalEventChangedPno       (QString value);
    void signalEventChangedPName     (QString value);
    void signalEventChangedTotalCnt  (QString value);
    void signalEventChangedNGCnt     (QString value);
    void signalEventChangedNGRate    (QString value);
    void signalEventChangedLimitFe   (QString value);
    void signalEventChangedLimitSus  (QString value);

public:
    explicit PanelMDOPReportRowModel(QObject *parent = nullptr):QObject(parent)
    {
    }

    PanelMDOPReportRowModel(QString value, QObject *parent = nullptr):QObject(parent)
    {

    }
};
#endif // PANELMDOPREPORTROWMODEL_H
