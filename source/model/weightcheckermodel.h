#ifndef WEIGHTCHECKERMODEL_H
#define WEIGHTCHECKERMODEL_H

#include <QObject>
#include <QtMath>
#include <QDebug>
#include "source/model/productsettingmodel.h"

class WeightCheckerProduct: QObject
{
    Q_OBJECT

public:
    quint64 mSeq                      ;
    int     mNo                       ;
    QString mName                     ;
    int     mUnderSettingValue        ;
    int     mUnderWarningSettingValue ;
    int     mNormalSettingValue       ;
    int     mOverSettingValue         ;
    int     mOverWarningSettingValue  ;
    int     mTareSettingValue         ;
    int    mTotalCnt                  = 0;
    qint64 mTotalWeight               = 0;
    double mTotalAvgWeight            = 0;
    double mTotalSD                   = 0;
    double mTotalCV                   = 0.0f;
    int    mTradeCnt                  = 0;
    qint64 mTradeWeight               = 0;
    double mTradeAvgWeight            = 0;
    double mTradeSD                   = 0;
    double mTradeCV                   = 0.0f;
    int    mOverCnt                   = 0;
    int    mUnderCnt                  = 0;
    int    mEtcCnt                    = 0;
    int    mMinWeight                 = 0;
    int    mMaxWeight                 = 0;

    QList<int> mListTotalWeightValue;
    QList<int> mListTradeWeightValue;

    void addEvent(QString eventType, int value)
    {
        if     (eventType == "N"      ){mTotalCnt++; mTotalWeight = mTotalWeight + value; mTradeCnt++; mTradeWeight = mTradeWeight + value; mListTradeWeightValue.append(value);}
        else if(eventType == "UW"     ){mTotalCnt++; mTotalWeight = mTotalWeight + value; mTradeCnt++; mTradeWeight = mTradeWeight + value; mListTradeWeightValue.append(value);}
        else if(eventType == "OW"     ){mTotalCnt++; mTotalWeight = mTotalWeight + value; mTradeCnt++; mTradeWeight = mTradeWeight + value; mListTradeWeightValue.append(value);}
        else if(eventType == "U"      ){mTotalCnt++; mTotalWeight = mTotalWeight + value; mUnderCnt++; }
        else if(eventType == "O"      ){mTotalCnt++; mTotalWeight = mTotalWeight + value; mOverCnt ++; }
        else if(eventType == "ETC"    ){mTotalCnt++; mTotalWeight = mTotalWeight + value; mEtcCnt  ++; }
        else if(eventType == "WC MD F"){mTotalCnt++; mTotalWeight = mTotalWeight + value; mEtcCnt  ++; }
        else                           { return; }

        if(value != 0 && (mMinWeight > value || mMinWeight == 0))
            mMinWeight = value;

        if(mMaxWeight < value)
            mMaxWeight = value;

        mListTotalWeightValue.append(value);
    }

    void finishedAddEvent()
    {
        double deviationSum = 0;
        double variance = 0;

        if(mTotalCnt == 0)
        {
            mTotalAvgWeight = 0;
            mTotalSD = 0;
            mTotalCV = 0;
        }
        else
        {
            mTotalAvgWeight = ((double)mTotalWeight/(double)mTotalCnt);

            for(int i = 0; i < mListTotalWeightValue.size(); i ++)
            {
                int temp = (mListTotalWeightValue[i] - mTotalAvgWeight);
                deviationSum += (mListTotalWeightValue[i] - mTotalAvgWeight) * (mListTotalWeightValue[i] - mTotalAvgWeight);
            }

            variance = deviationSum / (double)mTotalCnt;

            mTotalSD = qSqrt(variance);
            mTotalCV = ((double)mTotalSD / mTotalAvgWeight) * 100;
        }

        deviationSum = 0;
        variance = 0;

        if(mTradeCnt == 0)
        {
            mTradeAvgWeight = 0;
            mTradeSD = 0;
            mTradeCV = 0;
        }
        else
        {
            mTradeAvgWeight = ((double)mTradeWeight/(double)mTradeCnt);

            for(int i = 0; i < mListTradeWeightValue.size(); i ++)
            {
                deviationSum += (mListTradeWeightValue[i] - mTradeAvgWeight) * (mListTradeWeightValue[i] - mTradeAvgWeight);
            }

            variance = deviationSum / mTradeCnt;

            mTradeSD = qSqrt(variance);
            mTradeCV = ((double)mTradeSD / mTradeAvgWeight) * 100;
        }
    }
    explicit WeightCheckerProduct(QObject *parent = nullptr):QObject(parent){}
};

class WeightCheckerModel : QObject
{
    Q_OBJECT

public:
    QList<WeightCheckerProduct * > mListProduct;
signals:

public:
    void reset()
    {
        for(int i = 0; i < mListProduct.size(); i ++)
        {
            delete mListProduct[i];
        }

        mListProduct.clear();
    }
    void setProduct(ProductSettingModel * pPs)
    {
        WeightCheckerProduct * pProduct = nullptr;

        pProduct = findProductBySeq(pPs->mSeq);

        if(pProduct == nullptr)
        {
            pProduct = new WeightCheckerProduct(this);
            mListProduct.append(pProduct);
        }

        pProduct->mSeq                      = pPs->mSeq;
        pProduct->mNo                       = pPs->mNo;
        pProduct->mName                     = pPs->mName;
        pProduct->mUnderSettingValue        = pPs->mUnderWeight;
        pProduct->mUnderWarningSettingValue = pPs->mUnderWarningWeight;
        pProduct->mNormalSettingValue       = pPs->mNormalWeight;
        pProduct->mOverSettingValue         = pPs->mOverWeight;
        pProduct->mOverWarningSettingValue  = pPs->mOverWarningWeight;
        pProduct->mTareSettingValue         = pPs->mTareWeight;
    }

    void addEvent(quint64 pseq, QString eventType, int value)
    {
        WeightCheckerProduct * pProduct = findProductBySeq(pseq);

        if(pProduct == nullptr)
        {
            qDebug() << "[WeightCheckerModel::addEvent]can not found pseq = " << pseq;
            return;
        }

        pProduct->addEvent(eventType, value);
    }
    WeightCheckerProduct * findProductBySeq(quint64 seq)
    {
        for(int i = 0; i < mListProduct.size(); i ++)
        {
            if(mListProduct[i]->mSeq == seq)
                return mListProduct[i];
        }
        return nullptr;
    }

    void finishedAddEvent()
    {
        for(int i = 0; i < mListProduct.size(); i ++)
        {
            WeightCheckerProduct * pMin = mListProduct.at(i);

            for(int j = i; j < mListProduct.size(); j ++)
            {
                 WeightCheckerProduct * pTemp = mListProduct.at(j);

                 if(pTemp->mNo < pMin->mNo)
                 {
                     mListProduct.replace(j, pMin);
                     pMin = pTemp;
                 }
            }
            pMin->finishedAddEvent();
            mListProduct.replace(i, pMin);
        }
    }
    explicit WeightCheckerModel(QObject *parent = nullptr):QObject(parent){}
};
#endif // WEIGHTCHECKERMODEL_H
