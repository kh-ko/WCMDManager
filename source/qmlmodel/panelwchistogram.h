#ifndef PANELWCHISTOGRAM_H
#define PANELWCHISTOGRAM_H
#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"

class PanelWCHistogramModel : public QObject
{
    Q_OBJECT

private:
    CoreService * mpCoreService;

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
    //void signalEventChangedProduct();
    //void signalEventChangedXMin     (int  value);
    //void signalEventChangedXMax     (int  value);
    //void signalEventChangedYGab     (int  value);

public slots:
    Q_INVOKABLE void onCommandSetRange(int xMin, int xMax)
    {
        loadData(xMin, xMax);
    }
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
    void onSignalEventChangedIsLoading(bool value)
    {
        if(value == false)
        {
            loadData(-1, -1);
        }
    }

    void onSignalEventChangedProductSeq()
    {
        loadData(-1, -1);
    }
public:
    void loadData(int xMin, int xMax)
    {
        WeightCheckerProduct * pWCProduct = nullptr;

        quint64 mPSeq = mpCoreService->mLSettingService.mWCProductSeq;

        pWCProduct = mpCoreService->mDataLoader.mWCModel.findProductBySeq(mPSeq);

        if(xMin == -1 || xMax == -1)
        {
            if(pWCProduct == nullptr)
            {
                mXMin = 0; mXMax = 0;
            }
            else
            {
                mXMin = pWCProduct->mUnderSettingValue;
                mXMax = pWCProduct->mOverSettingValue ;
            }
        }
        else
        {
            mXMin = xMin;
            mXMax = xMax;
        }

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

    explicit PanelWCHistogramModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        connect(&mpCoreService->mDataLoader     , SIGNAL(signalEventChangedIsLoading   (bool)), this, SLOT(onSignalEventChangedIsLoading (bool)));
        connect(&mpCoreService->mLSettingService, SIGNAL(signalEventChangedWCProductSeq(    )), this, SLOT(onSignalEventChangedProductSeq(    )));

        onSignalEventChangedIsLoading(mpCoreService->mDataLoader.mIsLoading);
    }
};

#endif // PANELWCHISTOGRAM_H
