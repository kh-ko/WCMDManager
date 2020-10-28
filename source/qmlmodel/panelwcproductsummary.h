#ifndef PANELWCPRODUCTSUMMARY_H
#define PANELWCPRODUCTSUMMARY_H
#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"

class PanelWCProductSummaryModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int    mTotalCnt           READ getTotalCnt             NOTIFY signalEventChangedTotalCnt          )
    Q_PROPERTY(qint64 mTotalWeight        READ getTotalWeight          NOTIFY signalEventChangedTotalWeight       )
    Q_PROPERTY(int    mTotalAvgWeight     READ getTotalAvgWeight       NOTIFY signalEventChangedTotalAvgWeight    )
    Q_PROPERTY(int    mTotalSD            READ getTotalSD              NOTIFY signalEventChangedTotalSD           )
    Q_PROPERTY(double mTotalCV            READ getTotalCV              NOTIFY signalEventChangedTotalCV           )
    Q_PROPERTY(int    mTradeSettingValue  READ getTradeSettingValue    NOTIFY signalEventChangedTradeSettingValue )
    Q_PROPERTY(int    mTradeCnt           READ getTradeCnt             NOTIFY signalEventChangedTradeCnt          )
    Q_PROPERTY(qint64 mTradeWeight        READ getTradeWeight          NOTIFY signalEventChangedTradeWeight       )
    Q_PROPERTY(int    mTradeAvgWeight     READ getTradeAvgWeight       NOTIFY signalEventChangedTradeAvgWeight    )
    Q_PROPERTY(int    mTradeSD            READ getTradeSD              NOTIFY signalEventChangedTradeSD           )
    Q_PROPERTY(double mTradeCV            READ getTradeCV              NOTIFY signalEventChangedTradeCV           )
    Q_PROPERTY(int    mOverSettingValue   READ getOverSettingValue     NOTIFY signalEventChangedOverSettingValue  )
    Q_PROPERTY(int    mOverCnt            READ getOverCnt              NOTIFY signalEventChangedOverCnt           )
    Q_PROPERTY(int    mUnderSettingValue  READ getUnderSettingValue    NOTIFY signalEventChangedUnderSettingValue )
    Q_PROPERTY(int    mUnderCnt           READ getUnderCnt             NOTIFY signalEventChangedUnderCnt          )
    Q_PROPERTY(int    mEtcCnt             READ getEtcCnt               NOTIFY signalEventChangedEtcCnt            )
    Q_PROPERTY(int    mTareWeight         READ getTareWeight           NOTIFY signalEventChangedTareWeight        )
    Q_PROPERTY(int    mMinWeight          READ getMinWeight            NOTIFY signalEventChangedMinWeight         )
    Q_PROPERTY(int    mMaxWeight          READ getMaxWeight            NOTIFY signalEventChangedMaxWeight         )

