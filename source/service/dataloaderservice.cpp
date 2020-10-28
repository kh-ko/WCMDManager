#include "dataloaderservice.h"

#include <QApplication>
#include <QDebug>

void DataLoaderService::loadData(int dNumber, int year, int month, int day, bool reLoad)
{
    qDebug() << "[DataLoaderService::loadData] device num = " << dNumber << ", year = " << year << ", month = " <<  month << ", day = " << day;

    if(mDeviceNumber == dNumber
        && mYear     == year
        && mMonth    == month
        && mDay      == day
        && reLoad    == false)
    {
        return;
    }

    setIsLoading(true);

    mDeviceNumber = dNumber;
    mYear = year;
    mMonth = month;
    mDay = day;
    mProcDay = 1;

    reset();

    QString path     = getPath();
    QString fileName = getProductStatisticsFileName();


    QDir dir(path);
    mAllFileList = dir.entryList(QStringList() << "*.txt",QDir::Files,QDir::SortFlag::Name);

    connect(this, SIGNAL(signalCommandReadProductStatistics(QString, QString)), &mFileLoader, SLOT(onCommandReadAll(QString, QString)));
    connect(&mFileLoader, SIGNAL(signalReadAll(int, QString)), this, SLOT(onSignalReadProductStatistics(int, QString)));

    qDebug() << "load file path = " << path;
    qDebug() << "load file name = " << fileName;

    emit signalCommandReadProductStatistics(path, fileName);
}

void DataLoaderService::onSignalReadProductStatistics(int error, QString content)
{
    if(error == EnumDefine::FileErrorType::FILE_ERROR_NONE)
    {
        qDebug() << "[DataLoaderService::onSignalReadProductStatistics]" << error;

        QStringList tempList = content.split("\n");
        tempList.removeLast();

        mProductStatistics.addDailyStatistics(mProcDay, tempList);
    }

    mProcDay ++;

    QString path     = getPath();
    QString fileName = getProductStatisticsFileName();

    if(fileName != "")
    {
        qDebug() << "load file name = " << fileName;
        emit signalCommandReadProductStatistics(path, fileName);
    }
    else
    {
        mProductStatistics.sort();

        disconnect(this, SIGNAL(signalCommandReadProductStatistics(QString, QString)), &mFileLoader, SLOT(onCommandReadAll(QString, QString)));
        disconnect(&mFileLoader, SIGNAL(signalReadAll(int, QString)), this, SLOT(onSignalReadProductStatistics(int, QString)));

        connect(this, SIGNAL(signalCommandReadProductHistory(QString, QString)), &mFileLoader, SLOT(onCommandReadAll(QString, QString)));
        connect(&mFileLoader, SIGNAL(signalReadAll(int, QString)), this, SLOT(onSignalReadProductHistory(int, QString)));

        qDebug() << "load file name = " << getProductHistoryFileName();
        emit signalCommandReadProductHistory(path, getProductHistoryFileName());
    }
}

void DataLoaderService::onSignalReadProductHistory(int error, QString content)
{
    if(error == EnumDefine::FileErrorType::FILE_ERROR_NONE)
    {
        qDebug() << "[DataLoaderService::onSignalReadProductHistory]" << error;

        QStringList tempList = content.split("\n");
        tempList.removeLast();

        for(int i = 0; i < tempList.size(); i ++)
        {
            ProductSettingModel * ps = new ProductSettingModel(this);
            ps->setValue(tempList.at(i));
            mListProductHis.append(ps);
            mWCModel.setProduct(ps);
        }
    }

    QString path     = getPath();
    QString fileName = getEventHistoryFileName();

    disconnect(this, SIGNAL(signalCommandReadProductHistory(QString, QString)), &mFileLoader, SLOT(onCommandReadAll(QString, QString)));
    disconnect(&mFileLoader, SIGNAL(signalReadAll(int, QString)), this, SLOT(onSignalReadProductHistory(int, QString)));

    connect(this, SIGNAL(signalCommandReadEventHistory(QString, QString, int)), &mFileLoader, SLOT(onCommandReadLine(QString, QString, int)));
    connect(&mFileLoader, SIGNAL(signalReadLine(int, QStringList)), this, SLOT(onSignalReadEventHistory(int, QStringList)));
    connect(&mFileLoader, SIGNAL(signalReadEof()), this, SLOT(onSignalReadEofEventHistory()));

    qDebug() << "load file name = " << fileName;

    emit signalCommandReadEventHistory(path, fileName, 3000);
}
void DataLoaderService::onSignalReadEventHistory(int error, QStringList content)
{
    if(error == EnumDefine::FileErrorType::FILE_ERROR_NONE)
    {
        qDebug() << "[DataLoaderService::onSignalReadEventHistory]" << error;

        for(int i = 0; i < content.size(); i ++)
        {
            EventItemModel event;
            event.setValue(content.at(i));

            if(isMetalCheckupEvent(event.mEventType))
            {
                MDCheckupItemModel * pItem = new MDCheckupItemModel(this);
                pItem->setValue(&event, mListProductHis[event.mProductHisIdx]->mNo, mListProductHis[event.mProductHisIdx]->mName);
                mListMDCheckupHis.append(pItem);
            }
            else if(isMetalDetectEvent(event.mEventType))
            {
                MDDetectItemModel * pItem = new MDDetectItemModel(this);
                pItem->setValue(&event, mListProductHis[event.mProductHisIdx]->mNo, mListProductHis[event.mProductHisIdx]->mName);
                mListMDDetectHis.append(pItem);
            }
            else if(isWeightCheckerEvent(event.mEventType))
            {
                mWCModel.addEvent(mListProductHis[event.mProductHisIdx]->mSeq, event.mEventType, event.mValue);
            }
        }
    }

    QString path     = getPath();
    QString fileName = getEventHistoryFileName();

    emit signalCommandReadEventHistory(path, fileName, 3000);
}
void DataLoaderService::onSignalReadEofEventHistory()
{
    disconnect(this, SIGNAL(signalCommandReadEventHistory(QString, QString, int)), &mFileLoader, SLOT(onCommandReadLine(QString, QString, int)));
    disconnect(&mFileLoader, SIGNAL(signalReadLine(int, QStringList)), this, SLOT(onSignalReadEventHistory(int, QStringList)));
    disconnect(&mFileLoader, SIGNAL(signalReadEof()), this, SLOT(onSignalReadEofEventHistory()));

    mWCModel.finishedAddEvent();
    setIsLoading(false);
}

