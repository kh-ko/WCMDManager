#ifndef PANELMETALSTATISTICSMODEL_H
#define PANELMETALSTATISTICSMODEL_H
#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"

class PanelMetalStatisticsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsLoading      READ getIsLoading      NOTIFY signalEventChangedIsLoading     );
    Q_PROPERTY(int     mMaxDay         READ getMaxDay         NOTIFY signalEventChangedMaxDay        );
    Q_PROPERTY(int     mYear           READ getYear           NOTIFY signalEventChangedYear          );
    Q_PROPERTY(int     mMonth          READ getMonth          NOTIFY signalEventChangedMonth         );
    Q_PROPERTY(int     mDay            READ getDay            NOTIFY signalEventChangedDay           );
    Q_PROPERTY(int     mSelProductNo   READ getSelProductNo   NOTIFY signalEventChangedSelProductNo  );
    Q_PROPERTY(QString mSelProductName READ getSelProductName NOTIFY signalEventChangedSelProductName);
    Q_PROPERTY(quint64 mTotalCnt       READ getTotalCnt       NOTIFY signalEventChangedTotalCnt      );
    Q_PROPERTY(quint64 mNGCnt          READ getNGCnt          NOTIFY signalEventChangedNGCnt         );

private:
    CoreService * mpCoreService;
    quint64 mSelProductSeq;

    bool    mIsLoading      ;
    int     mMaxDay         ;
    int     mYear           ;
    int     mMonth          ;
    int     mDay            ;
    int     mSelProductNo   ;
    QString mSelProductName ;
    quint64 mTotalCnt       ;
    quint64 mNGCnt          ;
    ProductStatisticsModel listStatistics[31];

    bool    getIsLoading     (){ return mIsLoading     ; }
    int     getMaxDay        (){ return mMaxDay        ; }
    int     getYear          (){ return mYear          ; }
    int     getMonth         (){ return mMonth         ; }
    int     getDay           (){ return mDay           ; }
    int     getSelProductNo  (){ return mSelProductNo  ; }
    QString getSelProductName(){ return mSelProductName; }
    quint64 getTotalCnt      (){ return mTotalCnt      ; }
    quint64 getNGCnt         (){ return mNGCnt         ; }

    void setIsLoading     (bool    value){ if(mIsLoading      == value) return; mIsLoading      = value; emit signalEventChangedIsLoading     (mIsLoading     );}
    void setMaxDay        (int     value){ if(mMaxDay         == value) return; mMaxDay         = value; emit signalEventChangedMaxDay        (mMaxDay        );}
    void setYear          (int     value){ if(mYear           == value) return; mYear           = value; emit signalEventChangedYear          (mYear          );}
    void setMonth         (int     value){ if(mMonth          == value) return; mMonth          = value; emit signalEventChangedMonth         (mMonth         );}
    void setDay           (int     value){ if(mDay            == value) return; mDay            = value; emit signalEventChangedDay           (mDay           );}
    void setSelProductNo  (int     value){ if(mSelProductNo   == value) return; mSelProductNo   = value; emit signalEventChangedSelProductNo  (mSelProductNo  );}
    void setSelProductName(QString value){ if(mSelProductName == value) return; mSelProductName = value; emit signalEventChangedSelProductName(mSelProductName);}
    void setTotalCnt      (quint64 value){ if(mTotalCnt       == value) return; mTotalCnt       = value; emit signalEventChangedTotalCnt      (mTotalCnt      );}
    void setNGCnt         (quint64 value){ if(mNGCnt          == value) return; mNGCnt          = value; emit signalEventChangedNGCnt         (mNGCnt         );}

signals:
    void signalEventChangedIsLoading     (bool    value);
    void signalEventChangedMaxDay        (int     value);
    void signalEventChangedYear          (int     value);
    void signalEventChangedMonth         (int     value);
    void signalEventChangedDay           (int     value);
    void signalEventChangedSelProductNo  (int     value);
    void signalEventChangedSelProductName(QString value);
    void signalEventChangedTotalCnt      (quint64 value);
    void signalEventChangedNGCnt         (quint64 value);

    void signalEventCompletedUpdate      ();

