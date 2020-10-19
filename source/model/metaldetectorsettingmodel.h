#ifndef METALDETECTORSETTINGMODEL_H
#define METALDETECTORSETTINGMODEL_H

#include <QObject>

class MetalDetectorSettingModel : QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mLimitCriteriaFe  READ getLimitCriteriaFe  NOTIFY signalEventChangedLimitCriteriaFe )
    Q_PROPERTY(QString mLimitCriteriaSus READ getLimitCriteriaSus NOTIFY signalEventChangedLimitCriteriaSus)
    Q_PROPERTY(QString mHACCP            READ getHACCP            NOTIFY signalEventChangedHACCP           )
    Q_PROPERTY(QString mCheckupCycle     READ getCheckupCycle     NOTIFY signalEventChangedCheckupCycle    )

public:
    QString mLimitCriteriaFe ;
    QString mLimitCriteriaSus;
    QString mHACCP           ;
    QString mCheckupCycle    ;

    QString getLimitCriteriaFe (){return mLimitCriteriaFe ; }
    QString getLimitCriteriaSus(){return mLimitCriteriaSus; }
    QString getHACCP           (){return mHACCP           ; }
    QString getCheckupCycle    (){return mCheckupCycle    ; }

    void setLimitCriteriaFe (QString value){ if(mLimitCriteriaFe  == value) return; mLimitCriteriaFe  = value; emit signalEventChangedLimitCriteriaFe (mLimitCriteriaFe ); }
    void setLimitCriteriaSus(QString value){ if(mLimitCriteriaSus == value) return; mLimitCriteriaSus = value; emit signalEventChangedLimitCriteriaSus(mLimitCriteriaSus); }
    void setHACCP           (QString value){ if(mHACCP            == value) return; mHACCP            = value; emit signalEventChangedHACCP           (mHACCP           ); }
    void setCheckupCycle    (QString value){ if(mCheckupCycle     == value) return; mCheckupCycle     = value; emit signalEventChangedHACCP           (mCheckupCycle    ); }

signals:
    void signalEventChangedLimitCriteriaFe (QString value);
    void signalEventChangedLimitCriteriaSus(QString value);
    void signalEventChangedHACCP           (QString value);
    void signalEventChangedCheckupCycle    (QString value);

public:
    explicit MetalDetectorSettingModel(QObject *parent = nullptr):QObject(parent){}
    MetalDetectorSettingModel(QString limitCriteriaFe, QString limitCriteriaSus, QString haccp, QString checkupCycle, QObject *parent = nullptr):QObject(parent)
    {
        setLimitCriteriaFe (limitCriteriaFe );
        setLimitCriteriaSus(limitCriteriaSus);
        setHACCP           (haccp           );
        setCheckupCycle    (checkupCycle    );
    }
    MetalDetectorSettingModel& operator=(MetalDetectorSettingModel other)
    {
        setLimitCriteriaFe (other.mLimitCriteriaFe );
        setLimitCriteriaSus(other.mLimitCriteriaSus);
        setHACCP           (other.mHACCP           );
        setCheckupCycle    (other.mCheckupCycle    );
        return *this;
    }
};

#endif // METALDETECTORSETTINGMODEL_H
