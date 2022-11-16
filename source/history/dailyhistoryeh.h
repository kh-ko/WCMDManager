#ifndef DAILYHISTORYEH_H
#define DAILYHISTORYEH_H

#include <QObject>
#include <QDebug>
#include "source/history/dto/enum/enumdef.h"
#include "source/history/dto/eventdto.h"
#include "source/history/dto/pdtimesdto.h"
#include "source/history/dto/pdcheckupdto.h"
#include "source/history/dto/pdwcstatsdto.h"
#include "source/history/dailyhistoryph.h"
#include "source/history/dailyhistoryps.h"
#include "source/history/fileutil/filereaderex.h"

#define INVAILD_PD_SEQ 0


class DailyHistoryEH : public QObject
{
    Q_OBJECT

public:
    int               mDevNum = 0;
    QString           mStrDate ;
    QString           mSrcPath ;
    QThread         * mpReadThread = nullptr;
    FileReaderEx    * mpFileReader = nullptr;

    DailyHistoryPS   * mpPS = nullptr;
    DailyHistoryPH   * mpPH = nullptr;

    //QList<EventDto>     mEventList;
    QList<PDCheckupDto> mCheckupEventList;
    QList<EventDto>     mMDFailList;
    QList<PDTimeDto>    mPDTimeList;
    QList<PDWCStatsDto> mPDWCStatsList;
    QList<EventDto>     mWCEventList;

    explicit DailyHistoryEH(QObject *parent = nullptr) : QObject(parent)
    {

    }
    ~DailyHistoryEH()
    {
        close();
    }

    void clear()
    {
        close();
        mpRecentPDWCStats = nullptr;

        //mEventList.clear();
        mCheckupEventList.clear();
        mMDFailList.clear();
        mPDWCStatsList.clear();
        mWCEventList.clear();
    }

    void load(int devNum, QString srcPath, QString strDate, DailyHistoryPH * pPH, DailyHistoryPS * pPS)
    {
        mDevNum  = devNum ;
        mStrDate = strDate;
        mSrcPath = srcPath;

        mpPS = pPS;
        mpPH = pPH;

        open();
        read();
    }

    PDSettingDto findSettingDto(quint64 pdSeq, int pdHisIdx)
    {
        PDSettingDto setting;
        PDStatsDto   stats;
        setting = mpPH->findSettingDto(pdSeq, pdHisIdx);

        if(setting.mSeq != 0)
            return setting;

        qDebug() << "[DailyHistoryEH::findSettingDto] can not found pd setting : date = "<< mStrDate << ", pdSeq = " << pdSeq << ", hisIdx = " << pdHisIdx;

        stats = mpPS->findStatsDto(pdSeq);

        setting.mSeq        = stats.mSeq ;
        setting.mProductNum = stats.mNum ;
        setting.mName       = stats.mName;

        return setting;
    }

    PDWCStatsDto findPDWCStatsDto(quint64 pdSeq)
    {
        PDWCStatsDto dummy;

        for(int i = 0; i <mPDWCStatsList.size(); i++)
        {
            if(mPDWCStatsList[i].mSeq == pdSeq)
                return mPDWCStatsList[i];
        }

        return dummy;
    }

signals:
    void signalEventLoadCompleted(int err);

