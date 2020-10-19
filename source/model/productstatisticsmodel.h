#ifndef PRODUCTSTATISTICSMODEL_H
#define PRODUCTSTATISTICSMODEL_H

#include <QObject>

class ProductStatisticsModel : QObject
{
    Q_OBJECT

public:
    quint64 mProductSeq  = 0;
    int     mProductNo   = 0;
    QString mProductName = "";
    qint64  mUnderCnt    = 0;
    qint64  mUnderWCnt   = 0;
    qint64  mNormalCnt   = 0;
    qint64  mOverWCnt    = 0;
    qint64  mOverCnt     = 0;
    qint64  mEtcCnt      = 0;
    qint64  mEtcMetalCnt = 0;
    qint64  mMDPassCnt   = 0;
    qint64  mMDDetectCnt = 0;
    qint64  mTotalCnt    = 0;
    float   mMDNGRate    = 0;

public:
    void setValue(QString value)
    {
        QStringList fields = value.split(",");

        for(int i = 0; i < fields.size(); i ++)
        {
            QString key   = fields.at(i).split(":")[0];
            QString value = fields.at(i).split(":")[1];

            if     (key == "ProdcutSettingSeq"){mProductSeq  = value.toULongLong();}
            else if(key == "ProductNo"        ){mProductNo   = value.toInt()      ;}
            else if(key == "ProductName"      ){mProductName = value              ;}
            else if(key == "U"                ){mUnderCnt    = value.toLongLong() ;}
            else if(key == "UW"               ){mUnderWCnt   = value.toLongLong() ;}
            else if(key == "N"                ){mNormalCnt   = value.toLongLong() ;}
            else if(key == "OW"               ){mOverWCnt    = value.toLongLong() ;}
            else if(key == "O"                ){mOverCnt     = value.toLongLong() ;}
            else if(key == "ETC"              ){mEtcCnt      = value.toLongLong() ;}
            else if(key == "WC MD F"          ){mEtcMetalCnt = value.toLongLong() ;}
            else if(key == "MD F"             ){mMDDetectCnt = value.toLongLong() ;}
            else if(key == "MD P"             ){mMDPassCnt   = value.toLongLong() ;}
        }

        mTotalCnt = mUnderCnt + mUnderWCnt + mNormalCnt + mOverWCnt + mOverCnt + mEtcCnt + mEtcMetalCnt;
        //mMDNGRate = mTotalCnt == 0 ? 0 : mMDDetectCnt / mTotalCnt;
    }

    void setValue(ProductStatisticsModel * pValue)
    {
        mProductNo   = pValue->mProductNo  ;
        mProductName = pValue->mProductName;
        mUnderCnt    = pValue->mUnderCnt   ;
        mUnderWCnt   = pValue->mUnderWCnt  ;
        mNormalCnt   = pValue->mNormalCnt  ;
        mOverWCnt    = pValue->mOverWCnt   ;
        mOverCnt     = pValue->mOverCnt    ;
        mEtcCnt      = pValue->mEtcCnt     ;
        mEtcMetalCnt = pValue->mEtcMetalCnt;
        mMDPassCnt   = pValue->mMDPassCnt  ;
        mMDDetectCnt = pValue->mMDDetectCnt;

        mTotalCnt = mUnderCnt + mUnderWCnt + mNormalCnt + mOverWCnt + mOverCnt + mEtcCnt + mEtcMetalCnt;
        //mMDNGRate = mMDDetectCnt / mTotalCnt;
    }

    void addValue(ProductStatisticsModel * pValue)
    {
        mProductNo   = pValue->mProductNo  ;
        mProductName = pValue->mProductName;
        mUnderCnt    = mUnderCnt    + pValue->mUnderCnt   ;
        mUnderWCnt   = mUnderWCnt   + pValue->mUnderWCnt  ;
        mNormalCnt   = mNormalCnt   + pValue->mNormalCnt  ;
        mOverWCnt    = mOverWCnt    + pValue->mOverWCnt   ;
        mOverCnt     = mOverCnt     + pValue->mOverCnt    ;
        mEtcCnt      = mEtcCnt      + pValue->mEtcCnt     ;
        mEtcMetalCnt = mEtcMetalCnt + pValue->mEtcMetalCnt;
        mMDPassCnt   = mMDPassCnt   + pValue->mMDPassCnt  ;
        mMDDetectCnt = mMDDetectCnt + pValue->mMDDetectCnt;

        mTotalCnt = mUnderCnt + mUnderWCnt + mNormalCnt + mOverWCnt + mOverCnt + mEtcCnt + mEtcMetalCnt;
        //mMDNGRate = mMDDetectCnt / mTotalCnt;
    }

    void reset()
    {
        mProductSeq  = 0;
        mProductNo   = 0;
        mProductName = "";
        mUnderCnt    = 0;
        mUnderWCnt   = 0;
        mNormalCnt   = 0;
        mOverWCnt    = 0;
        mOverCnt     = 0;
        mEtcCnt      = 0;
        mEtcMetalCnt = 0;
        mMDPassCnt   = 0;
        mMDDetectCnt = 0;
        mTotalCnt    = 0;
        mMDNGRate    = 0;
    }
    explicit ProductStatisticsModel(QObject *parent = nullptr):QObject(parent){}
};
#endif // PRODUCTSTATISTICSMODEL_H
