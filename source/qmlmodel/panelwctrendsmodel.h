#ifndef PANELWCTRENDSMODEL_H
#define PANELWCTRENDSMODEL_H
#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"

class PanelWCTrendsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool mIsNonData        READ getIsNonData      NOTIFY signalEventChangedIsNonData     )
    Q_PROPERTY(bool mMinMaxMode       READ getMinMaxMode     NOTIFY signalEventChangedMinMaxMode    )
    Q_PROPERTY(bool mFilterMode       READ getFilterMode     NOTIFY signalEventChangedFilterMode    )
    Q_PROPERTY(int  mDataMinWeight    READ getDataMinWeight  NOTIFY signalEventChangedDataMinWeight )
    Q_PROPERTY(int  mWeightGab        READ getWeightGab      NOTIFY signalEventChangedWeightGab     )
    Q_PROPERTY(int  mDataStartIdx     READ getDataStartIdx   NOTIFY signalEventChangedDataStartIdx  )
    Q_PROPERTY(int  mDataEndIdx       READ getDataEndIdx     NOTIFY signalEventChangedDataEndIdx    )
    Q_PROPERTY(int  mDataTotalCnt     READ getDataTotalCnt   NOTIFY signalEventChangedDataTotalCnt  )
    Q_PROPERTY(int  mDataGap          READ getDataGap        NOTIFY signalEventChangedDataGap       )
private:
    CoreService * mpCoreService;

    int  mCanvasWidth     = 0;
    int  mCanvasHeight   = 0;

    int mDataStartIdx    = 0;
    int mDataEndIdx      = 0;
    int mDataTotalCnt    = 0;
    int mDataGap         = 1;
    int mDataMinWeight   = 0;
    int mDataMaxWeight   = 0;
    int mDataWeightRange = 0;
    int mWeightGab       = 0;
    int mOverWeight      = 0;
    int mUnderWeight     = 0;

    bool mIsNonData      = true;
    bool mMinMaxMode     = false;
    bool mFilterMode     = false;

    QList<int> mListMin;
    QList<int> mListMax;
    QList<int> mDataList;

public:
    bool getIsNonData    (){ return mIsNonData    ;}
    bool getMinMaxMode   (){ return mMinMaxMode   ;}
    bool getFilterMode   (){ return mFilterMode   ;}
    int  getDataMinWeight(){ return mDataMinWeight;}
    int  getWeightGab    (){ return mWeightGab    ;}
    int  getDataStartIdx (){ return mDataStartIdx ;}
    int  getDataEndIdx   (){ return mDataEndIdx   ;}
    int  getDataTotalCnt (){ return mDataTotalCnt ;}
    int  getDataGap      (){ return mDataGap      ;}

    void setIsNonData    (bool value){ if(mIsNonData     == value) return; mIsNonData     = value; emit signalEventChangedIsNonData    (mIsNonData    ); }
    void setMinMaxMode   (bool value){ if(mMinMaxMode    == value) return; mMinMaxMode    = value; emit signalEventChangedMinMaxMode   (mMinMaxMode   ); }
    void setFilterMode   (bool value){ if(mFilterMode    == value) return; mFilterMode    = value; emit signalEventChangedFilterMode   (mFilterMode   ); }
    void setDataMinWeight(int  value){ if(mDataMinWeight == value) return; mDataMinWeight = value; emit signalEventChangedDataMinWeight(mDataMinWeight); }
    void setWeightGab    (int  value){ if(mWeightGab     == value) return; mWeightGab     = value; emit signalEventChangedWeightGab    (mWeightGab    ); }
    void setDataStartIdx (int  value){ if(mDataStartIdx  == value) return; mDataStartIdx  = value; emit signalEventChangedDataStartIdx (mDataStartIdx ); }
    void setDataEndIdx   (int  value){ if(mDataEndIdx    == value) return; mDataEndIdx    = value; emit signalEventChangedDataEndIdx   (mDataEndIdx   ); }
    void setDataTotalCnt (int  value){ if(mDataTotalCnt  == value) return; mDataTotalCnt  = value; emit signalEventChangedDataTotalCnt (mDataTotalCnt ); }
    void setDataGap      (int  value){ if(mDataGap       == value) return; mDataGap       = value; emit signalEventChangedDataGap      (mDataGap      ); }