public slots:
    Q_INVOKABLE int onCommandGetProductListSize()
    {
        return mpCoreService->mDataLoader.mProductStatistics.mListMonthStatistics.size();
    }
    Q_INVOKABLE quint64 onCommandGetProductSeqInProductList(int idx)
    {
        if(idx < 0 || idx >= mpCoreService->mDataLoader.mProductStatistics.mListMonthStatistics.size())
            return 0;

        return mpCoreService->mDataLoader.mProductStatistics.mListMonthStatistics.at(idx)->mProductSeq;
    }
    Q_INVOKABLE int onCommandGetProductNoInProductList(int idx)
    {
        if(idx < 0 || idx >= mpCoreService->mDataLoader.mProductStatistics.mListMonthStatistics.size())
            return 0;

        return mpCoreService->mDataLoader.mProductStatistics.mListMonthStatistics.at(idx)->mProductNo;
    }
    Q_INVOKABLE QString onCommandGetProductNameInProductList(int idx)
    {
        if(idx < 0 || idx >= mpCoreService->mDataLoader.mProductStatistics.mListMonthStatistics.size())
            return 0;

        return mpCoreService->mDataLoader.mProductStatistics.mListMonthStatistics.at(idx)->mProductName;
    }

    Q_INVOKABLE void onCommandSelProduct(quint64 seq)
    {
        if(mIsLoading)
            return;

        ProductStatisticsModel * pModel = mpCoreService->mDataLoader.mProductStatistics.findMonthStatistcs(seq);

        if(pModel == nullptr)
            return;

        mSelProductSeq = seq;

        UpdateDailyStatistics();

        setSelProductNo(pModel->mProductNo);
        setSelProductName(pModel->mProductName);
        setTotalCnt(pModel->mTotalCnt);
        setNGCnt(pModel->mMDDetectCnt);
    }

    Q_INVOKABLE qint64 onCommandGetTotalCnt(int day)
    {
        if(mIsLoading)
            return 0;

        if(day < 1 || day > 31)
            return 0;

        return listStatistics[day - 1].mTotalCnt;
    }

    Q_INVOKABLE qint64 onCommandGetDetectCnt(int day)
    {
        if(mIsLoading)
            return 0;

        if(day < 1 || day > 31)
            return 0;

        return listStatistics[day - 1].mMDDetectCnt;
    }

public slots:
    void onSignalEventChangedIsLoading(bool value)
    {
        setIsLoading(value);

        if(value == true)
            return;

         if(mpCoreService->mDataLoader.mProductStatistics.mListMonthStatistics.size() < 1)
         {
             reset();
             emit signalEventCompletedUpdate();
             return;
         }

         onCommandSelProduct(mpCoreService->mDataLoader.mProductStatistics.mListMonthStatistics[0]->mProductSeq);
    }

    void onSignalEventChangedSelectDate()
    {
        setYear(mpCoreService->mLSettingService.mSelectedYear);
        setMonth(mpCoreService->mLSettingService.mSelectedMonth);
        setDay(mpCoreService->mLSettingService.mSelectedDay);

        int maxDay = 1;

        if(mMonth == 2)
        {
            if((mYear % 4) == 0 && ((mYear % 100) != 0 || (mYear % 400) == 0))
            {
                maxDay = 29;
            }
            else
            {
                maxDay = 28;
            }
        }
        else if(mMonth == 4 || mMonth == 6 || mMonth == 9 || mMonth == 11)
        {
            maxDay = 30;
        }
        else
        {
            maxDay = 31;
        }

        setMaxDay(maxDay);
    }
public:
    ProductStatisticsModel *findStatisticsBySeq(QList<ProductStatisticsModel *> * pList, quint64 seq)
    {
        for(int i = 0; i < pList->size(); i ++)
        {
            ProductStatisticsModel * pModel = pList->at(i);

            if(pModel->mProductSeq == seq)
                return pModel;
        }
        return nullptr;
    }

    void UpdateDailyStatistics()
    {
        reset();

        for(int i = 0; i < 31; i ++)
        {
            QList<ProductStatisticsModel *> * pList = &mpCoreService->mDataLoader.mProductStatistics.mListDailyStatistics[i];

            ProductStatisticsModel * pModel = findStatisticsBySeq(pList, mSelProductSeq);

            if(pModel == nullptr)
                continue;

            listStatistics[i].setValue(pModel);
        }

        emit signalEventCompletedUpdate();
    }

    void reset()
    {
        setSelProductNo  (0);
        setSelProductName("");
        setTotalCnt      (0);
        setNGCnt         (0);

        for(int i = 0; i < 31; i ++)
        {
            listStatistics[i].reset();
        }
    }

    explicit PanelMetalStatisticsModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        connect(&mpCoreService->mDataLoader     , SIGNAL(signalEventChangedIsLoading (bool)), this, SLOT(onSignalEventChangedIsLoading (bool)));
        connect(&mpCoreService->mLSettingService, SIGNAL(signalEventChangedSelectDate(    )), this, SLOT(onSignalEventChangedSelectDate(    )));
        reset();

        onSignalEventChangedSelectDate();
        onSignalEventChangedIsLoading(mpCoreService->mDataLoader.mIsLoading);
    }
};
#endif // PANELMETALSTATISTICSMODEL_H
