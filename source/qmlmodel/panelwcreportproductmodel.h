#ifndef PANELWCREPORTPRODUCTMODEL_H
#define PANELWCREPORTPRODUCTMODEL_H

#include <QObject>
#include <QtMath>
#include <QDebug>

class PanelWCReportProductModel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mNumName                   READ getNumName                  NOTIFY signalEventChangedNumName                 )
    Q_PROPERTY(int     mUnderSettingValue         READ getUnderSettingValue        NOTIFY signalEventChangedUnderSettingValue       )
    Q_PROPERTY(int     mUnderWarningSettingValue  READ getUnderWarningSettingValue NOTIFY signalEventChangedUnderWarningSettingValue)
    Q_PROPERTY(int     mNormalSettingValue        READ getNormalSettingValue       NOTIFY signalEventChangedNormalSettingValue      )
    Q_PROPERTY(int     mOverSettingValue          READ getOverSettingValue         NOTIFY signalEventChangedOverSettingValue        )
    Q_PROPERTY(int     mOverWarningSettingValue   READ getOverWarningSettingValue  NOTIFY signalEventChangedOverWarningSettingValue )
    Q_PROPERTY(int     mTareSettingValue          READ getTareSettingValue         NOTIFY signalEventChangedTareSettingValue        )
    Q_PROPERTY(int     mTotalCnt                  READ getTotalCnt                 NOTIFY signalEventChangedTotalCnt                )
    Q_PROPERTY(qint64  mTotalWeight               READ getTotalWeight              NOTIFY signalEventChangedTotalWeight             )
    Q_PROPERTY(double  mTotalAvgWeight            READ getTotalAvgWeight           NOTIFY signalEventChangedTotalAvgWeight          )
    Q_PROPERTY(double  mTotalSD                   READ getTotalSD                  NOTIFY signalEventChangedTotalSD                 )
    Q_PROPERTY(double  mTotalCV                   READ getTotalCV                  NOTIFY signalEventChangedTotalCV                 )
    Q_PROPERTY(int     mTradeCnt                  READ getTradeCnt                 NOTIFY signalEventChangedTradeCnt                )
    Q_PROPERTY(qint64  mTradeWeight               READ getTradeWeight              NOTIFY signalEventChangedTradeWeight             )
    Q_PROPERTY(double  mTradeAvgWeight            READ getTradeAvgWeight           NOTIFY signalEventChangedTradeAvgWeight          )
    Q_PROPERTY(double  mTradeSD                   READ getTradeSD                  NOTIFY signalEventChangedTradeSD                 )
    Q_PROPERTY(double  mTradeCV                   READ getTradeCV                  NOTIFY signalEventChangedTradeCV                 )
    Q_PROPERTY(int     mOverCnt                   READ getOverCnt                  NOTIFY signalEventChangedOverCnt                 )
    Q_PROPERTY(int     mUnderCnt                  READ getUnderCnt                 NOTIFY signalEventChangedUnderCnt                )
    Q_PROPERTY(int     mEtcCnt                    READ getEtcCnt                   NOTIFY signalEventChangedEtcCnt                  )
    Q_PROPERTY(int     mMinWeight                 READ getMinWeight                NOTIFY signalEventChangedMinWeight               )
    Q_PROPERTY(int     mMaxWeight                 READ getMaxWeight                NOTIFY signalEventChangedMaxWeight               )

