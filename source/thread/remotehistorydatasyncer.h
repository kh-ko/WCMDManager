#ifndef REMOTEHISTORYDATASYNCER_H
#define REMOTEHISTORYDATASYNCER_H

#include <QObject>
#include <QApplication>
#include <QTimer>
#include <QThread>
#include <QMap>
#include <QTcpSocket>
#include <QDataStream>

#include "source/globaldef/EnumDefine.h"
#include "source/thread/dto/devicesocketdto.h"
#include "source/util/filewriter.h"
#include "source/model/eventitemmodel.h"
#include "source/model/productsettingmodel.h"

class ReceiveDataSpliter : public QObject
{
    Q_OBJECT

public:
    QString                      mStrDate;
    QString                      mLastFileName;
    QByteArray                   mRemainEhData;
    QList<EventItemModel *>      mListCheckupEvent;
    QList<ProductSettingModel *> mListPSSetting;

    QString getCHFileName()
    {
        return QString("%1-CH.txt").arg(mStrDate);
    }

    bool compareDateByFileName(QString fileName)
    {
        int splitIdx = fileName.lastIndexOf("-");
        QString strDate = fileName.left(splitIdx);

        return (strDate == mStrDate);
    }

    bool setDateByFileName(QString fileName)
    {
        int splitIdx = fileName.lastIndexOf("-");
        QString strDate = fileName.left(splitIdx);

        if(mLastFileName != fileName)
        {
            mRemainEhData.clear();
        }

        mLastFileName = fileName;

        if(strDate != mStrDate)
        {
            clear();
            mStrDate = strDate;
            return true;
        }

        return false;
    }

    QString getCHStrRow(int idx)
    {
        if(idx >= mListCheckupEvent.size())
            return "";

        EventItemModel      * pEvent = mListCheckupEvent[idx];
        ProductSettingModel * pPS;

        if(pEvent->mProductHisIdx >= mListPSSetting.size())
            return "";

        pPS = mListPSSetting[pEvent->mProductHisIdx];

        QString ret = QString("PNO:%1,PNAME:%2,TIME:%3,FE01:%4,FE02:%5,FE03:%6,SUS01:%7,SUS02:%8,SUS03:%9\n")
                      .arg(pPS->mNo  )
                      .arg(pPS->mName)
                      .arg(pEvent->mDate.split(" ")[1].split(".")[0])
                      .arg((pEvent->mValue & (0x01 << 5)) != 0 ? 1 : 0)
                      .arg((pEvent->mValue & (0x01 << 4)) != 0 ? 1 : 0)
                      .arg((pEvent->mValue & (0x01 << 3)) != 0 ? 1 : 0)
                      .arg((pEvent->mValue & (0x01 << 2)) != 0 ? 1 : 0)
                      .arg((pEvent->mValue & (0x01 << 1)) != 0 ? 1 : 0)
                      .arg((pEvent->mValue & (0x01 << 0)) != 0 ? 1 : 0);

        return ret;
    }

    void addEhData(StPacket * data)
    {
        QByteArray procData;

        if(data->mSize == 0)
            return;

        mRemainEhData.append(data->mData, data->mSize);

        int lastIdx = mRemainEhData.lastIndexOf("\n");

        if(lastIdx + 1 > 0)
        {
            procData = mRemainEhData.left(lastIdx + 1);
        }

        if(lastIdx + 1 < mRemainEhData.size())
        {
            mRemainEhData = mRemainEhData.mid(lastIdx + 1);
        }
        else
        {
            mRemainEhData.clear();
        }

        if(procData.size() < 1)
            return;

        if(procData.contains("M CHECK") == false)
            return;

        QString strData = QString::fromUtf8(procData.data(), procData.size());

        QStringList valueList = strData.split("\n");

        for(int i = 0; i < valueList.size(); i ++)
        {
            QString temp = valueList[i];

            if(temp.contains("M CHECK"))
            {
                EventItemModel * event = new EventItemModel(this);
                event->setValue(temp);
                mListCheckupEvent.append(event);
            }
        }
    }

    void addPhData(StPacket * data)
    {
        QByteArray procData;

        if(data->mSize == 0)
            return;

        mRemainEhData.append(data->mData, data->mSize);

        int lastIdx = mRemainEhData.lastIndexOf("\n");

        if(lastIdx + 1 > 0)
        {
            procData = mRemainEhData.left(lastIdx + 1);
        }

        if(lastIdx + 1 < mRemainEhData.size())
        {
            mRemainEhData = mRemainEhData.mid(lastIdx + 1);
        }
        else
        {
            mRemainEhData.clear();
        }

        if(procData.size() < 1)
            return;

        QString strData = QString::fromUtf8(procData.data(), procData.size());

        QStringList valueList = strData.split("\n");

        for(int i = 0; i < valueList.size(); i ++)
        {
            QString temp = valueList[i];

            if(temp.size() < 1)
                continue;

            ProductSettingModel * setting = new ProductSettingModel(this);
            setting->setValue(temp);
            mListPSSetting.append(setting);
        }
    }