    void signalCommandReadMultiLine(int lineCnt);
    void signalCommandOpen(QString path, QString fileName);

private slots:
    void onReaded(QStringList lines)
    {

        foreach(QString line, lines)
        {
            EventDto dto;
            if(dto.setValue(line) == false)
                continue;


//            if((mRecentPDSeq != dto.mPDSeq && mRecentPDSeq != INVAILD_PD_SEQ && dto.mPDSeq != INVAILD_PD_SEQ) || dto.isRunEvent() || dto.isStopEvent() || dto.isStartEvent() || dto.isExitEvent())
//            {
//                if(mRecentPDSeq != INVAILD_PD_SEQ)
//                    addPDTime(mRecentPDSeq, dto.mDateTime.toMSecsSinceEpoch() - mRunTime);
//                mRecentPDSeq = INVAILD_PD_SEQ;
//            }

//            if(dto.mPDSeq != INVAILD_PD_SEQ)
//            {
//                if(mRecentPDSeq == INVAILD_PD_SEQ)
//                {
//                    mRunTime = dto.mDateTime.toMSecsSinceEpoch();
//                }
//                mRecentPDSeq = dto.mPDSeq;
//                mStopTime = dto.mDateTime.toMSecsSinceEpoch();

//            }
            //mEventList.append(dto);

            if(dto.isMetalCheckup())
            {
                PDCheckupDto checkupDto;
                PDSettingDto setting = findSettingDto(dto.mPDSeq, dto.mPDHisIdx);

                checkupDto.setValue(dto, setting.mProductNum, setting.mName);
                mCheckupEventList.append(checkupDto);
            }

            if(dto.isMetalDetectEvent())
            {
                mMDFailList.append(dto);
            }

            if(dto.isWCEvent())
            {
                if(mpRecentPDWCStats == nullptr || mpRecentPDWCStats->mSeq != dto.mPDSeq)
                {
                    PDWCStatsDto * pWCStats = findPDWCStatsPtr(dto.mPDSeq);

                    if(pWCStats == nullptr)
                    {
                        PDWCStatsDto wcStats;
                        wcStats.mSeq = dto.mPDSeq;
                        mPDWCStatsList.append(wcStats);
                        pWCStats = &mPDWCStatsList[mPDWCStatsList.size() - 1];
                    }

                    mpRecentPDWCStats = pWCStats;
                }

                mpRecentPDWCStats->addEvent(dto);
            }

            if(dto.isWCEvent() || dto.isCalibEvent())
            {
                mWCEventList.append(dto);
            }
        }

        if(lines.size() < mReadLineCnt)
        {
//            if(mRecentPDSeq != INVAILD_PD_SEQ)
//                addPDTime(mRecentPDSeq, mStopTime - mRunTime);
            loadComplete();
            return;
        }

        read();
    }

private:
    PDWCStatsDto     * mpRecentPDWCStats = nullptr;
    quint64             mRecentPDSeq = INVAILD_PD_SEQ;
    qint64              mRunTime = 0;
    qint64              mStopTime = 0;
    int mReadLineCnt = 1000;

    void loadComplete()
    {
        for(int i = 0; i < mPDWCStatsList.size(); i++)
        {
            mPDWCStatsList[i].calSDCV();
        }
        close();
        emit signalEventLoadCompleted(EnumDef::DAILY_ERR_NONE);
    }

    void open()
    {
        close();

        mpReadThread = new QThread;
        mpFileReader = new FileReaderEx;

        mpFileReader->moveToThread(mpReadThread);
        mpReadThread->start();

        connect(mpReadThread, &QThread::finished, mpFileReader, &QObject::deleteLater);
        connect(this, SIGNAL(signalCommandOpen(QString, QString)), mpFileReader, SLOT(onCommandOpen(QString, QString)));
        connect(this, SIGNAL(signalCommandReadMultiLine(int)), mpFileReader, SLOT(onCommandReadMultiLine(int)));
        connect(mpFileReader, SIGNAL(signalEventReadMultiLine(QStringList)), this, SLOT(onReaded(QStringList)));

        emit signalCommandOpen(mSrcPath, QString("%1-EH.txt").arg(mStrDate));
    }

    void close()
    {
        if(mpFileReader != nullptr)
        {
            disconnect(mpFileReader, nullptr, nullptr, nullptr);
            mpFileReader = nullptr;
        }

        if(mpReadThread != nullptr)
        {
            if(mpReadThread->isRunning())
            {
                mpReadThread->quit();
                mpReadThread->wait();
            }

            mpReadThread->deleteLater();
            mpReadThread = nullptr;
        }
    }

    void read()
    {
        emit signalCommandReadMultiLine(mReadLineCnt);
    }

    PDWCStatsDto * findPDWCStatsPtr(quint64 pdSeq)
    {
        for(int i = 0; i <mPDWCStatsList.size(); i++)
        {
            if(mPDWCStatsList[i].mSeq == pdSeq)
                return &mPDWCStatsList[i];
        }
        return nullptr;
    }

    PDTimeDto * findPDTimePtr(quint64 pdSeq)
    {
        for(int i = 0; i <mPDTimeList.size(); i++)
        {
            if(mPDTimeList[i].mSeq == pdSeq)
                return &mPDTimeList[i];
        }
        return nullptr;
    }
    void addPDTime(quint64 pdSeq, qint64 time)
    {
        PDTimeDto * timeDto = findPDTimePtr(pdSeq);

        if(timeDto == nullptr)
        {
            PDTimeDto newTimeDto;

            newTimeDto.mSeq = pdSeq;
            newTimeDto.mTime = time;
            mPDTimeList.append(newTimeDto);
        }
        else
        {
            timeDto->mTime = timeDto->mTime + time;
        }
    }
};
#endif // DAILYHISTORYEH_H
