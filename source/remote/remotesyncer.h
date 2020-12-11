#ifndef REMOTESYNCER_H
#define REMOTESYNCER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QTcpSocket>

#include "source/remote/dto/enum/remoteenumdef.h"
#include "source/history/fileutil/filewriterex.h"
#include "source/remote/strpacket.h"

class RemoteSyncer : public QObject
{
    Q_OBJECT
private:
    const quint16  PORT          = 10024;
    QString        mSyncDate     = "";
    int            mDevNum       = 0;
    QString        mDstDir       = "";

    QTimer      *  mpTimer       = nullptr;
    QTcpSocket  *  mpSocket      = nullptr;
    QByteArray     mRcvBuffer    ;

    FileWriterEx * mpFileWriter  = nullptr;
    quint64        mRcvByte      = 0;
    quint64        mRcvTotalByte = 0;
    QStringList    mRcvFileList  ;

public:
    explicit RemoteSyncer(QObject *parent = nullptr) : QObject(parent)
    {
    }
    ~RemoteSyncer()
    {
        close();
    }

public slots:
    void onCommandSync(QString dstDir, int deviceNum, QString ip, QString syncDate)
    {
        mSyncDate = syncDate ;
        mDevNum   = deviceNum;
        mDstDir   = dstDir   ;

        qDebug() << "[RemoteSyncer::onCommandSync] dstDir : " << dstDir << ", deviceNum : " << deviceNum << ", ip : " << ip << ", syncDate : " << syncDate;

        if(open(ip, PORT) == false)
            return;

        QByteArray sendBuf;
        QByteArray syncDateBuff = syncDate.toUtf8();
        StRPacket  packet;

        packet.mFuncCode = RemoteEnumDef::RFUNC_CODE_RSYNC;
        packet.mSize = syncDateBuff.size();

        sendBuf.append((char *)&packet, sizeof(StRPacket));
        sendBuf.append(syncDateBuff);

        mpSocket->write(sendBuf);
        mpTimer->start();

    }

    void onCommandCancel()
    {
        syncFinished(RemoteEnumDef::RSYNC_ERR_CANCLE);
    }

signals:
    void signalEventProgress (int progressValue, int totalValue);
    void signalEventFinished (int err);

private slots:
    void onTimeout()
    {
        syncFinished(RemoteEnumDef::RSYNC_ERR_NETWORK);
    }

    void onSockError(QAbstractSocket::SocketError err)
    {
        qDebug() << "[RemoteSyncer::onSockError]" << err;
        syncFinished(RemoteEnumDef::RSYNC_ERR_NETWORK);
    }