    void clear()
    {
        mRemainEhData.clear();

        for(int i = 0; i < mListCheckupEvent.size(); i ++)
        {
            delete mListCheckupEvent.at(i);
        }
        mListCheckupEvent.clear();

        for(int i = 0; i < mListPSSetting.size(); i ++)
        {
            delete mListPSSetting.at(i);
        }
        mListPSSetting.clear();
    }

    explicit ReceiveDataSpliter(QObject *parent = nullptr):QObject(parent){}
    ~ReceiveDataSpliter(){ clear();}

};

class RemoteHistoryDataSyncWoker : public QObject
{
    Q_OBJECT
public:
    QByteArray mRcvBuffer   ;
    QTimer     *mpTimer     = nullptr;
    QTcpSocket *mpSocket    = nullptr;
    int        mDeviceNum   = 0;
    QString    mIp          ;
    quint16    mPort = 10024;
    QString    mLastSyncDate;

    ReceiveDataSpliter mRDataSpliter;
    FileWriter         *mpFileWriter = nullptr;
    FileWriter         *mpCheckHistoryFileWriter = nullptr;
    QStringList        mFileNameList;
    QString            mFilePath;
    quint64            mTotalBytes = 0;
    quint64            mRcvBytes = 0;
public slots:
    void onCommandCancle();

    void onStart();
    void onReceive();
    void onSockError(QAbstractSocket::SocketError error);
    void onTimeout();

signals:
    void signalEventProgress(float value);
    void signalEventFinished(int error);

public:
    explicit RemoteHistoryDataSyncWoker(QObject *parent = nullptr);
    ~RemoteHistoryDataSyncWoker();

private:
    void open();
    void close(EnumDefine::RemoteSyncErrorType error);
    void procPacket(QByteArray data);
    void writeCheckHistory();
};

class RemoteHistoryDataSyncer : public QObject
{
    Q_OBJECT
public:
    RemoteHistoryDataSyncWoker * mpWoker = nullptr;
    QThread mThread;

    void sync(int deviceNum, QString ip, QString lastSyncDate, int deviceNo)
    {
        if(mpWoker != nullptr)
            return;

        mpWoker = new RemoteHistoryDataSyncWoker;
        mpWoker->mDeviceNum = deviceNum;
        mpWoker->mIp = ip;
        mpWoker->mLastSyncDate = lastSyncDate;
        mpWoker->mFilePath = QString("%1/database/%2").arg(QApplication::applicationDirPath()).arg(deviceNo);
        mpWoker->moveToThread(&mThread);

        connect(&mThread, &QThread::finished, mpWoker, &QObject::deleteLater);
        connect(&mThread, &QThread::started,  mpWoker, &RemoteHistoryDataSyncWoker::onStart);

        connect(this   , SIGNAL(signalCommandCancle (     )), mpWoker, SLOT(onCommandCancle      (     )));

        connect(mpWoker, SIGNAL(signalEventProgress (float)), this   , SLOT(onSignalEventProgress(float)));
        connect(mpWoker, SIGNAL(signalEventFinished (int  )), this   , SLOT(onSignalEventFinished(int  )));

        mThread.start();
    }

    void cancle()
    {
        if(mThread.isRunning())
        {
            emit signalCommandCancle();
        }
        else
        {
            emit signalEventFinished(EnumDefine::RemoteSyncErrorType::RSYNC_ERROR_CANCLE);
        }
    }

    explicit RemoteHistoryDataSyncer(QObject *parent = nullptr) : QObject(parent)
    {
    }
    ~RemoteHistoryDataSyncer()
    {
        if(mThread.isRunning())
        {
            mThread.quit();
            mThread.wait();
        }
    }

signals:
    void signalEventProgress(float value);
    void signalEventFinished(int        );

    void signalCommandCancle(           );

public slots:
    void onSignalEventProgress (float value)
    {
        emit signalEventProgress(value);
    }

    void onSignalEventFinished(int error)
    {
        disconnect(this   , SIGNAL(signalCommandCancle (     )), mpWoker, SLOT(onCommandCancle      (     )));
        disconnect(mpWoker, SIGNAL(signalEventProgress (float)), this   , SLOT(onSignalEventProgress(float)));
        disconnect(mpWoker, SIGNAL(signalEventFinished (int  )), this   , SLOT(onSignalEventFinished(int  )));

        mThread.quit();
        mThread.wait();

        emit signalEventFinished(error);
    }
};



#endif // REMOTEHISTORYDATASYNCER_H