signals:
    void signalEventChangedData();
    void signalEventChangedIsNonData    (bool value);
    void signalEventChangedMinMaxMode   (bool value);
    void signalEventChangedFilterMode   (bool value);
    void signalEventChangedDataMinWeight(int  value);
    void signalEventChangedWeightGab    (int  value);
    void signalEventChangedDataStartIdx (int  value);
    void signalEventChangedDataEndIdx   (int  value);
    void signalEventChangedDataTotalCnt (int  value);
    void signalEventChangedDataGap      (int  value);

public slots:
    Q_INVOKABLE void onCommandSetMinMaxMode(bool value)
    {
        setMinMaxMode(value);
        loadData();
    }
    Q_INVOKABLE void onCommandSetFilter(bool value)
    {
        setFilterMode(value);
        loadData();
    }
    Q_INVOKABLE void onCommandResetZoom()
    {
        loadData();
    }
    Q_INVOKABLE void onCommandSetRange(int x1, int y1, int x2, int y2)
    {
    }
    Q_INVOKABLE void onCommandSetCanvasSize(int width, int height)
    {
        int dataCnt = (mDataEndIdx - mDataStartIdx) + 1;
        int pointIdx = 0;
        int pointCnt = dataCnt > width ? width : dataCnt;

        mCanvasWidth = width;
        mCanvasHeight = height;

        mListMin.clear();
        mListMax.clear();

        if(mDataList.size() < 1)
            return;

        float pointGap = (float)pointCnt / (float)dataCnt;

        for(int i = mDataStartIdx; i < mDataEndIdx + 1; i ++)
        {
            pointIdx = ((float)(i - mDataStartIdx)) * pointGap;

            if(mListMin.size() > pointIdx)
            {
                if(mListMin[pointIdx] > mDataList[i])
                    mListMin[pointIdx] = mDataList[i];

                if(mListMax[pointIdx] < mDataList[i])
                    mListMax[pointIdx] = mDataList[i];
            }
            else
            {
                mListMin.append(mDataList[i]);
                mListMax.append(mDataList[i]);
            }
        }
    }
    Q_INVOKABLE int onCommandGetPointCnt()
    {
        return mListMin.size();
    }
    Q_INVOKABLE int onCommandGetLineOverY()
    {
        int temp = mOverWeight - mDataMinWeight;

        qDebug() << "over = " << mOverWeight << ", data min = " << mDataMinWeight << ", range = " << mDataWeightRange;

        if(mDataWeightRange == 0)
            return 0;

        return mCanvasHeight - (mCanvasHeight * ((float)temp / (float)mDataWeightRange));
    }
    Q_INVOKABLE int onCommandGetLineUnderY()
    {
        int temp = mUnderWeight - mDataMinWeight;

        qDebug() << "under = " << mUnderWeight << ", data min = " << mDataMinWeight << ", range = " << mDataWeightRange << ",mCanvasHeight = " << mCanvasHeight;

        if(mDataWeightRange == 0)
            return 0;

        return mCanvasHeight - (mCanvasHeight * ((float)temp / (float)mDataWeightRange));
    }
    Q_INVOKABLE int onCommandGetPointMinY(int idx)
    {
        int temp = mListMin[idx] - mDataMinWeight;

        if(mDataWeightRange == 0)
            return 0;

        return mCanvasHeight - (mCanvasHeight * ((float)temp / (float)mDataWeightRange));
    }
    Q_INVOKABLE int onCommandGetPointMaxY(int idx)
    {
        int temp = mListMax[idx] - mDataMinWeight;

        if(mDataWeightRange == 0)
            return 0;

        return mCanvasHeight - (mCanvasHeight * ((float)temp / (float)mDataWeightRange));
    }

    void onSignalEventChangedIsLoading(bool value)
    {
        if(value == false)
        {
            loadData();
        }
    }

    void onSignalEventChangedProductSeq()
    {
        loadData();
    }

