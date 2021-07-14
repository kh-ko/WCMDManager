#ifndef PANELMETALOPERATEHISTORYMODEL_H
#define PANELMETALOPERATEHISTORYMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"
#include "source/service/devinfoservice.h"
#include "source/service/util/svcconnectutil.h"

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

        return pDLoaderSvc->mDailyHis.mPS.mPSList.size();
    }
    Q_INVOKABLE int getPNO(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mPS.mPSList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mPS.mPSList[idx].mNum;
    }
    Q_INVOKABLE QString getPName(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mPS.mPSList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mPS.mPSList[idx].mName;
    }
    Q_INVOKABLE QString getLimCriteriaFe(int idx)
    {
        return mDevInfo.getLimFe(pDLoaderSvc->mDailyHis.mPS.mPSList[idx].mSeq);
        //return pLSettingSvc->mMDSettingModel.mLimitCriteriaFe;
    }
    Q_INVOKABLE QString getLimCriteriaSus(int idx)
    {
        return mDevInfo.getLimSus(pDLoaderSvc->mDailyHis.mPS.mPSList[idx].mSeq);
        //return pLSettingSvc->mMDSettingModel.mLimitCriteriaSus;
    }

    Q_INVOKABLE qint64 getTotalCnt(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mPS.mPSList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mPS.mPSList[idx].mMDTotalCnt;
    }
    Q_INVOKABLE qint64 getNGCnt(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mPS.mPSList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mPS.mPSList[idx].mMDFailCnt;
    }
public slots:
    void onChangedIsLoading(bool value)
    {
        setIsLoading(value);

        mDevInfo = pDevInfoSvc->findDevInfo(pDLoaderSvc->mDevNum);
    }
public:
    DevInfoDto mDevInfo;

    explicit PanelMetalOperateHistoryModel(QObject *parent = nullptr):QObject(parent)
    {
        ENABLE_SLOT_DLOAD_CHANGED_IS_LOADING;

        onChangedIsLoading(pDLoaderSvc->mIsLoading);
    }
};
#endif // PANELMETALOPERATEHISTORYMODEL_H
