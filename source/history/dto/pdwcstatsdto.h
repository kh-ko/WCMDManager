#ifndef PDWCSTATSDTO_H
#define PDWCSTATSDTO_H

#include <QObject>
#include <QtMath>
#include "source/history/dto/pdsettingdto.h"
#include "source/history/dto/pdstatsdto.h"
#include "source/history/dto/eventdto.h"

class PDWCStatsDto
{
public:
    quint64      mSeq                = 0;
    quint32      mWCOCnt             = 0;
    quint32      mWCOWCnt            = 0;
    quint32      mWCNorCnt           = 0;
    quint32      mWCUCnt             = 0;
    quint32      mWCUWCnt            = 0;
    quint32      mWCEtcCnt           = 0;
    quint32      mWCMDCnt            = 0;
    quint32      mMDPassCnt          = 0;
    quint32      mMDFailCnt          = 0;
    quint32      mWCTotalCnt         = 0;
    quint32      mMDTotalCnt         = 0;
    qint64       mTotalWeight        = 0;
    int          mTotalAvgWeight     = 0;
    int          mTotalSD            = 0;
    double       mTotalCV            = 0;
    qint64       mTradeWeight        = 0;
    int          mTradeAvgWeight     = 0;
    int          mTradeSD            = 0;
    double       mTradeCV            = 0;
    int          mTotalMinWeight     = 0;
    int          mTotalMaxWeight     = 0;
    int          mTradeMinWeight     = 0;
    int          mTradeMaxWeight     = 0;

    QList<quint32>   mTotalTrends;
    QList<quint32>   mTradeTrends;


    PDWCStatsDto(){}
    PDWCStatsDto(const PDWCStatsDto& copy) :
        mSeq           (copy.mSeq           ),
        mWCOCnt        (copy.mWCOCnt        ),
        mWCOWCnt       (copy.mWCOWCnt       ),
        mWCNorCnt      (copy.mWCNorCnt      ),
        mWCUCnt        (copy.mWCUCnt        ),
        mWCUWCnt       (copy.mWCUWCnt       ),
        mWCEtcCnt      (copy.mWCEtcCnt      ),
        mWCMDCnt       (copy.mWCMDCnt       ),
        mMDPassCnt     (copy.mMDPassCnt     ),
        mMDFailCnt     (copy.mMDFailCnt     ),
        mWCTotalCnt    (copy.mWCTotalCnt    ),
        mMDTotalCnt    (copy.mMDTotalCnt    ),
        mTotalWeight   (copy.mTotalWeight   ),
        mTotalAvgWeight(copy.mTotalAvgWeight),
        mTotalSD       (copy.mTotalSD       ),
        mTotalCV       (copy.mTotalCV       ),
        mTradeWeight   (copy.mTradeWeight   ),
        mTradeAvgWeight(copy.mTradeAvgWeight),
        mTradeSD       (copy.mTradeSD       ),
        mTradeCV       (copy.mTradeCV       ),
        mTotalMinWeight(copy.mTotalMinWeight),
        mTotalMaxWeight(copy.mTotalMaxWeight),
        mTradeMinWeight(copy.mTradeMinWeight),
        mTradeMaxWeight(copy.mTradeMaxWeight),
        mTotalTrends   (copy.mTotalTrends   ),
        mTradeTrends   (copy.mTradeTrends   ){}
    ~PDWCStatsDto(){}

    PDWCStatsDto& operator=(const PDWCStatsDto& other)
    {
        mSeq            = other.mSeq           ;
        mWCOCnt         = other.mWCOCnt        ;
        mWCOWCnt        = other.mWCOWCnt       ;
        mWCNorCnt       = other.mWCNorCnt      ;
        mWCUCnt         = other.mWCUCnt        ;
        mWCUWCnt        = other.mWCUWCnt       ;
        mWCEtcCnt       = other.mWCEtcCnt      ;
        mWCMDCnt        = other.mWCMDCnt       ;
        mMDPassCnt      = other.mMDPassCnt     ;
        mMDFailCnt      = other.mMDFailCnt     ;
        mWCTotalCnt     = other.mWCTotalCnt    ;
        mMDTotalCnt     = other.mMDTotalCnt    ;
        mTotalWeight    = other.mTotalWeight   ;
        mTotalAvgWeight = other.mTotalAvgWeight;
        mTotalSD        = other.mTotalSD       ;
        mTotalCV        = other.mTotalCV       ;
        mTradeWeight    = other.mTradeWeight   ;
        mTradeAvgWeight = other.mTradeAvgWeight;
        mTradeSD        = other.mTradeSD       ;
        mTradeCV        = other.mTradeCV       ;
        mTotalMinWeight = other.mTotalMinWeight;
        mTotalMaxWeight = other.mTotalMaxWeight;
        mTradeMinWeight = other.mTradeMinWeight;
        mTradeMaxWeight = other.mTradeMaxWeight;
        mTotalTrends    = other.mTotalTrends   ;
        mTradeTrends    = other.mTradeTrends   ;

        return *this;
    }

