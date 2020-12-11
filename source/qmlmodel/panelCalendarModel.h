#ifndef PANELCALENDARMODEL_H
#define PANELCALENDARMODEL_H

#include <QObject>
#include <QDebug>

#include "source/history/def/filedef.h"
#include "source/service/dataloaderservice.h"
#include "source/service/localsettingservice.h"
#include "source/service/util/svcconnectutil.h"

class PanelCalendarModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int mYear        READ getYear );
    Q_PROPERTY(int mMonth       READ getMonth);
    Q_PROPERTY(int mDay         READ getDay  );


private:
    int mYear ;
    int mMonth;
    int mDay  ;

    int getYear (){ return mYear ; }
    int getMonth(){ return mMonth; }
    int getDay  (){ return mDay  ; }

    void setDate (int year, int month, int day)
    {
        if(mYear == year && mMonth == month && mDay == day) return;

        mYear  = year ;
        mMonth = month;
        mDay   = day  ;

        emit signalEventChangedDate();
    }

signals:
    void signalEventChangedDate ();
    void signalEventUpdate      ();

public slots:
    Q_INVOKABLE bool onCommandIsVaildDate(int year, int month, int day)
    {
        if(pDLoaderSvc->mIsLoading)
            return false;

        QString strDate = QString("%1-%2-%3").arg(QString::number(year).rightJustified(4,'0')).arg(QString::number(month).rightJustified(2,'0')).arg(QString::number(day).rightJustified(2,'0'));
        return QFile::exists(QString("%1/%2/%3-PS.txt").arg(FileDef::DATABASE_DIR()).arg(pLSettingSvc->mDeviceNumber).arg(strDate));
    }
    Q_INVOKABLE void onCommandSelectDate(int year, int month, int day)
    {
        QDate selDate(year, month, day);

        pLSettingSvc->setSelectDate(selDate);
    }
public slots:
    void onChangedSelectDate()
    {
        setDate(pLSettingSvc->mSelectedDate.year(), pLSettingSvc->mSelectedDate.month(), pLSettingSvc->mSelectedDate.day());
    }

    void onChangedIsLoading(bool value)
    {
        if(value == false)
            emit signalEventUpdate();
    }


public:
    explicit PanelCalendarModel(QObject *parent = nullptr):QObject(parent)
    {
        ENABLE_SLOT_LSETTING_CHANGED_SEL_DATE;
        ENABLE_SLOT_DLOAD_CHANGED_IS_LOADING;

        onChangedSelectDate();
        onChangedIsLoading(pDLoaderSvc->mIsLoading);
    }
};
#endif // PANELCALENDARMODEL_H
