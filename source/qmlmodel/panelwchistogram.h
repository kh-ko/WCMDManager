#ifndef PANELWCHISTOGRAM_H
#define PANELWCHISTOGRAM_H
#include <QObject>
#include <QDebug>

#include "source/service/util/svcconnectutil.h"
#include "source/service/coreservice.h"

class PanelWCHistogramModel : public QObject
{
    Q_OBJECT

private:
    CoreService * mpCoreService;

    int     mXMin           = 0;
    int     mXMax           = 0;
    int     mXGab           = 0;
    int     mYGab           = 1;
    quint32 mListYValue[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    quint32 mListXValue[11] = {0,0,0,0,0,0,0,0,0,0,0,};

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
    Q_INVOKABLE quint32 onCommandGetYValue(int idx)
    {
        return mListYValue[idx];
    }
    Q_INVOKABLE int onCommandGetYGab()
    {
        return mYGab;
    }
    void onChangedIsLoading(bool value)
    {
        if(value == false)
        {
            loadData(-1, -1);
        }
    }

    void onChangedWCProductSeq()
    {
        loadData(-1, -1);
    }
public:
    void loadData(int xMin, int xMax)
    {
        PDSettingDto setting = pDLoaderSvc->mDailyHis.mPH.findSettingDto(pLSettingSvc->mWCProductSeq);

        if(xMin == -1 || xMax == -1)
        {
            mXMin = setting.mWCUnderWeight;//pWCProduct->mUnderSettingValue;
            mXMax = setting.mWCOverWeight ;//pWCProduct->mOverSettingValue ;

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

        PDWCStatsDto wcStats = pDLoaderSvc->mDailyHis.mEH.findPDWCStatsDto(setting.mSeq);

        foreach(quint32 value, wcStats.mTotalTrends)
        {
            insertYValue(value);
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

    void insertYValue(quint32 value)
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
        ENABLE_SLOT_DLOAD_CHANGED_IS_LOADING;
        ENABLE_SLOT_LSETTING_CHANGED_SEL_WC_PD;

        onChangedIsLoading(pDLoaderSvc->mIsLoading);
        onChangedWCProductSeq();
    }
};

#endif // PANELWCHISTOGRAM_H