    void addEvent(EventDto event)
    {
        bool isTrade = false;

        switch(event.mEType)
        {
        case EnumDef::ET_WEIGHT_NORMAL          : mWCNorCnt++; isTrade = true; break;
        case EnumDef::ET_WEIGHT_UNDER_WARNING   : mWCUWCnt ++; isTrade = true; break;
        case EnumDef::ET_WEIGHT_OVER_WARNING    : mWCOWCnt ++; isTrade = true; break;
        case EnumDef::ET_WEIGHT_UNDER           : mWCUCnt  ++; break;
        case EnumDef::ET_WEIGHT_OVER            : mWCOCnt  ++; break;
        case EnumDef::ET_WEIGHT_ETCERROR        : mWCEtcCnt++; break;
        case EnumDef::ET_WEIGHT_ETC_METAL_ERROR : mWCMDCnt ++; break;
        default: return;
        }

        if(mTotalTrends.size() == 0            ){mTotalMinWeight = event.mEValue; mTotalMaxWeight = event.mEValue;}
        if(mTotalMinWeight > (int)event.mEValue){mTotalMinWeight = event.mEValue;                                 }
        if(mTotalMaxWeight < (int)event.mEValue){mTotalMaxWeight = event.mEValue;                                 }

        mWCTotalCnt++;
        mTotalWeight = mTotalWeight + event.mEValue;

        if(mSeq == 1)
        {
            qDebug() << "[debug] eventValue = " << event.mEValue << ", total = " << mTotalWeight;
        }
        mTotalTrends.append(event.mEValue);

        if(isTrade)
        {
            if(mTradeTrends.size() == 0            ){mTradeMinWeight = event.mEValue; mTradeMaxWeight = event.mEValue;}
            if(mTradeMinWeight > (int)event.mEValue){mTradeMinWeight = event.mEValue;                                 }
            if(mTradeMaxWeight < (int)event.mEValue){mTradeMaxWeight = event.mEValue;                                 }

            mTradeWeight = mTradeWeight + event.mEValue;
            mTradeTrends.append(event.mEValue);
        }
    }

    void calSDCV()
    {
        double deviationSum               = 0;
        double variance                   = 0;

        mTotalAvgWeight = mWCTotalCnt == 0 ? 0 : mTotalWeight/mWCTotalCnt;

        for(int i = 0; i < mTotalTrends.size(); i ++)
        {
            deviationSum += (mTotalTrends[i] - mTotalAvgWeight) * (mTotalTrends[i] - mTotalAvgWeight);
        }

        variance = mTotalTrends.size() == 0 ? 0 : deviationSum / (double) mTotalTrends.size();

        mTotalSD = qSqrt(variance);
        mTotalCV = mTotalAvgWeight == 0 ? 0 : (mTotalSD / (double)mTotalAvgWeight) * 100;

        deviationSum = 0;
        variance = 0;

        quint32 tradeTotalCnt = mWCNorCnt + mWCUWCnt + mWCOWCnt;
        mTradeAvgWeight = tradeTotalCnt == 0 ? 0 : mTradeWeight/tradeTotalCnt;

        for(int i = 0; i < mTradeTrends.size(); i ++)
        {
            deviationSum += (mTradeTrends[i] - mTradeAvgWeight) * (mTradeTrends[i] - mTradeAvgWeight);
        }

        variance = mTradeTrends.size() == 0 ? 0 : deviationSum / (double) mTradeTrends.size();

        mTradeSD = qSqrt(variance);
        mTradeCV = mTradeAvgWeight == 0 ? 0 : (mTradeSD / (double)mTradeAvgWeight) * 100;
    }
};

Q_DECLARE_METATYPE(PDWCStatsDto);

#endif // PDWCSTATSDTO_H
