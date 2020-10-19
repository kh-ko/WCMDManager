#include "filewriter.h"

#include <QDebug>

bool FileWriter::appendWrite(QString path, QString fileName, char * content, int size)
{
    if(mPath != path ||mFileName != fileName)
    {
        if(mPath != path)
            mkdirRecursively(path);

        close();

        if(QFile::exists(QString("%1/%2.txt").arg(path).arg(fileName)))
            QFile::remove(QString("%1/%2.txt").arg(path).arg(fileName));

        mpFile = new QFile();
        mpFile->setFileName(QString("%1/%2").arg(path).arg(fileName));
        mpFile->open(QIODevice::ReadWrite | QIODevice::Append);

        if(mpFile->isOpen() == false)
        {
            qDebug() << "[FileWriter::appendWrite]can not overWriteLine : " << path << "/" << fileName  ;
            return false;
        }

        mPath = path;
        mFileName = fileName;
    }

     qDebug() << "[FileWriter::appendWrite] fileName = " << fileName;

    mpFile->write(content, size);
    mpFile->flush();

    return true;
}

void FileWriter::close()
{
    if(mpFile != nullptr)
    {
        if(mpFile->isOpen())
            mpFile->close();

        delete mpFile;

        mpFile = nullptr;
    }

    mPath = "";
    mFileName = "";
}

void FileWriter::mkdirRecursively(QString path)
{
    if(QDir().exists(path))
        return;

    QStringList folderList = path.split("/");
    QString     pathName = QString("");

    for(int i = 0; i < folderList.size(); i ++)
    {
        QString folderName = folderList.at(i);

        if(folderName == nullptr || folderName.length() == 0)
            continue;

        if(pathName.length() == 0)
        {
#if defined(Q_OS_WIN)
            pathName = QString("%1").arg(folderName);
#else
            pathName = QString("/%1").arg(folderName);
#endif
        }
        else
            pathName = QString("%1/%2").arg(pathName).arg(folderName);

        if(QDir().exists(pathName))
            continue;

        QDir().mkdir(pathName);
    }
}

FileWriter::FileWriter(QObject *parent) : QObject(parent)
{

}

FileWriter::~FileWriter()
{
    close();
}
