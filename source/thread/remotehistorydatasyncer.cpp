#include "remotehistorydatasyncer.h"

#include "source/util/myalloc.h"


void RemoteHistoryDataSyncWoker::onCommandCancle()
{
    close(EnumDefine::RemoteSyncErrorType::RSYNC_ERROR_CANCLE);
}

void RemoteHistoryDataSyncWoker::onStart()
{
    open();
}

void RemoteHistoryDataSyncWoker::onReceive()
{
    if(mpSocket == nullptr)
        return;

    int headerSize = sizeof(StPacket);
    int availableSize = mpSocket->bytesAvailable();

    while (availableSize > 0) {

        if(mRcvBuffer.size() == 0 && availableSize < headerSize)
            return;
        else if(mRcvBuffer.size() == 0)
        {
            mRcvBuffer.append(mpSocket->read(headerSize));
            availableSize = availableSize - headerSize;
        }

        StPacket * pHeader = (StPacket *)mRcvBuffer.data();

        if(availableSize < pHeader->mSize)
            return;

        if(pHeader->mDeviceNum != mDeviceNum)
        {
            close(EnumDefine::RemoteSyncErrorType::RSYNC_ERROR_NETWORK);
            return;
        }
        mRcvBuffer.append(mpSocket->read(pHeader->mSize));
        availableSize = availableSize - pHeader->mSize;

        procPacket(mRcvBuffer);

        mRcvBuffer.clear();
    }
}

void RemoteHistoryDataSyncWoker::onSockError(QAbstractSocket::SocketError error)
{
    qDebug() << "[RemoteHistoryDataSyncWoker::onSockError]error =" << error;

    close(EnumDefine::RemoteSyncErrorType::RSYNC_ERROR_NETWORK);
}

void RemoteHistoryDataSyncWoker::onTimeout()
{
    onSockError(QAbstractSocket::SocketError::SocketTimeoutError);
}

RemoteHistoryDataSyncWoker::RemoteHistoryDataSyncWoker(QObject *parent) : QObject(parent)
{

}

RemoteHistoryDataSyncWoker::~RemoteHistoryDataSyncWoker()
{
    close(EnumDefine::RemoteSyncErrorType::RSYNC_ERROR_CLOSE);
}

void RemoteHistoryDataSyncWoker::open()
{
    mpTimer = new QTimer(this);
    mpTimer->setInterval(5000);
    connect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    mpFileWriter = new FileWriter(this);
    mpCheckHistoryFileWriter = new FileWriter(this);
    mpSocket = new QTcpSocket(this);
    connect(mpSocket, SIGNAL(readyRead()), this, SLOT(onReceive  ()));
    connect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));

    mpSocket->connectToHost(mIp, mPort);

    if(mpSocket->waitForConnected(1000) == false)
    {
        onSockError(QAbstractSocket::SocketError::SocketTimeoutError);
        return;
    }

    QByteArray sendBuf;
    QByteArray syncDate = mLastSyncDate.toUtf8();
    StPacket packet;

    packet.mFuncCode = EnumDefine::FuncCode::FUNC_CODE_RSYNC;
    packet.mSize = syncDate.size();

    qDebug() << "[RemoteHistoryDataSyncWoker::open] last sync date = " << mLastSyncDate;

    sendBuf.append((char *)&packet, sizeof(StPacket));
    sendBuf.append(syncDate);
    mpSocket->write(sendBuf);

    mpTimer->start();
}

void RemoteHistoryDataSyncWoker::close(EnumDefine::RemoteSyncErrorType error)
{
    qDebug() << "[RemoteHistoryDataSyncWoker::close]";

    QDir dir(mFilePath);
    QStringList fileList = dir.entryList(QStringList() << "*.temp",QDir::Files,QDir::SortFlag::Name);

    for(int i = 0; i < fileList.size(); i ++)
    {
        QFile::remove(QString("%1/%2").arg(mFilePath).arg(fileList.at(i)));
    }

    if(mpSocket != nullptr)
    {
        disconnect(mpSocket, SIGNAL(readyRead()), this, SLOT(onReceive  ()));
        disconnect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));

        qDebug() << "[RemoteHistoryDataSyncWoker::close]state = " << mpSocket->state();

        if(mpSocket->state() != QAbstractSocket::SocketState::UnconnectedState)
        {
            mpSocket->disconnectFromHost();
            mpSocket->waitForDisconnected(1000);
        }
        mpSocket->close();

        mpSocket->deleteLater();

        mpSocket = nullptr;
    }

    if(mpFileWriter != nullptr)
    {
        mpFileWriter->close();
        delete mpFileWriter;

        mpFileWriter = nullptr;
    }

    if(mpCheckHistoryFileWriter != nullptr)
    {
        mpCheckHistoryFileWriter->close();
        delete mpCheckHistoryFileWriter;

        mpCheckHistoryFileWriter = nullptr;
    }


    if(mpTimer != nullptr)
    {
        mpTimer->stop();
        delete mpTimer;
        mpTimer = nullptr;
    }

    emit signalEventFinished(error);
}