private:
    CoreService * mpCoreService;
    quint64 mSelProductSeq;

    int    mTotalCnt          = 0;
    qint64 mTotalWeight       = 0;
    int    mTotalAvgWeight    = 0;
    int    mTotalSD           = 0;
    double mTotalCV           = 0.0f;
    int    mTradeSettingValue = 0;
    int    mTradeCnt          = 0;
    qint64 mTradeWeight       = 0;
    int    mTradeAvgWeight    = 0;
    int    mTradeSD           = 0;
    double mTradeCV           = 0.0f;
    int    mOverSettingValue  = 0;
    int    mOverCnt           = 0;
    int    mUnderSettingValue = 0;
    int    mUnderCnt          = 0;
    int    mEtcCnt            = 0;
    int    mTareWeight        = 0;
    int    mMinWeight         = 0;
    int    mMaxWeight         = 0;

    int    getTotalCnt         (){ return mTotalCnt         ; }
    qint64 getTotalWeight      (){ return mTotalWeight      ; }
    int    getTotalAvgWeight   (){ return mTotalAvgWeight   ; }
    int    getTotalSD          (){ return mTotalSD          ; }
    double getTotalCV          (){ return mTotalCV          ; }
    int    getTradeSettingValue(){ return mTradeSettingValue; }
    int    getTradeCnt         (){ return mTradeCnt         ; }
    qint64 getTradeWeight      (){ return mTradeWeight      ; }
    int    getTradeAvgWeight   (){ return mTradeAvgWeight   ; }
    int    getTradeSD          (){ return mTradeSD          ; }
    double getTradeCV          (){ return mTradeCV          ; }
    int    getOverSettingValue (){ return mOverSettingValue ; }
    int    getOverCnt          (){ return mOverCnt          ; }
    int    getUnderSettingValue(){ return mUnderSettingValue; }
    int    getUnderCnt         (){ return mUnderCnt         ; }
    int    getEtcCnt           (){ return mEtcCnt           ; }
    int    getTareWeight       (){ return mTareWeight       ; }
    int    getMinWeight        (){ return mMinWeight        ; }
    int    getMaxWeight        (){ return mMaxWeight        ; }

    void setTotalCnt         (int    value){ if(mTotalCnt          == value) return; mTotalCnt          = value; emit signalEventChangedTotalCnt         (mTotalCnt         ); }
    void setTotalWeight      (qint64 value){ if(mTotalWeight       == value) return; mTotalWeight       = value; emit signalEventChangedTotalWeight      (mTotalWeight      ); }
    void setTotalAvgWeight   (int    value){ if(mTotalAvgWeight    == value) return; mTotalAvgWeight    = value; emit signalEventChangedTotalAvgWeight   (mTotalAvgWeight   ); }
    void setTotalSD          (int    value){ if(mTotalSD           == value) return; mTotalSD           = value; emit signalEventChangedTotalSD          (mTotalSD          ); }
    void setTotalCV          (double value){ if(mTotalCV           == value) return; mTotalCV           = value; emit signalEventChangedTotalCV          (mTotalCV          ); }
    void setTradeSettingValue(int    value){ if(mTradeSettingValue == value) return; mTradeSettingValue = value; emit signalEventChangedTradeSettingValue(mTradeSettingValue); }
    void setTradeCnt         (int    value){ if(mTradeCnt          == value) return; mTradeCnt          = value; emit signalEventChangedTradeCnt         (mTradeCnt         ); }
    void setTradeWeight      (qint64 value){ if(mTradeWeight       == value) return; mTradeWeight       = value; emit signalEventChangedTradeWeight      (mTradeWeight      ); }
    void setTradeAvgWeight   (int    value){ if(mTradeAvgWeight    == value) return; mTradeAvgWeight    = value; emit signalEventChangedTradeAvgWeight   (mTradeAvgWeight   ); }
    void setTradeSD          (int    value){ if(mTradeSD           == value) return; mTradeSD           = value; emit signalEventChangedTradeSD          (mTradeSD          ); }
    void setTradeCV          (double value){ if(mTradeCV           == value) return; mTradeCV           = value; emit signalEventChangedTradeCV          (mTradeCV          ); }
    void setOverSettingValue (int    value){ if(mOverSettingValue  == value) return; mOverSettingValue  = value; emit signalEventChangedOverSettingValue (mOverSettingValue ); }
    void setOverCnt          (int    value){ if(mOverCnt           == value) return; mOverCnt           = value; emit signalEventChangedOverCnt          (mOverCnt          ); }
    void setUnderSettingValue(int    value){ if(mUnderSettingValue == value) return; mUnderSettingValue = value; emit signalEventChangedUnderSettingValue(mUnderSettingValue); }
    void setUnderCnt         (int    value){ if(mUnderCnt          == value) return; mUnderCnt          = value; emit signalEventChangedUnderCnt         (mUnderCnt         ); }
    void setEtcCnt           (int    value){ if(mEtcCnt            == value) return; mEtcCnt            = value; emit signalEventChangedEtcCnt           (mEtcCnt           ); }
    void setTareWeight       (int    value){ if(mTareWeight        == value) return; mTareWeight        = value; emit signalEventChangedTareWeight       (mTareWeight       ); }
    void setMinWeight        (int    value){ if(mMinWeight         == value) return; mMinWeight         = value; emit signalEventChangedMinWeight        (mMinWeight        ); }
    void setMaxWeight        (int    value){ if(mMaxWeight         == value) return; mMaxWeight         = value; emit signalEventChangedMaxWeight        (mMaxWeight        ); }

