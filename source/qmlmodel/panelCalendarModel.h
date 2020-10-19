#ifndef PANELCALENDARMODEL_H
#define PANELCALENDARMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"

class PanelCalendarModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int mYear        READ getYear );
    Q_PROPERTY(int mMonth       READ getMonth);
    Q_PROPERTY(int mDay         READ getDay  );


private:
    CoreService * mpCoreService;

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
        if(mpCoreService->mDataLoader.mIsLoading)
            return false;

        int calDateNumber = year * 10000 + month * 100 + day;

        for(int i = 0; i < mpCoreService->mDataLoader.mAllFileList.size(); i++)
        {
            QString date = mpCoreService->mDataLoader.mAllFileList.at(i).split(".")[0];

            if(date.contains("-") == false)
                continue;

            QStringList temp = date.split("-");

            if(temp.size() != 4)
                continue;

            int dateNumber  = temp[0].toInt() * 10000 + temp[1].toInt() * 100 + temp[2].toInt();

            if(dateNumber == calDateNumber)
                return true;

            if(calDateNumber < dateNumber)
                break;
        }

        return false;
    }
    Q_INVOKABLE void onCommandSelectDate(int year, int month, int day)
    {
        mpCoreService->mLSettingService.setSelectDate(year, month, day);
    }
public slots:
    void onSignalEventChangedSelectDate()
    {
        setDate(mpCoreService->mLSettingService.mSelectedYear, mpCoreService->mLSettingService.mSelectedMonth, mpCoreService->mLSettingService.mSelectedDay);
    }

    void onSignalEventChangedIsLoading(bool value)
    {
        if(value == false)
            emit signalEventUpdate();
    }


public:
    explicit PanelCalendarModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        connect(&mpCoreService->mLSettingService, SIGNAL(signalEventChangedSelectDate(    )), this, SLOT(onSignalEventChangedSelectDate(    )));
        connect(&mpCoreService->mDataLoader     , SIGNAL(signalEventChangedIsLoading (bool)), this, SLOT(onSignalEventChangedIsLoading (bool)));

        onSignalEventChangedSelectDate();
        onSignalEventChangedIsLoading(mpCoreService->mDataLoader.mIsLoading);
    }
};
#endif // PANELCALENDARMODEL_H