public:
    quint64 mSeq                      = 0;
    int     mNo                       = 0;
    QString mName                     = "";
    QString mNumName                  = "";
    int     mUnderSettingValue        = 0;
    int     mUnderWarningSettingValue = 0;
    int     mNormalSettingValue       = 0;
    int     mOverSettingValue         = 0;
    int     mOverWarningSettingValue  = 0;
    int     mTareSettingValue         = 0;
    int     mTotalCnt                 = 0;
    qint64  mTotalWeight              = 0;
    double  mTotalAvgWeight           = 0;
    double  mTotalSD                  = 0;
    double  mTotalCV                  = 0.0f;
    int     mTradeCnt                 = 0;
    qint64  mTradeWeight              = 0;
    double  mTradeAvgWeight           = 0;
    double  mTradeSD                  = 0;
    double  mTradeCV                  = 0.0f;
    int     mOverCnt                  = 0;
    int     mUnderCnt                 = 0;
    int     mEtcCnt                   = 0;
    int     mMinWeight                = 0;
    int     mMaxWeight                = 0;

    QList<int> mListTotalWeightValue;
    QList<int> mListTradeWeightValue;
    QList<int> mListGMinValue;
    QList<int> mListGMaxValue;

    quint64 getSeq                     (){ return mSeq                     ; }
    int     getNo                      (){ return mNo                      ; }
    QString getName                    (){ return mName                    ; }
    QString getNumName                 (){ return mNumName                 ; }
    int     getUnderSettingValue       (){ return mUnderSettingValue       ; }
    int     getUnderWarningSettingValue(){ return mUnderWarningSettingValue; }
    int     getNormalSettingValue      (){ return mNormalSettingValue      ; }
    int     getOverSettingValue        (){ return mOverSettingValue        ; }
    int     getOverWarningSettingValue (){ return mOverWarningSettingValue ; }
    int     getTareSettingValue        (){ return mTareSettingValue        ; }
    int     getTotalCnt                (){ return mTotalCnt                ; }
    qint64  getTotalWeight             (){ return mTotalWeight             ; }
    double  getTotalAvgWeight          (){ return mTotalAvgWeight          ; }
    double  getTotalSD                 (){ return mTotalSD                 ; }
    double  getTotalCV                 (){ return mTotalCV                 ; }
    int     getTradeCnt                (){ return mTradeCnt                ; }
    qint64  getTradeWeight             (){ return mTradeWeight             ; }
    double  getTradeAvgWeight          (){ return mTradeAvgWeight          ; }
    double  getTradeSD                 (){ return mTradeSD                 ; }
    double  getTradeCV                 (){ return mTradeCV                 ; }
    int     getOverCnt                 (){ return mOverCnt                 ; }
    int     getUnderCnt                (){ return mUnderCnt                ; }
    int     getEtcCnt                  (){ return mEtcCnt                  ; }
    int     getMinWeight               (){ return mMinWeight               ; }
    int     getMaxWeight               (){ return mMaxWeight               ; }

