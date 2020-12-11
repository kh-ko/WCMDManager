#ifndef DATALOADERSERVICE_H
#define DATALOADERSERVICE_H

#include <QObject>
#include "source/history/def/filedef.h"
#include "source/history/dailyhistory.h"
#include "source/history/monthlystatshistory.h"
#include "source/service/localsettingservice.h"
#include "source/service/util/svcconnectutil.h"

#define pDLoaderSvc DataLoaderService::getInstance()

class DataLoaderService : public QObject
{
    Q_OBJECT
public:
    static DataLoaderService * getInstance()
    {
        static DataLoaderService  *pSelf = nullptr;

        if(pSelf == nullptr)
        {
            pSelf = new DataLoaderService();
        }

        return pSelf;
    }

    bool                mIsRunning      = false;
    bool                mIsLoading      = false;
    int                 mDevNum                ;
    QDate               mDate                  ;
    DailyHistory        mDailyHis              ;
    MonthlyStatsHistory mMonthlyStatsHis       ;

    explicit DataLoaderService(QObject *parent = nullptr) : QObject(parent)
    {
        connect(&mDailyHis, SIGNAL(signalEventLoadCompleted(int)), this, SLOT(onDailyLoadComplete(int)));
        connect(&mMonthlyStatsHis, SIGNAL(signalEventLoadCompleted()), this, SLOT(onMonthlyStatsLoadComplete()));
    }

    ~DataLoaderService()
    {
        stop();
    }

    void start(int devNum, QDate date)
    {
        qDebug() << "[DataLoaderService::start]";

        mIsRunning = true;

        ENABLE_SLOT_LSETTING_CHANGED_SEL_DEV;
        ENABLE_SLOT_LSETTING_CHANGED_SEL_DATE;

        load(devNum, date);
    }

    void load(int devNum, QDate date)
    {
        if(mIsRunning == false)
            return;

        qDebug() << "[DataLoaderService::load]";

        mDailyHis.clear();
        mMonthlyStatsHis.clear();

        mDevNum = devNum;
        mDate = date;

        setIsLoading(true);
        mDailyHis.load(devNum, QString("%1/%2").arg(FileDef::DATABASE_DIR()).arg(devNum), date.toString(DATE_FILE_NAME_FMT));
    }

    void stop()
    {
        qDebug() << "[DataLoaderService::stop]";

        setIsLoading(false);

        mIsRunning = false;

        mDailyHis.clear();
        mMonthlyStatsHis.clear();
    }

signals:
    void signalEventLoadComplete();
    void signalEventChangedIsLoading(bool value);

public slots:
    void onDailyLoadComplete(int err)
    {
        qDebug() << "[DataLoaderService::onDailyLoadComplete]";
        qDebug() << "[debug]getListSize : size = " << pDLoaderSvc->mDailyHis.mPS.mPSList.size();

        mMonthlyStatsHis.load(mDevNum, QString("%1/%2").arg(FileDef::DATABASE_DIR()).arg(mDevNum), mDate);
    }

    void onMonthlyStatsLoadComplete()
    {
        qDebug() << "[DataLoaderService::onMonthlyStatsLoadComplete]";

        setIsLoading(false);
    }

    void onChangedSelectDate()
    {
        qDebug() << "[DataLoaderService::onChangedSelectDate]" << pLSettingSvc->mSelectedDate.toString(DATE_FILE_NAME_FMT);

        load(pLSettingSvc->mDeviceNumber, pLSettingSvc->mSelectedDate);
    }
    void onChangedDeviceNumber()
    {
        qDebug() << "[DataLoaderService::onChangedDeviceNumber]";

        load(pLSettingSvc->mDeviceNumber, pLSettingSvc->mSelectedDate);
    }

private:
    void setIsLoading(bool value)
    {
        if(mIsLoading == value)
            return;

        mIsLoading = value;

        emit signalEventChangedIsLoading(mIsLoading);
    }
};

#endif // DATALOADERSERVICE_H
