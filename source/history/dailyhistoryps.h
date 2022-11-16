#ifndef DAILYHISTORYPS_H
#define DAILYHISTORYPS_H

#include <QObject>
#include <QDebug>
#include "source/history/dto/enum/enumdef.h"
#include "source/history/dto/pdstatsdto.h"
#include "source/history/fileutil/filereaderex.h"

class DailyHistoryPS : public QObject
{
    Q_OBJECT

public:
    int               mDevNum = 0;
    QString           mStrDate ;
    QString           mSrcPath ;
    QThread         * mpReadThread = nullptr;
    FileReaderEx    * mpFileReader = nullptr;

    QList<PDStatsDto> mPSList;

    explicit DailyHistoryPS(QObject *parent = nullptr) : QObject(parent)
    {

    }
    ~DailyHistoryPS()
    {
        close();
    }

    void load(int devNum, QString srcPath, QString strDate)
    {
        qDebug() << "[DailyHistoryPS::load]" << strDate;

        mDevNum  = devNum ;
        mStrDate = strDate;
        mSrcPath = srcPath;

        open();
        read();
    }

    void clear()
    {
        close();
        mPSList.clear();
    }

    PDStatsDto findStatsDto(quint64 pdSeq)
    {
        PDStatsDto stats;

        foreach(PDStatsDto stats, mPSList)
        {
            if(stats.mSeq == pdSeq)
            {
                return stats;
            }
        }

        return stats;
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
            PDStatsDto dto;
            int insertIdx = 0;
            if(dto.setValue(line) == false)
                continue;

            for(insertIdx = 0; insertIdx < mPSList.size(); insertIdx ++)
            {
                if(mPSList[insertIdx].mNum > dto.mNum)
                    break;
            }
            mPSList.insert(insertIdx, dto);
        }

        if(lines.size() < mReadLineCnt)
        {
            loadComplete();
            return;
        }

        read();
    }

private:
    int mReadLineCnt = 1000;

    void loadComplete()
    {
        close();
        emit signalEventLoadCompleted((int)EnumDef::DAILY_ERR_NONE);
    }

    void open()
    {
        qDebug() << "[DailyHistoryPS::open]";

        close();

        mpReadThread = new QThread;
        mpFileReader = new FileReaderEx;

        mpFileReader->moveToThread(mpReadThread);
        mpReadThread->start();

        connect(mpReadThread, &QThread::finished, mpFileReader, &QObject::deleteLater);
        connect(this, SIGNAL(signalCommandOpen(QString, QString)), mpFileReader, SLOT(onCommandOpen(QString, QString)));
        connect(this, SIGNAL(signalCommandReadMultiLine(int)), mpFileReader, SLOT(onCommandReadMultiLine(int)));
        connect(mpFileReader, SIGNAL(signalEventReadMultiLine(QStringList)), this, SLOT(onReaded(QStringList)));

        emit signalCommandOpen(mSrcPath, QString("%1-PS.txt").arg(mStrDate));
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

};
#endif // DAILYHISTORYPS_H