private:
    void setSeq                     (quint64 value){if( mSeq                      == value) return; mSeq                      = value;}
    void setNo                      (int     value){if( mNo                       == value) return; mNo                       = value;}
    void setName                    (QString value){if( mName                     == value) return; mName                     = value;}
    void setNumName                 (QString value){if( mNumName                  == value) return; mNumName                  = value; emit signalEventChangedNumName                 (mNumName                 );}
    void setUnderSettingValue       (int     value){if( mUnderSettingValue        == value) return; mUnderSettingValue        = value; emit signalEventChangedUnderSettingValue       (mUnderSettingValue       );}
    void setUnderWarningSettingValue(int     value){if( mUnderWarningSettingValue == value) return; mUnderWarningSettingValue = value; emit signalEventChangedUnderWarningSettingValue(mUnderWarningSettingValue);}
    void setNormalSettingValue      (int     value){if( mNormalSettingValue       == value) return; mNormalSettingValue       = value; emit signalEventChangedNormalSettingValue      (mNormalSettingValue      );}
    void setOverSettingValue        (int     value){if( mOverSettingValue         == value) return; mOverSettingValue         = value; emit signalEventChangedOverSettingValue        (mOverSettingValue        );}
    void setOverWarningSettingValue (int     value){if( mOverWarningSettingValue  == value) return; mOverWarningSettingValue  = value; emit signalEventChangedOverWarningSettingValue (mOverWarningSettingValue );}
    void setTareSettingValue        (int     value){if( mTareSettingValue         == value) return; mTareSettingValue         = value; emit signalEventChangedTareSettingValue        (mTareSettingValue        );}
    void setTotalCnt                (int     value){if( mTotalCnt                 == value) return; mTotalCnt                 = value; emit signalEventChangedTotalCnt                (mTotalCnt                );}
    void setTotalWeight             (qint64  value){if( mTotalWeight              == value) return; mTotalWeight              = value; emit signalEventChangedTotalWeight             (mTotalWeight             );}
    void setTotalAvgWeight          (double  value){if( mTotalAvgWeight           == value) return; mTotalAvgWeight           = value; emit signalEventChangedTotalAvgWeight          (mTotalAvgWeight          );}
    void setTotalSD                 (double  value){if( mTotalSD                  == value) return; mTotalSD                  = value; emit signalEventChangedTotalSD                 (mTotalSD                 );}
    void setTotalCV                 (double  value){if( mTotalCV                  == value) return; mTotalCV                  = value; emit signalEventChangedTotalCV                 (mTotalCV                 );}
    void setTradeCnt                (int     value){if( mTradeCnt                 == value) return; mTradeCnt                 = value; emit signalEventChangedTradeCnt                (mTradeCnt                );}
    void setTradeWeight             (qint64  value){if( mTradeWeight              == value) return; mTradeWeight              = value; emit signalEventChangedTradeWeight             (mTradeWeight             );}
    void setTradeAvgWeight          (double  value){if( mTradeAvgWeight           == value) return; mTradeAvgWeight           = value; emit signalEventChangedTradeAvgWeight          (mTradeAvgWeight          );}
    void setTradeSD                 (double  value){if( mTradeSD                  == value) return; mTradeSD                  = value; emit signalEventChangedTradeSD                 (mTradeSD                 );}
    void setTradeCV                 (double  value){if( mTradeCV                  == value) return; mTradeCV                  = value; emit signalEventChangedTradeCV                 (mTradeCV                 );}
    void setOverCnt                 (int     value){if( mOverCnt                  == value) return; mOverCnt                  = value; emit signalEventChangedOverCnt                 (mOverCnt                 );}
    void setUnderCnt                (int     value){if( mUnderCnt                 == value) return; mUnderCnt                 = value; emit signalEventChangedUnderCnt                (mUnderCnt                );}
    void setEtcCnt                  (int     value){if( mEtcCnt                   == value) return; mEtcCnt                   = value; emit signalEventChangedEtcCnt                  (mEtcCnt                  );}
    void setMinWeight               (int     value){if( mMinWeight                == value) return; mMinWeight                = value; emit signalEventChangedMinWeight               (mMinWeight               );}
    void setMaxWeight               (int     value){if( mMaxWeight                == value) return; mMaxWeight                = value; emit signalEventChangedMaxWeight               (mMaxWeight               );}

signals:
    void signalEventChangedNumName                 (QString value);
    void signalEventChangedUnderSettingValue       (int     value);
    void signalEventChangedUnderWarningSettingValue(int     value);
    void signalEventChangedNormalSettingValue      (int     value);
    void signalEventChangedOverSettingValue        (int     value);
    void signalEventChangedOverWarningSettingValue (int     value);
    void signalEventChangedTareSettingValue        (int     value);
    void signalEventChangedTotalCnt                (int     value);
    void signalEventChangedTotalWeight             (qint64  value);
    void signalEventChangedTotalAvgWeight          (double  value);
    void signalEventChangedTotalSD                 (double  value);
    void signalEventChangedTotalCV                 (double  value);
    void signalEventChangedTradeCnt                (int     value);
    void signalEventChangedTradeWeight             (qint64  value);
    void signalEventChangedTradeAvgWeight          (double  value);
    void signalEventChangedTradeSD                 (double  value);
    void signalEventChangedTradeCV                 (double  value);
    void signalEventChangedOverCnt                 (int     value);
    void signalEventChangedUnderCnt                (int     value);
    void signalEventChangedEtcCnt                  (int     value);
    void signalEventChangedMinWeight               (int     value);
    void signalEventChangedMaxWeight               (int     value);

