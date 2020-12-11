#ifndef MONTHLYSTATSHISTORY_H
#define MONTHLYSTATSHISTORY_H

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include "source/history/def/datetimeform.h"
#include "source/history/dailyhistoryps.h"

class MonthlyStatsHistory : public QObject
{
    Q_OBJECT

public:
    int               mDevNum = 0;
    QString           mSrcPath ;

    QDate             mDate ;
    int               mProcDayIdx = 0;
    QList<PDStatsDto> mPDList;
    DailyHistoryPS    mDayList[31];

    explicit MonthlyStatsHistory(QObject *parent = nullptr) : QObject(parent)
    {

    }
    ~MonthlyStatsHistory()
    {
        close();
    }

    void load(int devNum, QString srcPath, QDate date)
    {
        qDebug() << "[MonthlyStatsHistory::load]" << date.toString(DATE_FILE_NAME_FMT);

        close();

        open();

        mProcDayIdx = 0;
        mDevNum  = devNum ;
        mDate.setDate(date.year(), date.month(), mProcDayIdx + 1);
        mSrcPath = srcPath;

        mDayList[mProcDayIdx].load(devNum, srcPath, QString("%1").arg(mDate.toString("yyyy-MM-dd")));
    }

    void clear()
    {
        close();
        mPDList.clear();
    }

    PDStatsDto findStatsDto(quint64 pdSeq)
    {
        PDStatsDto stats;

        foreach(PDStatsDto stats, mPDList)
        {
            if(stats.mSeq == pdSeq)
            {
                return stats;
            }
        }

        return stats;
    }

    bool existDay(int day)
    {
        if(day > 31)
            return false;

        if(mDayList[day - 1].mPSList.size() < 1)
            return false;

        return true;
    }

signals:
    void signalEventLoadCompleted();

private slots:
    void onLoaded(int err)
    {
        foreach(PDStatsDto dayStats, mDayList[mProcDayIdx].mPSList)
        {
            PDStatsDto monthStats = findStatsDto(dayStats.mSeq);

            monthStats.mSeq                =  dayStats.mSeq               ;
            monthStats.mNum                =  dayStats.mNum               ;
            monthStats.mName               =  dayStats.mName              ;
            monthStats.mWCOCnt             += dayStats.mWCOCnt            ;
            monthStats.mWCOWCnt            += dayStats.mWCOWCnt           ;
            monthStats.mWCNorCnt           += dayStats.mWCNorCnt          ;
            monthStats.mWCUCnt             += dayStats.mWCUCnt            ;
            monthStats.mWCUWCnt            += dayStats.mWCUWCnt           ;
            monthStats.mWCEtcCnt           += dayStats.mWCEtcCnt          ;
            monthStats.mWCMDCnt            += dayStats.mWCMDCnt           ;
            monthStats.mMDPassCnt          += dayStats.mMDPassCnt         ;
            monthStats.mMDFailCnt          += dayStats.mMDFailCnt         ;
            monthStats.mWCTotalCnt         += dayStats.mWCTotalCnt        ;
            monthStats.mMDTotalCnt         += dayStats.mMDTotalCnt        ;

            addStatsDto(monthStats);
        }

        mProcDayIdx++;

        if(mProcDayIdx >= 31 || mDate.setDate(mDate.year(), mDate.month(), mProcDayIdx + 1) == false)
        {
            emit signalEventLoadCompleted();
            return;
        }

        mDayList[mProcDayIdx].load(mDevNum, mSrcPath, QString("%1").arg(mDate.toString("yyyy-MM-dd")));
    }

private:
    void open()
    {
        for(int i = 0; i < 31; i ++)
        {
            connect(&mDayList[i], SIGNAL(signalEventLoadCompleted(int)), this, SLOT(onLoaded(int)));
        }
    }
    void close()
    {
        for(int i = 0; i < 31; i ++)
        {
            disconnect(&mDayList[i], SIGNAL(signalEventLoadCompleted(int)), this, SLOT(onLoaded(int)));
            mDayList[i].clear();
        }
    }

    void addStatsDto(PDStatsDto stats)
    {
        for(int i = 0; i < mPDList.size(); i++)
        {
            if(stats.mSeq == mPDList[i].mSeq)
            {
                mPDList.replace(i, stats);
                return;
            }
        }

        mPDList.append(stats);
    }
};
#endif // MONTHLYSTATSHISTORY_H