public:
    void loadData()
    {
        WeightCheckerProduct * pWCProduct = nullptr;

        quint64 mPSeq = mpCoreService->mLSettingService.mWCProductSeq;

        pWCProduct = mpCoreService->mDataLoader.mWCModel.findProductBySeq(mPSeq);

        if(pWCProduct == nullptr)
        {
            qDebug() << "[debug] pWCProduct is null";
            clear();
            emit signalEventChangedData();
            return;
        }

        setIsNonData(false);

        if(mFilterMode == true)
        {
            mDataList = pWCProduct->mListTradeWeightValue;
        }
        else
        {
            mDataList = pWCProduct->mListTotalWeightValue;
        }

        mOverWeight = pWCProduct->mOverSettingValue;
        mUnderWeight = pWCProduct->mUnderSettingValue;

        if(mMinMaxMode)
        {
            int tempMin = pWCProduct->mUnderSettingValue < pWCProduct->mMinWeight ? pWCProduct->mUnderSettingValue : pWCProduct->mMinWeight;
            int tempMax = pWCProduct->mOverSettingValue  > pWCProduct->mMaxWeight ? pWCProduct->mOverSettingValue  : pWCProduct->mMaxWeight;
            int tempGap = tempMax - tempMin;

            mDataStartIdx  = 0;
            setDataEndIdx(mDataList.size() - 1);
            setDataTotalCnt(mDataList.size());
            setDataGap(mDataTotalCnt < 10  ? 1 : ((float)mDataTotalCnt / 10.0f) + 0.5);

            setYScope(pWCProduct->mMinWeight - (tempGap * 0.2), pWCProduct->mMaxWeight  + (tempGap * 0.2));
        }
        else
        {
            int tempGap = pWCProduct->mOverSettingValue - pWCProduct->mUnderSettingValue;

            mDataStartIdx  = 0;
            setDataEndIdx(mDataList.size() - 1);
            setDataTotalCnt(mDataList.size());
            setDataGap(mDataTotalCnt < 10 ? 1 : ((float)mDataTotalCnt / 10.0f) + 0.5);

            setYScope(pWCProduct->mUnderSettingValue - (tempGap * 0.2), pWCProduct->mOverSettingValue  + (tempGap * 0.2));
        }

        emit signalEventChangedData();
    }

    void setYScope(int min, int max)
    {
        setDataMinWeight(min);
        mDataMaxWeight = max;
        mDataWeightRange = mDataMaxWeight - mDataMinWeight;

        setWeightGab((mDataMaxWeight - mDataMinWeight) / 10);
    }

    void clear()
    {
        mDataStartIdx    = 0;
        setDataEndIdx(0);
        setDataMinWeight(0);
        setDataTotalCnt(0);
        setDataGap(0);
        mDataMaxWeight   = 0;
        mDataWeightRange = 0;
        setWeightGab(0);
        mOverWeight      = 0;
        mUnderWeight     = 0;

        mDataList.clear();
        mListMax.clear();
        mListMin.clear();

        setIsNonData(true);
    }

    explicit PanelWCTrendsModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        connect(&mpCoreService->mDataLoader     , SIGNAL(signalEventChangedIsLoading   (bool)), this, SLOT(onSignalEventChangedIsLoading (bool)));
        connect(&mpCoreService->mLSettingService, SIGNAL(signalEventChangedWCProductSeq(    )), this, SLOT(onSignalEventChangedProductSeq(    )));

        onSignalEventChangedIsLoading(mpCoreService->mDataLoader.mIsLoading);
    }
};
#endif // PANELWCTRENDSMODEL_H