public slots:
    Q_INVOKABLE void onCommandSetNumName                 (QString value){setNumName                 (value);}
    Q_INVOKABLE void onCommandSetUnderSettingValue       (int     value){setUnderSettingValue       (value);}
    Q_INVOKABLE void onCommandSetUnderWarningSettingValue(int     value){setUnderWarningSettingValue(value);}
    Q_INVOKABLE void onCommandSetNormalSettingValue      (int     value){setNormalSettingValue      (value);}
    Q_INVOKABLE void onCommandSetOverSettingValue        (int     value){setOverSettingValue        (value);}
    Q_INVOKABLE void onCommandSetOverWarningSettingValue (int     value){setOverWarningSettingValue (value);}
    Q_INVOKABLE void onCommandSetTareSettingValue        (int     value){setTareSettingValue        (value);}
    Q_INVOKABLE void onCommandSetTotalCnt                (int     value){setTotalCnt                (value);}
    Q_INVOKABLE void onCommandSetTotalWeight             (qint64  value){setTotalWeight             (value);}
    Q_INVOKABLE void onCommandSetTotalAvgWeight          (double  value){setTotalAvgWeight          (value);}
    Q_INVOKABLE void onCommandSetTotalSD                 (double  value){setTotalSD                 (value);}
    Q_INVOKABLE void onCommandSetTotalCV                 (double  value){setTotalCV                 (value);}
    Q_INVOKABLE void onCommandSetTradeCnt                (int     value){setTradeCnt                (value);}
    Q_INVOKABLE void onCommandSetTradeWeight             (qint64  value){setTradeWeight             (value);}
    Q_INVOKABLE void onCommandSetTradeAvgWeight          (double  value){setTradeAvgWeight          (value);}
    Q_INVOKABLE void onCommandSetTradeSD                 (double  value){setTradeSD                 (value);}
    Q_INVOKABLE void onCommandSetTradeCV                 (double  value){setTradeCV                 (value);}
    Q_INVOKABLE void onCommandSetOverCnt                 (int     value){setOverCnt                 (value);}
    Q_INVOKABLE void onCommandSetUnderCnt                (int     value){setUnderCnt                (value);}
    Q_INVOKABLE void onCommandSetEtcCnt                  (int     value){setEtcCnt                  (value);}
    Q_INVOKABLE void onCommandSetMinWeight               (int     value){setMinWeight               (value);}
    Q_INVOKABLE void onCommandSetMaxWeight               (int     value){setMaxWeight               (value);}

public:
    bool setValueFromStrStatistics(QString value)
    {

        QStringList fields = value.split(",");

        for(int i = 0; i < fields.size(); i ++)
        {
            QString key   = fields.at(i).split(":")[0];
            QString value = fields.at(i).split(":")[1];

            if     (key == "ProdcutSettingSeq"){mSeq  = value.toULongLong();}
            else if(key == "ProductNo"        ){mNo   = value.toInt()      ;}
            else if(key == "ProductName"      ){mName = value              ;}
        }

        if(mSeq == 0)
            return false;

        mNumName = QString("%1 %2").arg(QString::number(mNo).rightJustified(3, '0')).arg(mName);

        return true;

    }

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

        calGraphValue();

        mListTotalWeightValue.clear();
        mListTradeWeightValue.clear();
    }

    void calGraphValue()
    {
        int dataCnt = mListTotalWeightValue.size();
        int gPointCnt = 1000;
        int pointIdx = 0;
        int pointCnt = dataCnt > gPointCnt ? gPointCnt : dataCnt;

        mListGMinValue.clear();
        mListGMaxValue.clear();

        if(mListTotalWeightValue.size() < 1)
            return;

        float pointGap = (float)pointCnt / (float)dataCnt;

        for(int i = 0; i < dataCnt; i ++)
        {
            pointIdx = ((float)i) * pointGap;

            if(mListGMinValue.size() > pointIdx)
            {
                if(mListGMinValue[pointIdx] > mListTotalWeightValue[i])
                    mListGMinValue[pointIdx] = mListTotalWeightValue[i];

                if(mListGMaxValue[pointIdx] < mListTotalWeightValue[i])
                    mListGMaxValue[pointIdx] = mListTotalWeightValue[i];
            }
            else
            {
                mListGMinValue.append(mListTotalWeightValue[i]);
                mListGMaxValue.append(mListTotalWeightValue[i]);
            }
        }
    }

    explicit PanelWCReportProductModel(QObject *parent = nullptr):QObject(parent){}
};
#endif // PANELWCREPORTPRODUCTMODEL_H