void RemoteHistoryDataSyncWoker::procPacket(QByteArray data)
{
    if(mpTimer != nullptr)
        mpTimer->stop();

    StPacket * packet = (StPacket *)data.data();

    switch(packet->mFuncCode)
    {
    case EnumDefine::FuncCode::FUNC_CODE_RSYNC_ALREADY_SYNCING:
        {
            qDebug() << "[RemoteHistoryDataSyncWoker::procPacket] FUNC_CODE_RSYNC_ALREADY_SYNCING";
            close(EnumDefine::RemoteSyncErrorType::RSYNC_ERROR_ALREADY_SYNCING);
        }
        break;

    case EnumDefine::FuncCode::FUNC_CODE_RSYNC_INIT:
        {
            qDebug() << "[RemoteHistoryDataSyncWoker::procPacket] FUNC_CODE_RSYNC_INIT";
            if(packet->mSize != (sizeof(StPacketRSyncInitRes) - sizeof(StPacket)))
                close(EnumDefine::RemoteSyncErrorType::RSYNC_ERROR_NETWORK);

            StPacketRSyncInitRes * rsyncHeader = (StPacketRSyncInitRes *)packet;
            mTotalBytes = rsyncHeader->mTotalByte;
        }
        break;

    case EnumDefine::FuncCode::FUNC_CODE_RSYNC_FILE_INFO:
        {
            qDebug() << "[RemoteHistoryDataSyncWoker::procPacket] FUNC_CODE_RSYNC_FILE_INFO" << QString::fromUtf8(packet->mData, packet->mSize);

            if(packet->mSize > 0)
            {
                QString fileName = QString::fromUtf8(packet->mData, packet->mSize);

                if(mRDataSpliter.compareDateByFileName(fileName) == false)
                {
                    writeCheckHistory();
                }

                mRDataSpliter.setDateByFileName(fileName);
                mFileNameList.append(fileName);
            }
            else
            {
                close(EnumDefine::RemoteSyncErrorType::RSYNC_ERROR_FILE_INFO);
            }
        }
        break;

    case EnumDefine::FuncCode::FUNC_CODE_RSYNC_FILE_CONTENT:
        {
            if(packet->mSize > 0)
            {
                if(mFileNameList[mFileNameList.size() - 1].contains("-EH"))
                {
                    mRDataSpliter.addEhData(packet);
                }
                else if(mFileNameList[mFileNameList.size() - 1].contains("-PH"))
                {
                    mRDataSpliter.addPhData(packet);
                }

                mpFileWriter->appendWrite(mFilePath, QString("%1.temp").arg(mFileNameList[mFileNameList.size() - 1]), packet->mData, packet->mSize);
                mRcvBytes = packet->mSize + mRcvBytes;
                emit signalEventProgress(mRcvBytes/mTotalBytes);
            }
        }
        break;

    case EnumDefine::FuncCode::FUNC_CODE_RSYNC_COMPLETE:
        qDebug() << "[RemoteHistoryDataSyncWoker::procPacket] FUNC_CODE_RSYNC_COMPLETE";

        writeCheckHistory();

        mpFileWriter->close();

        for(int i = 0; i < mFileNameList.size(); i ++)
        {
            if(QFile::exists(QString("%1/%2").arg(mFilePath).arg(mFileNameList.at(i))))
                QFile::remove(QString("%1/%2").arg(mFilePath).arg(mFileNameList.at(i)));

            QFile::rename(QString("%1/%2.temp").arg(mFilePath).arg(mFileNameList.at(i)), QString("%1/%2").arg(mFilePath).arg(mFileNameList.at(i)));
        }

        emit signalEventProgress(1);
        close(EnumDefine::RemoteSyncErrorType::RSYNC_ERROR_NONE);
        break;
    }

    if(mpTimer != nullptr)
        mpTimer->start();
}

void RemoteHistoryDataSyncWoker::writeCheckHistory()
{
    bool isWritten = false;

    for(int i = 0; i < mRDataSpliter.mListCheckupEvent.size(); i ++)
    {
        QByteArray row = mRDataSpliter.getCHStrRow(i).toUtf8();
        if(row.size() > 0)
        {
            isWritten = true;
            mpCheckHistoryFileWriter->appendWrite(mFilePath, QString("%1.temp").arg(mRDataSpliter.getCHFileName()), row.data(), row.size());
        }
    }

    if(isWritten)
    {
        mpCheckHistoryFileWriter->close();
        mFileNameList.append(mRDataSpliter.getCHFileName());
    }
}

