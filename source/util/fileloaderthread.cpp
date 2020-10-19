#include "fileloaderthread.h"

#include <QDebug>
#include "source/globaldef/EnumDefine.h"

FileLoakerThreadWorker::FileLoakerThreadWorker(QObject *parent) : QObject(parent)
{

}

FileLoakerThreadWorker::~FileLoakerThreadWorker()
{
    qDebug() << "FileLoakerThreadWorker::delete";

    close();
}

void FileLoakerThreadWorker::onCommandReadAll(QString path, QString fileName)
{
    if(QFile::exists(QString("%1/%2").arg(path).arg(fileName)) == false)
    {
        emit signalReadAll(EnumDefine::FileErrorType::FILE_ERROR_NOT_EXIST, "");
        return;
    }

    QFile file(QString("%1/%2").arg(path).arg(fileName));
    file.open(QIODevice::ReadOnly | QIODevice::Text );

    if(file.isOpen() == false)
    {
        emit signalReadAll(EnumDefine::FileErrorType::FILE_ERROR_OPEN, "");
        return;
    }

    QTextStream out(&file);
    QString content = out.readAll();

    file.close();

    signalReadAll(EnumDefine::FileErrorType::FILE_ERROR_NONE, content);
}
void FileLoakerThreadWorker::onCommandReadLine(QString path, QString fileName, int lineCnt)
{
    QStringList lines;

    if(QFile::exists(QString("%1/%2").arg(path).arg(fileName)) == false)
    {
        emit signalReadLine(EnumDefine::FileErrorType::FILE_ERROR_NOT_EXIST, lines);
        emit signalReadEof();
        return;
    }

    if(mpFile != nullptr && mpFile->fileName() != QString("%1/%2").arg(path).arg(fileName))
        close();

    if(mpFile == nullptr)
    {
        mpFile = new QFile(QString("%1/%2").arg(path).arg(fileName),this);
        mpFile->open(QIODevice::ReadOnly | QIODevice::Text );

        if(mpFile->isOpen() == false)
        {
            qDebug() << "[onCommandLoadLine] file name =" << QString("%1/%2").arg(path).arg(fileName) << ",occured exception, file name = " <<  mpFile->errorString();
            close();

            emit signalReadLine(EnumDefine::FileErrorType::FILE_ERROR_OPEN, lines);
            emit signalReadEof();
            return;
        }

        mpOutStream = new QTextStream();
        mpOutStream->setDevice(mpFile);
    }

    for(int i = 0; i < lineCnt; i ++)
    {
        if(mpOutStream->atEnd())
            break;

        lines.append(mpOutStream->readLine());
    }

    if(lines.size() == 0)
    {
        close();
        emit signalReadEof();
        return;
    }

    emit signalReadLine(EnumDefine::FileErrorType::FILE_ERROR_NONE, lines);
}

void FileLoakerThreadWorker::close()
{
    if(mpFile != nullptr)
    {
        if(mpOutStream != nullptr)
            delete mpOutStream;

        mpOutStream = nullptr;

        if(mpFile->isOpen())
            mpFile->close();

        delete mpFile;
        mpFile = nullptr;
    }
}
