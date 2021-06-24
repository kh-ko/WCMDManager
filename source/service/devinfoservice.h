#ifndef DEVINFOSERVICE_H
#define DEVINFOSERVICE_H

#include <QObject>
#include <QSettings>
#include <QDir>
#include <QDebug>
#include "source/history/def/filedef.h"
#include "source/remote/dto/devinfodto.h"

#define pDevInfoSvc DevInfoService::getInstance()

class DevInfoService : public QObject
{
    Q_OBJECT
public:
    static DevInfoService * getInstance()
    {
        static DevInfoService  *pSelf = nullptr;

        if(pSelf == nullptr)
        {
            pSelf = new DevInfoService();
        }

        return pSelf;
    }

    QList<DevInfoDto>  mDevList;

    explicit DevInfoService(QObject *parent = nullptr) : QObject(parent)
    {
        qDebug() << "[DevInfoService] create instance";

        mpSettings = new QSettings("novasen","WCMDManager", this);
    }

    void start()
    {
    }

    void stop()
    {

    }

    void refreshList()
    {
        mDevList.clear();

        QDir dir(FileDef::DATABASE_DIR());

        QStringList dirList = dir.entryList(QStringList() << "*",QDir::Dirs, QDir::SortFlag::Name);

        foreach(QString dir, dirList)
        {
            DevInfoDto devInfo;

            devInfo.mNumber = dir.toInt();
            devInfo.mName   = mpSettings->value(QString("deviceinfo/%1").arg(devInfo.mNumber), "-").toString();

            QString strMDLimit = mpSettings->value(QString("deviceinfo/%1_md_limit").arg(devInfo.mNumber),"").toString();;

            convertMDLimitStrToList(strMDLimit, devInfo.mPDSeq, devInfo.mLimFe, devInfo.mLimSus);

            if(devInfo.mNumber != 0)
                addToList(devInfo);
        }
    }

    void editDevInfo(int num, QString name)
    {
        mpSettings->setValue(QString("deviceinfo/%1").arg(num), name);

        emit signalEventChangedDevInfo(num, name);
    }

    void editDevMDLimit(int num, QString strMDLimit)
    {
        mpSettings->setValue(QString("deviceinfo/%1_md_limit").arg(num), strMDLimit);

        DevInfoDto dev = findDevInfo(num);

        convertMDLimitStrToList(strMDLimit, dev.mPDSeq, dev.mLimFe, dev.mLimSus);

        refreshList();

        emit signalEventChangedDevMDLimit(num, strMDLimit);
    }

    DevInfoDto findDevInfo(int num)
    {
        DevInfoDto dto;

        for(int i = 0; i < mDevList.size(); i ++)
        {
            if(mDevList[i].mNumber == num)
                return mDevList[i];
        }

        return dto;
    }

    void convertMDLimitStrToList(QString strMDLimit, QList<quint64> &seqList, QList<QString> &limitFeList, QList<QString> &limitSusList)
    {
        seqList.clear();
        limitFeList.clear();
        limitSusList.clear();

        QStringList limitList = strMDLimit.split(" ");

        foreach(QString limitItem, limitList)
        {
            QStringList item = limitItem.split(";");

            if(item.size() != 3)
                continue;

            quint64 seq = item.at(0).toULongLong();
            QString fe  = item.at(1);
            QString sus = item.at(2);

            seqList.append(seq);
            limitFeList.append(fe);
            limitSusList.append(sus);
        }
    }

signals:
    void signalEventChangedDevInfo(int num, QString name);
    void signalEventChangedDevMDLimit(int num, QString strMDLimit);

private:
    QSettings * mpSettings = nullptr;

    void addToList(DevInfoDto dto)
    {
        for(int i = 0; i < mDevList.size(); i ++)
        {
            if(mDevList[i].mNumber == dto.mNumber)
                return;
        }

        for(int i = 0; i < mDevList.size(); i ++)
        {
            if(mDevList[i].mNumber > dto.mNumber)
            {
                mDevList.insert(i, dto);
                return;
            }
        }

        mDevList.append(dto);
    }

};

#endif // DEVSETTINGSERVICE_H
