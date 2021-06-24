#ifndef PDCHECKUPDTO_H
#define PDCHECKUPDTO_H

#include <QObject>
#include <QDateTime>
#include "source/history/def/datetimeform.h"
#include "source/history/dto/eventdto.h"
class PDCheckupDto
{
public:
    quint64 mProductSeq = 0;
    int     mProductNo  = 0;
    QString mProductName= "";
    QTime   mTime;
    bool    mIsPassFe01 = false;
    bool    mIsPassFe02 = false;
    bool    mIsPassFe03 = false;
    bool    mIsPassSus01= false;
    bool    mIsPassSus02= false;
    bool    mIsPassSus03= false;

    PDCheckupDto(){}
    PDCheckupDto(const PDCheckupDto& copy):
        mProductSeq (copy.mProductSeq ),
        mProductNo  (copy.mProductNo  ),
        mProductName(copy.mProductName),
        mTime       (copy.mTime       ),
        mIsPassFe01 (copy.mIsPassFe01 ),
        mIsPassFe02 (copy.mIsPassFe02 ),
        mIsPassFe03 (copy.mIsPassFe03 ),
        mIsPassSus01(copy.mIsPassSus01),
        mIsPassSus02(copy.mIsPassSus02),
        mIsPassSus03(copy.mIsPassSus03){}
    ~PDCheckupDto(){}

    PDCheckupDto& operator=(const PDCheckupDto& other)
    {
        mProductSeq  = other.mProductSeq ;
        mProductNo   = other.mProductNo  ;
        mProductName = other.mProductName;
        mTime        = other.mTime       ;
        mIsPassFe01  = other.mIsPassFe01 ;
        mIsPassFe02  = other.mIsPassFe02 ;
        mIsPassFe03  = other.mIsPassFe03 ;
        mIsPassSus01 = other.mIsPassSus01;
        mIsPassSus02 = other.mIsPassSus02;
        mIsPassSus03 = other.mIsPassSus03;
        return *this;
    }

    bool setValue(EventDto event, int pdNum, QString pdName)
    {
        mProductSeq  = event.mPDSeq;
        mProductNo   = pdNum;
        mProductName = pdName;
        mTime        = event.mDateTime.time();

        mIsPassFe01  = (event.mEValue & (1 << 5)) != 0 ? true : false;
        mIsPassFe02  = (event.mEValue & (1 << 4)) != 0 ? true : false;
        mIsPassFe03  = (event.mEValue & (1 << 3)) != 0 ? true : false;
        mIsPassSus01 = (event.mEValue & (1 << 2)) != 0 ? true : false;
        mIsPassSus02 = (event.mEValue & (1 << 1)) != 0 ? true : false;
        mIsPassSus03 = (event.mEValue & (1 << 0)) != 0 ? true : false;

        return true;
    }

    bool setValue(QString value)
    {
        int findFieldCnt = 0;

        QStringList fieldList = value.split(",");

        foreach(QString field ,fieldList)
        {
            if(field.contains(":") == false)
                continue;

            int splitIdx  = field.indexOf(":");
            QString key   = field.left(splitIdx);
            QString value = field.mid(splitIdx+1);

            if     (key == "PSEQ" ){findFieldCnt++; mProductSeq  = value.toULongLong()        ;}
            else if(key == "PNO"  ){findFieldCnt++; mProductNo   = value.toInt()              ;}
            else if(key == "PNAME"){findFieldCnt++; mProductName = value                      ;}
            else if(key == "TIME" ){findFieldCnt++; mTime        = QTime::fromString(TIME_FMT);}
            else if(key == "FE01" ){findFieldCnt++; mIsPassFe01  = (value.toInt() == 1)       ;}
            else if(key == "FE02" ){findFieldCnt++; mIsPassFe02  = (value.toInt() == 1)       ;}
            else if(key == "FE03" ){findFieldCnt++; mIsPassFe03  = (value.toInt() == 1)       ;}
            else if(key == "SUS01"){findFieldCnt++; mIsPassSus01 = (value.toInt() == 1)       ;}
            else if(key == "SUS02"){findFieldCnt++; mIsPassSus02 = (value.toInt() == 1)       ;}
            else if(key == "SUS03"){findFieldCnt++; mIsPassSus03 = (value.toInt() == 1)       ;}
        }

        return findFieldCnt == 0 ? false : true;
    }

    QString toString(){
        return QString("PSEQ:%1,PNO:%2,PNAME:%3,TIME:%4,FE01:%5,FE02:%6,FE03:%7,SUS01:%8,SUS02:%9,SUS03:%10")
                .arg(mProductSeq)
                .arg(mProductNo)
                .arg(mProductName)
                .arg(mTime.toString(TIME_FMT))
                .arg(mIsPassFe01  == true ? 1 : 0)
                .arg(mIsPassFe02  == true ? 1 : 0)
                .arg(mIsPassFe03  == true ? 1 : 0)
                .arg(mIsPassSus01 == true ? 1 : 0)
                .arg(mIsPassSus02 == true ? 1 : 0)
                .arg(mIsPassSus03 == true ? 1 : 0);
    }

};
Q_DECLARE_METATYPE(PDCheckupDto);
#endif // PDCHECKUPDTO_H