QString DataLoaderService::getPath()
{
    QString path = QString("%1/database/%2").arg(mAppDirPath).arg(mDeviceNumber);
    return path;
}
QString DataLoaderService::getProductStatisticsFileName()
{
    int maxDay = 1;

    if(mMonth == 2)
    {
        if((mYear % 4) == 0 && ((mYear % 100) != 0 || (mYear % 400) == 0))
        {
            maxDay = 29;
        }
        else
        {
            maxDay = 28;
        }
    }
    else if(mMonth == 4 || mMonth == 6 || mMonth == 9 || mMonth == 11)
    {
        maxDay = 30;
    }
    else
    {
        maxDay = 31;
    }

    if(mProcDay > maxDay)
        return "";

    QString year  = QString::number(mYear).rightJustified(4, '0');
    QString month = QString::number(mMonth).rightJustified(2, '0');
    QString day   = QString::number(mProcDay).rightJustified(2, '0');

    QString fileName = QString("%1-%2-%3-PS.txt").arg(year).arg(month).arg(day);

    return fileName;
}
QString DataLoaderService::getEventHistoryFileName()
{
    QString year  = QString::number(mYear).rightJustified(4, '0');
    QString month = QString::number(mMonth).rightJustified(2, '0');
    QString day   = QString::number(mDay).rightJustified(2, '0');

    QString fileName = QString("%1-%2-%3-EH.txt").arg(year).arg(month).arg(day);

    return fileName;
}
QString DataLoaderService::getProductHistoryFileName()
{
    QString year  = QString::number(mYear).rightJustified(4, '0');
    QString month = QString::number(mMonth).rightJustified(2, '0');
    QString day   = QString::number(mDay).rightJustified(2, '0');

    QString fileName = QString("%1-%2-%3-PH.txt").arg(year).arg(month).arg(day);

    return fileName;
}

bool DataLoaderService::isMetalCheckupEvent(QString value)
{
    if(value == "M CHECK")
        return true;

    return false;
}

bool DataLoaderService::isMetalDetectEvent(QString value)
{
    if(value == "M F")
        return true;

    return false;
}

bool DataLoaderService::isWeightCheckerEvent(QString value)
{
    if     (value == "N"              )return true;
    else if(value == "UW"             )return true;
    else if(value == "OW"             )return true;
    else if(value == "U"              )return true;
    else if(value == "O"              )return true;
    else if(value == "ETC"            )return true;
    else if(value == "WC MD F"        )return true;

    return false;
}

void DataLoaderService::reset()
{
    mWCModel.reset();
    mAllFileList.clear();

    mProductStatistics.reset();

    for(int i = 0; i < mListProductHis.size(); i ++)
    {
        delete mListProductHis.at(i);
    }

    mListProductHis.clear();

    for(int i = 0; i < mListMDCheckupHis.size(); i ++)
    {
        delete mListMDCheckupHis.at(i);
    }

    mListMDCheckupHis.clear();

    for(int i = 0; i < mListMDDetectHis.size(); i ++)
    {
        delete mListMDDetectHis.at(i);
    }

    mListMDDetectHis.clear();
}
DataLoaderService::DataLoaderService(QObject *parent) : QObject(parent)
{
    mAppDirPath = QApplication::applicationDirPath();
}

/*"N"
"UW"
"OW"
"U"
"O"
"ETC"
"APP START"
"APP EXIT"
"M CHECK"
"W STATIC CARI"
"W DINAMIC CARI"
"RUN"
"STOP"
"M P"
"M F"
"M P CHECK"
"M F CHECK"
"N CHECK"
"UW CHECK"
"OW CHECK"
"U CHECK"
"O CHECK"
"ETC CHECK"
"WC MD F"
*/
