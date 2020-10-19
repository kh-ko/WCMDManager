#ifndef MDCHECKUPITEMMODEL_H
#define MDCHECKUPITEMMODEL_H

#include <QObject>
#include "source/model/eventitemmodel.h"
class MDCheckupItemModel : QObject
{
    Q_OBJECT

public:
    int     mProductNo  = 0;
    QString mProductName= "";
    QString mTime       = "";
    bool    mIsPassFe01 = false;
    bool    mIsPassFe02 = false;
    bool    mIsPassFe03 = false;
    bool    mIsPassSus01= false;
    bool    mIsPassSus02= false;
    bool    mIsPassSus03= false;
signals:

public:
    void setValue(EventItemModel * event, int productNo, QString productName)
    {
        mProductNo = productNo;
        mProductName = productName;
        mTime = event->mDate.split(" ")[1].split(".")[0];

        mIsPassFe01  = (event->mValue & (1 << 5)) != 0 ? true : false;
        mIsPassFe02  = (event->mValue & (1 << 4)) != 0 ? true : false;
        mIsPassFe03  = (event->mValue & (1 << 3)) != 0 ? true : false;
        mIsPassSus01 = (event->mValue & (1 << 2)) != 0 ? true : false;
        mIsPassSus02 = (event->mValue & (1 << 1)) != 0 ? true : false;
        mIsPassSus03 = (event->mValue & (1 << 0)) != 0 ? true : false;
    }

    void setValue(QString value)
    {
        QStringList valueList = value.split(",");

        for(int i = 0; i < valueList.size(); i ++)
        {
            if(valueList[i].contains(":") == false)
                continue;

            int splitIdx = valueList[i].indexOf(":");
            QString key = valueList[i].left(splitIdx);
            QString value = valueList[i].mid(splitIdx+1);

            if     (key == "PNO"  ){mProductNo   = value.toInt()       ;}
            else if(key == "PNAME"){mProductName = value               ;}
            else if(key == "TIME" ){mTime        = value               ;}
            else if(key == "FE01" ){mIsPassFe01  = (value.toInt() == 1);}
            else if(key == "FE02" ){mIsPassFe02  = (value.toInt() == 1);}
            else if(key == "FE03" ){mIsPassFe03  = (value.toInt() == 1);}
            else if(key == "SUS01"){mIsPassSus01 = (value.toInt() == 1);}
            else if(key == "SUS02"){mIsPassSus02 = (value.toInt() == 1);}
            else if(key == "SUS03"){mIsPassSus03 = (value.toInt() == 1);}
        }
    }

    QString toString()
    {

    }
    explicit MDCheckupItemModel(QObject *parent = nullptr):QObject(parent){}
};
#endif // MDCHECKUPITEMMODEL_H
