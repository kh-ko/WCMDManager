#ifndef DAILYHISTORY_H
#define DAILYHISTORY_H

#include <QObject>
#include <QDebug>
#include "source/history/dto/enum/enumdef.h"
#include "source/history/dailyhistoryeh.h"
#include "source/history/dailyhistoryph.h"
#include "source/history/dailyhistoryps.h"

class DailyHistory : public QObject
{
    Q_OBJECT

public:

    int               mDevNum = 0;
    QString           mStrDate ;
    QString           mSrcPath ;

    DailyHistoryEH    mEH;
    DailyHistoryPH    mPH;
    DailyHistoryPS    mPS;

    explicit DailyHistory(QObject *parent = nullptr) : QObject(parent)
    {
        connect(&mEH, SIGNAL(signalEventLoadCompleted(int)), this, SLOT(loadedEH(int)));
        connect(&mPH, SIGNAL(signalEventLoadCompleted(int)), this, SLOT(loadedPH(int)));
        connect(&mPS, SIGNAL(signalEventLoadCompleted(int)), this, SLOT(loadedPS(int)));
    }
    ~DailyHistory()
    {
    }

    void load(int devNum, QString srcPath, QString strDate)
    {
        mDevNum  = devNum ;
        mStrDate = strDate;
        mSrcPath = srcPath;

        qDebug() << "[debug]load : size = " << mPS.mPSList.size();

        mPH.load(mDevNum, mSrcPath, mStrDate);
    }

    void clear()
    {
        qDebug() << "[debug] clear";
        mEH.clear();
        mPH.clear();
        mPS.clear();
    }

signals:
    void signalEventLoadCompleted(int err);

private slots:
    void loadedPH(int err)
    {
        qDebug() << "[debug]loadedPH : size = " << mPS.mPSList.size();
        mPS.load(mDevNum, mSrcPath, mStrDate);
    }
    void loadedPS(int err)
    {
        qDebug() << "[debug]loadedPS : size = " << mPS.mPSList.size();
        mEH.load(mDevNum, mSrcPath, mStrDate, &mPH, &mPS);
    }
    void loadedEH(int err)
    {
        loadComplete(EnumDef::DAILY_ERR_NONE);
    }

private:
    void loadComplete(EnumDef::eDailyErr err)
    {
        emit signalEventLoadCompleted((int)err);
    }
};
#endif // DAILYHISTORY_H