signals:
    void signalEventChangedTotalCnt         (int    value);
    void signalEventChangedTotalWeight      (qint64 value);
    void signalEventChangedTotalAvgWeight   (int    value);
    void signalEventChangedTotalSD          (int    value);
    void signalEventChangedTotalCV          (double value);
    void signalEventChangedTradeSettingValue(int    value);
    void signalEventChangedTradeCnt         (int    value);
    void signalEventChangedTradeWeight      (qint64 value);
    void signalEventChangedTradeAvgWeight   (int    value);
    void signalEventChangedTradeSD          (int    value);
    void signalEventChangedTradeCV          (double value);
    void signalEventChangedOverSettingValue (int    value);
    void signalEventChangedOverCnt          (int    value);
    void signalEventChangedUnderSettingValue(int    value);
    void signalEventChangedUnderCnt         (int    value);
    void signalEventChangedEtcCnt           (int    value);
    void signalEventChangedTareWeight       (int    value);
    void signalEventChangedMinWeight        (int    value);
    void signalEventChangedMaxWeight        (int    value);

public slots:
    void onSignalEventChangedIsLoading(bool value)
    {
        if(value)
            return;

        loadData();
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
            setTotalCnt         (0);  setTradeAvgWeight   (0);
            setTotalWeight      (0);  setTradeSD          (0);
            setTotalAvgWeight   (0);  setTradeCV          (0);
            setTotalSD          (0);  setOverSettingValue (0);
            setTotalCV          (0);  setOverCnt          (0);
            setTradeSettingValue(0);  setUnderSettingValue(0);
            setTradeCnt         (0);  setUnderCnt         (0);
            setTradeWeight      (0);  setEtcCnt           (0);
            setMinWeight        (0);  setMaxWeight        (0);
            setTareWeight       (0);
            return;
        }

        setTotalCnt         (pWCProduct->mTotalCnt            );
        setTotalWeight      (pWCProduct->mTotalWeight         );
        setTotalAvgWeight   (pWCProduct->mTotalAvgWeight + 0.5);
        setTotalSD          (pWCProduct->mTotalSD + 0.5       );
        setTotalCV          (pWCProduct->mTotalCV             );
        setTradeSettingValue(pWCProduct->mNormalSettingValue  );
        setTradeCnt         (pWCProduct->mTradeCnt            );
        setTradeWeight      (pWCProduct->mTradeWeight         );
        setTradeAvgWeight   (pWCProduct->mTradeAvgWeight + 0.5);
        setTradeSD          (pWCProduct->mTradeSD + 0.5       );
        setTradeCV          (pWCProduct->mTradeCV             );
        setOverSettingValue (pWCProduct->mOverSettingValue    );
        setOverCnt          (pWCProduct->mOverCnt             );
        setUnderSettingValue(pWCProduct->mUnderSettingValue   );
        setUnderCnt         (pWCProduct->mUnderCnt            );
        setEtcCnt           (pWCProduct->mEtcCnt              );
        setMinWeight        (pWCProduct->mMinWeight           );
        setMaxWeight        (pWCProduct->mMaxWeight           );
        setTareWeight       (pWCProduct->mTareSettingValue    );
    }

    explicit PanelWCProductSummaryModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        connect(&mpCoreService->mDataLoader     , SIGNAL(signalEventChangedIsLoading   (bool)), this, SLOT(onSignalEventChangedIsLoading (bool)));
        connect(&mpCoreService->mLSettingService, SIGNAL(signalEventChangedWCProductSeq(    )), this, SLOT(onSignalEventChangedProductSeq(    )));

        onSignalEventChangedIsLoading(mpCoreService->mDataLoader.mIsLoading);
    }
};

#endif // PANELWCPRODUCTSUMMARY_H
