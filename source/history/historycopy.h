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

    bool copy(QString src, int &oErr)
    {
        QString backupFloder = QString("%1/%2").arg(src).arg("backup");
        QDir targetDir(backupFloder);

        oErr = 0;

        if(src.endsWith("/NOVASEN"))
        {
            qDebug() << "[HistoryCopy::copy] OLD version path" << src;
            return copyOldVersion(src, oErr);
        }

        if(src.endsWith("/novasen") == false)
        {
            qDebug() << "[HistoryCopy::copy] invaild path : " << src;
            oErr = 1;
            onComplete(false);
            return false;
        }

        if(targetDir.exists() == false)
        {
            qDebug() << "[HistoryCopy::copy] can not found backup folder : " << src;
            onComplete(false);
            oErr = 2;
            return false;
        }

        mpThread = new QThread;
        mpFileCopy = new FileCopyLocal;

        mpFileCopy->moveToThread(mpThread);
        mpThread->start();

        connect(mpThread, &QThread::finished, mpFileCopy, &QObject::deleteLater);
        connect(this, SIGNAL(signalCommandCopyFolder(QString, QString)), mpFileCopy, SLOT(onCommandCopyFolder(QString, QString)));
        connect(this, SIGNAL(signalCommandCopyOldFolder(QString, QString)), mpFileCopy, SLOT(onCommandCopyOldFolder(QString, QString)));
        connect(mpFileCopy, SIGNAL(signalEventProgress(int, int)), this, SLOT(onProgress(int, int)));
        connect(mpFileCopy, SIGNAL(signalEventComplete(bool)), this, SLOT(onComplete(bool)));

        emit signalCommandCopyFolder(FileDef::DATABASE_DIR(), backupFloder);

        return true;
    }

    bool copyOldVersion(QString src, int &oErr)
    {
        QString backupFloder = QString("%1/%2").arg(src).arg("backup");
        QDir targetDir(backupFloder);

        oErr = 0;

        if(src.endsWith("/NOVASEN") == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "][HistoryCopy::copy] invaild path : " << src;
            oErr = 1;
            onComplete(false);
            return false;
        }

        mpThread = new QThread;
        mpFileCopy = new FileCopyLocal;

        mpFileCopy->moveToThread(mpThread);
        mpThread->start();

        connect(mpThread, &QThread::finished, mpFileCopy, &QObject::deleteLater);
        connect(this, SIGNAL(signalCommandCopyFolder(QString, QString)), mpFileCopy, SLOT(onCommandCopyFolder(QString, QString)));
        connect(this, SIGNAL(signalCommandCopyOldFolder(QString, QString)), mpFileCopy, SLOT(onCommandCopyOldFolder(QString, QString)));
        connect(mpFileCopy, SIGNAL(signalEventProgress(int, int)), this, SLOT(onProgress(int, int)));
        connect(mpFileCopy, SIGNAL(signalEventComplete(bool)), this, SLOT(onComplete(bool)));

        emit signalCommandCopyOldFolder(FileDef::DATABASE_DIR(), src);

        return true;
    }


signals:
    void signalCommandCopyFolder(QString dst, QString src);
    void signalCommandCopyOldFolder(QString dst, QString src);
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
