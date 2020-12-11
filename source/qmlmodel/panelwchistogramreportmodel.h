#ifndef PANELWCHISTOGRAMREPORTMODEL_H
#define PANELWCHISTOGRAMREPORTMODEL_H
#include <QObject>
#include <QDebug>

#include "source/history/dailyhistory.h"
#include "source/service/coreservice.h"

class PanelWCHistogramReportModel : public QObject
{
    Q_OBJECT

private:
    int    mXMin           = 0;
    int    mXMax           = 0;
    int    mXGab           = 0;
    int    mYGab           = 1;
    int    mListYValue[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int    mListXValue[11] = {0,0,0,0,0,0,0,0,0,0,0,};

    int  getXMin     (){ return mXMin     ; }
    int  getXMax     (){ return mXMax     ; }
    int  getYGab     (){ return mYGab     ; }

    void setXMin     (int  value){ if(mXMin      == value) return; mXMin      = value; /*emit signalEventChangedXMin     (mXMin     );*/ }
    void setXMax     (int  value){ if(mXMax      == value) return; mXMax      = value; /*emit signalEventChangedXMax     (mXMax     );*/ }
    void setYGab     (int  value){ if(mYGab      == value) return; mYGab      = value; /*emit signalEventChangedYGab     (mYGab     );*/ }

signals:
    void signalEventChangedGraphData();

public slots:
    Q_INVOKABLE int onCommandGetXMin()
    {
        return mXMin;
    }
    Q_INVOKABLE int onCommandGetXMax()
    {
        return mXMax;
    }
    Q_INVOKABLE int onCommandGetXValue(int idx)
    {
        return mListXValue[idx];
    }
    Q_INVOKABLE int onCommandGetYValue(int idx)
    {
        return mListYValue[idx];
    }
    Q_INVOKABLE int onCommandGetYGab()
    {
        return mYGab;
    }

public:
    void reset()
    {
        mXMin = 0;
        mXMax = 0;
        mXGab = 0;
        mYGab = 1;

        memset(mListYValue, 0x00, sizeof(int) * 12);
        memset(mListXValue, 0x00, sizeof(int) * 11);
    }
/*
    void loadData(WeightCheckerProduct * pWCProduct)
    {
        if(pWCProduct == nullptr)
        {
            reset();
            return;
        }
        mXMin = pWCProduct->mUnderSettingValue;
        mXMax = pWCProduct->mOverSettingValue ;


        mXGab = (mXMax - mXMin) / 10;

        for(int i = 0; i < 11; i ++)
        {
            mListXValue[i] =mXMin + (i*mXGab);
        }

        memset(mListYValue, 0x00, sizeof(int) * 12);

        if(pWCProduct != nullptr)
        {
            for(int i = 0; i < pWCProduct->mListTotalWeightValue.size(); i ++)
            {
                int value = pWCProduct->mListTotalWeightValue[i];

                insertYValue(value);
            }
        }

        int yMax = 0;

        for(int i = 0; i < 12; i ++)
        {
            if(yMax < mListYValue[i])
                yMax = mListYValue[i];
        }

        if(yMax < 10)
        {
            mYGab = 1;
        }
        else
        {
            mYGab = ((float)yMax / (float)10.0f) + 0.9f;
        }

        QString strYMax = QString("%1").arg(yMax);


        emit signalEventChangedGraphData();
    }
*/
    void insertYValue(int value)
    {
        for(int i = 0; i < 12; i ++)
        {
            if(i == 11 || mListXValue[i] > value)
            {
                mListYValue[i] = mListYValue[i] + 1;
                return;
            }
        }
    }

    explicit PanelWCHistogramReportModel(QObject *parent = nullptr):QObject(parent)
    {
    }
};
#endif // PANELWCHISTOGRAMREPORTMODEL_H
