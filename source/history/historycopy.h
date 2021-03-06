#ifndef HISTORYCOPY_H
#define HISTORYCOPY_H

#include <QObject>
#include <QDebug>
#include "source/history/def/filedef.h"
#include "source/history/fileutil/filecopylocal.h"


class HistoryCopy : public QObject
{
    Q_OBJECT

public:
    int            mDevNum   ;
    QString        mDst;
    QString        mSrc;

    QThread        * mpThread         = nullptr;
    FileCopyLocal  * mpFileCopy       = nullptr;

    explicit HistoryCopy(QObject *parent = nullptr) : QObject(parent)
    {

    }
    ~HistoryCopy()
    {
        close();
    }

    bool copy(QString src)
    {
        QString backupFloder = QString("%1/%2").arg(src).arg("backup");
        mpThread = new QThread;
        mpFileCopy = new FileCopyLocal;

        mpFileCopy->moveToThread(mpThread);
        mpThread->start();

        connect(mpThread, &QThread::finished, mpFileCopy, &QObject::deleteLater);
        connect(this, SIGNAL(signalCommandCopyFolder(QString, QString)), mpFileCopy, SLOT(onCommandCopyFolder(QString, QString)));
        connect(mpFileCopy, SIGNAL(signalEventProgress(int, int)), this, SLOT(onProgress(int, int)));
        connect(mpFileCopy, SIGNAL(signalEventComplete(bool)), this, SLOT(onComplete(bool)));

        if(src.endsWith("/novasen") == false)
        {
            qDebug() << "[HistoryCopy::copy] invaild path : " << src;
            onComplete(false);
            return false;
        }

        QDir targetDir(backupFloder);

        if(targetDir.exists() == false)
        {
            qDebug() << "[HistoryCopy::copy] can not found backup folder : " << src;
            onComplete(false);
            return false;
        }

        emit signalCommandCopyFolder(FileDef::DATABASE_DIR(), backupFloder);

        return true;
    }


signals:
    void signalCommandCopyFolder(QString dst, QString src);
    void signalCommandCopyHistory(QString dst, QString ip, QString syncDate);

    void signalEventProgress(int procIdx, int totalCnt);
    void signalEventComplete(bool isSucc);

private slots:
    void onProgress(int procIdx, int totalCnt)
    {
        emit signalEventProgress(procIdx, totalCnt);
    }

    void onComplete(bool isSucc)
    {
        close();
        emit signalEventComplete(isSucc);
    }

private:
    void close()
    {
        if(mpFileCopy != nullptr)
        {
            disconnect(mpFileCopy, nullptr, nullptr, nullptr);
            mpFileCopy->cancel();
            mpFileCopy = nullptr;
        }

        if(mpThread != nullptr)
        {
            if(mpThread->isRunning())
            {
                mpThread->quit();
                mpThread->wait();
            }

            mpThread->deleteLater();
            mpThread = nullptr;
        }
    }

};
#endif // HISTORYCOPY_H
