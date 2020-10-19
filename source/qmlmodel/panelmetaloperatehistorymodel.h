#ifndef PANELMETALOPERATEHISTORYMODEL_H
#define PANELMETALOPERATEHISTORYMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"

class PanelMetalOperateHistoryModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsLoading      READ getIsLoading      NOTIFY signalEventChangedIsLoading     );

private:
    CoreService * mpCoreService;
    bool mIsLoading     ;

    bool getIsLoading(){ return mIsLoading; }
    void setIsLoading(bool value){ if(mIsLoading == value) return; mIsLoading = value; emit signalEventChangedIsLoading(mIsLoading);}

signals:
    void signalEventChangedIsLoading     (bool    value);

public slots:
    Q_INVOKABLE int getListSize()
    {
        if(mIsLoading)
            return 0;

        QList<ProductStatisticsModel *> * pList = mpCoreService->mDataLoader.mProductStatistics.getStatistics(mpCoreService->mDataLoader.mDay);

        if(pList == nullptr)
            return 0;

        return pList->size();
    }
    Q_INVOKABLE int getPNO(int idx)
    {
        if(mIsLoading)
            return 0;

        QList<ProductStatisticsModel *> * pList = mpCoreService->mDataLoader.mProductStatistics.getStatistics(mpCoreService->mDataLoader.mDay);

        if(pList == nullptr)
            return 0;

        if(pList->size() <= idx)
            return 0;

        return pList->at(idx)->mProductNo;
    }
    Q_INVOKABLE QString getPName(int idx)
    {
        if(mIsLoading)
            return 0;

        QList<ProductStatisticsModel *> * pList = mpCoreService->mDataLoader.mProductStatistics.getStatistics(mpCoreService->mDataLoader.mDay);

        if(pList == nullptr)
            return 0;

        if(pList->size() <= idx)
            return 0;

        return pList->at(idx)->mProductName;
    }
    Q_INVOKABLE QString getLimCriteriaFe()
    {
        return mpCoreService->mLSettingService.mMDSettingModel.mLimitCriteriaFe;
    }
    Q_INVOKABLE QString getLimCriteriaSus()
    {
        return mpCoreService->mLSettingService.mMDSettingModel.mLimitCriteriaSus;
    }
    Q_INVOKABLE qint64 getTotalCnt(int idx)
    {
        if(mIsLoading)
            return 0;

        QList<ProductStatisticsModel *> * pList = mpCoreService->mDataLoader.mProductStatistics.getStatistics(mpCoreService->mDataLoader.mDay);

        if(pList == nullptr)
            return 0;

        if(pList->size() <= idx)
            return 0;

        return pList->at(idx)->mTotalCnt;
    }
    Q_INVOKABLE qint64 getNGCnt(int idx)
    {
        if(mIsLoading)
            return 0;

        QList<ProductStatisticsModel *> * pList = mpCoreService->mDataLoader.mProductStatistics.getStatistics(mpCoreService->mDataLoader.mDay);

        if(pList == nullptr)
            return 0;

        if(pList->size() <= idx)
            return 0;

        return pList->at(idx)->mMDDetectCnt;
    }
public slots:
    void onSignalEventChangedIsLoading(bool value)
    {
        setIsLoading(value);
    }
public:
    explicit PanelMetalOperateHistoryModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        connect(&mpCoreService->mDataLoader     , SIGNAL(signalEventChangedIsLoading           (bool)), this, SLOT(onSignalEventChangedIsLoading           (bool)));

        onSignalEventChangedIsLoading(mpCoreService->mDataLoader.mIsLoading);
    }
};
#endif // PANELMETALOPERATEHISTORYMODEL_H