    void onReceive()
    {
        if(mpSocket == nullptr)
            return;

        int headerSize = sizeof(StRPacket);
        int availableSize = mpSocket->bytesAvailable();

        while (availableSize > 0) {

            if(mRcvBuffer.size() == 0 && availableSize < headerSize)
                return;
            else if(mRcvBuffer.size() == 0)
            {
                mRcvBuffer.append(mpSocket->read(headerSize));
                availableSize = availableSize - headerSize;
            }

            StRPacket * pHeader = (StRPacket *)mRcvBuffer.data();

            if(availableSize < pHeader->mSize)
                return;

            if(pHeader->mDeviceNum != mDevNum)
            {
                syncFinished(RemoteEnumDef::RSYNC_ERR_NETWORK);
                return;
            }

            mRcvBuffer.append(mpSocket->read(pHeader->mSize));
            availableSize = availableSize - pHeader->mSize;

            procPacket(mRcvBuffer);

            mRcvBuffer.clear();
        }
    }

private:
    bool open(QString ip, quint16 port)
    {
        mpTimer = new QTimer(this);
        mpTimer->setInterval(5000);
        connect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        mpSocket = new QTcpSocket(this);
        connect(mpSocket, SIGNAL(readyRead()), this, SLOT(onReceive  ()));
        connect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));

        mpSocket->connectToHost(ip, port);

        if(mpSocket->waitForConnected(1000) == false)
        {
            onSockError(QAbstractSocket::SocketError::SocketTimeoutError);
            return false;
        }
        return true;
    }

    void close()
    {
        qDebug() << "[RemoteSyncer::close]";

        closeFileWriter();

        if(mpSocket != nullptr)
        {
            disconnect(mpSocket, SIGNAL(readyRead()), this, SLOT(onReceive  ()));
            disconnect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));

            mpSocket->deleteLater();
            mpSocket = nullptr;
        }

        if(mpTimer != nullptr)
        {
            mpTimer->stop();
            delete mpTimer;
            mpTimer = nullptr;
        }
    }

    void openFileWriter(QString dir, QString fileName)
    {
        closeFileWriter();

        mpFileWriter = new FileWriterEx(this);
        mpFileWriter->open(dir, fileName, FileWriterEx::FILE_OPEN_APPENDWRITE);
    }

    void closeFileWriter()
    {
        if(mpFileWriter != nullptr)
        {
            mpFileWriter->close();
            delete mpFileWriter;

            mpFileWriter = nullptr;
        }
    }

    void syncFinished(int err)
    {
        close();
        emit signalEventFinished(err);
    }

    void procPacket(QByteArray rcvData)
    {
        if(mpTimer != nullptr)
            mpTimer->stop();

        StRPacket * packet = (StRPacket *)rcvData.data();

        switch(packet->mFuncCode)
        {
        case RemoteEnumDef::RFUNC_CODE_RSYNC_ALREADY_SYNCING:
            {
                qDebug() << "[RemoteSyncer::procPacket] FUNC_CODE_RSYNC_ALREADY_SYNCING";
                syncFinished(RemoteEnumDef::RSYNC_ERR_ALREADY_SYNCING);
                return;
            }
            break;

        case RemoteEnumDef::RFUNC_CODE_RSYNC_INIT:
            {
                qDebug() << "[RemoteSyncer::procPacket] FUNC_CODE_RSYNC_INIT";

                if(packet->mSize != (sizeof(StRPacketSyncInitRes) - sizeof(StRPacket)))
                {
                    syncFinished(RemoteEnumDef::RSYNC_ERR_NETWORK);
                    return;
                }

                StRPacketSyncInitRes * rsyncHeader = (StRPacketSyncInitRes *)packet;
                mRcvTotalByte = rsyncHeader->mTotalByte;
            }
            break;

        case RemoteEnumDef::RFUNC_CODE_RSYNC_FILE_INFO:
            {
                qDebug() << "[RemoteSyncer::procPacket] FUNC_CODE_RSYNC_FILE_INFO" << QString::fromUtf8(packet->mData, packet->mSize);

                if(packet->mSize > 0)
                {
                    QString fileName = QString::fromUtf8(packet->mData, packet->mSize);
                    mRcvFileList.append(fileName);

                    openFileWriter(mDstDir, QString("%1.temp").arg(fileName));
                }
                else
                {
                    syncFinished(RemoteEnumDef::RSYNC_ERR_FILE_INFO);
                    return;
                }
            }
            break;

        case RemoteEnumDef::RFUNC_CODE_RSYNC_FILE_CONTENT:
            {
                if(packet->mSize > 0)
                {
                    mpFileWriter->appendWriteByte(packet->mData, packet->mSize);
                    mRcvByte = packet->mSize + mRcvByte;
                    emit signalEventProgress(mRcvByte, mRcvTotalByte);
                }
            }
            break;

        case RemoteEnumDef::RFUNC_CODE_RSYNC_COMPLETE:
            qDebug() << "[RemoteSyncer::procPacket] FUNC_CODE_RSYNC_COMPLETE";

            closeFileWriter();

            for(int i = 0; i < mRcvFileList.size(); i ++)
            {
                if(QFile::exists(QString("%1/%2").arg(mDstDir).arg(mRcvFileList.at(i))))
                    QFile::remove(QString("%1/%2").arg(mDstDir).arg(mRcvFileList.at(i)));

                QFile::rename(QString("%1/%2.temp").arg(mDstDir).arg(mRcvFileList.at(i)), QString("%1/%2").arg(mDstDir).arg(mRcvFileList.at(i)));
            }

            syncFinished(RemoteEnumDef::RSYNC_ERR_NONE);
            return;
        }

        if(mpTimer != nullptr)
            mpTimer->start();
    }
};

#endif // REMOTESYNCER_H
