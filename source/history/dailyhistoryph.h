#ifndef DAILYHISTORYPH_H
#define DAILYHISTORYPH_H

#include <QObject>
#include <QDebug>
#include "source/history/dto/enum/enumdef.h"
#include "source/history/dto/pdsettingdto.h"
#include "source/history/fileutil/filereaderex.h"

class DailyHistoryPH : public QObject
{
    Q_OBJECT

public:
    int               mDevNum = 0;
    QString           mStrDate ;
    QString           mSrcPath ;
    QThread         * mpReadThread = nullptr;
    FileReaderEx    * mpFileReader = nullptr;

    QList<PDSettingDto> mPHList;
    QList<PDSettingDto> mPDList;

    explicit DailyHistoryPH(QObject *parent = nullptr) : QObject(parent)
    {

    }
    ~DailyHistoryPH()
    {
        close();
    }

    void load(int devNum, QString srcPath, QString strDate)
    {
        mDevNum  = devNum ;
        mStrDate = strDate;
        mSrcPath = srcPath;

        open();
        read();
    }

    void clear()
    {
        close();
        mPHList.clear();
        mPDList.clear();
    }

    PDSettingDto findSettingDto(quint64 pdSeq, int pdHisIdx)
    {
        PDSettingDto setting;

        if(mPHList.size() > pdHisIdx && mPHList[pdHisIdx].mSeq == pdSeq)
        {
            return mPHList[pdHisIdx];
        }

        for(int i = mPHList.size() - 1; i > -1; i--)
        {
            if(mPHList[i].mSeq == pdSeq)
                return mPHList[i];
        }

        return setting;
    }

    PDSettingDto findSettingDto(quint64 pdSeq)
    {
        PDSettingDto dummy;

        foreach(PDSettingDto setting, mPDList)
        {
            if(setting.mSeq == pdSeq)
                return setting;
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
            PDSettingDto dto;
            if(dto.setValue(line) == false)
                continue;

            addPDSetting(dto);
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

        emit signalCommandOpen(mSrcPath, QString("%1-PH.txt").arg(mStrDate));
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

    void addPDSetting(PDSettingDto setting)
    {
        bool isFound = false;

        for(int i = 0; i < mPDList.size(); i ++)
        {
            PDSettingDto old = mPDList[i];

            if(setting.mSeq == old.mSeq)
            {
                isFound = true;
                mPDList.replace(i, setting);
                break;
            }
        }

        if(!isFound)
            mPDList.append(setting);

        mPHList.append(setting);
    }

};

#endif // DAILYHISTORYPH_H
