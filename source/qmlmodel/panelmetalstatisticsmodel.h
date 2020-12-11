#ifndef PANELMETALSTATISTICSMODEL_H
#define PANELMETALSTATISTICSMODEL_H
#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"
#include "source/service/util/svcconnectutil.h"

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
        return pDLoaderSvc->mMonthlyStatsHis.mPDList.size();//mpCoreService->mDataLoader.mProductStatistics.mListMonthStatistics.size();
    }
    Q_INVOKABLE quint64 onCommandGetProductSeqInProductList(int idx)
    {
        if(idx < 0 || idx >= pDLoaderSvc->mMonthlyStatsHis.mPDList.size())
            return 0;

        return pDLoaderSvc->mMonthlyStatsHis.mPDList[idx].mSeq;
    }
    Q_INVOKABLE int onCommandGetProductNoInProductList(int idx)
    {
        if(idx < 0 || idx >= pDLoaderSvc->mMonthlyStatsHis.mPDList.size())
            return 0;

        return pDLoaderSvc->mMonthlyStatsHis.mPDList[idx].mNum;
    }
    Q_INVOKABLE QString onCommandGetProductNameInProductList(int idx)
    {
        if(idx < 0 || idx >= pDLoaderSvc->mMonthlyStatsHis.mPDList.size())
            return 0;

        return pDLoaderSvc->mMonthlyStatsHis.mPDList[idx].mName;
    }

    Q_INVOKABLE void onCommandSelProduct(quint64 seq)
    {
        if(mIsLoading)
            return;

        PDStatsDto stats = pDLoaderSvc->mMonthlyStatsHis.findStatsDto(seq);

        mSelProductSeq = seq;

        emit signalEventCompletedUpdate();

        setSelProductNo  (stats.mNum);
        setSelProductName(stats.mName);
        setTotalCnt      (stats.mMDTotalCnt);
        setNGCnt         (stats.mMDFailCnt);
    }

    Q_INVOKABLE qint64 onCommandGetTotalCnt(int day)
    {
        if(mIsLoading)
            return 0;

        if(day < 1 || day > 31)
            return 0;

        PDStatsDto stats = (pDLoaderSvc->mMonthlyStatsHis.mDayList[day - 1].findStatsDto(mSelProductSeq));

        return stats.mMDTotalCnt;
    }

    Q_INVOKABLE qint64 onCommandGetDetectCnt(int day)
    {
        if(mIsLoading)
            return 0;

        if(day < 1 || day > 31)
            return 0;

        PDStatsDto stats = (pDLoaderSvc->mMonthlyStatsHis.mDayList[day - 1].findStatsDto(mSelProductSeq));

        return stats.mMDFailCnt;
    }

public slots:
    void onChangedIsLoading(bool value)
    {
        setIsLoading(value);

        if(value == true)
            return;

        if(pDLoaderSvc->mMonthlyStatsHis.mPDList.size() < 1)
        {
            onCommandSelProduct(0);
        }
        else
        {
            onCommandSelProduct(pDLoaderSvc->mMonthlyStatsHis.mPDList[0].mSeq);
        }
    }

    void onChangedSelectDate()
    {
        setYear (pLSettingSvc->mSelectedDate.year());
        setMonth(pLSettingSvc->mSelectedDate.month());
        setDay  (pLSettingSvc->mSelectedDate.day());

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
    explicit PanelMetalStatisticsModel(QObject *parent = nullptr):QObject(parent)
    {
        ENABLE_SLOT_LSETTING_CHANGED_SEL_DATE;
        ENABLE_SLOT_DLOAD_CHANGED_IS_LOADING;

        onChangedSelectDate();
        onChangedIsLoading(pDLoaderSvc->mIsLoading);
    }
};
#endif // PANELMETALSTATISTICSMODEL_H
