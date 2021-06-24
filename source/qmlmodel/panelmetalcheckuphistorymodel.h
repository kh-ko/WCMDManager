#ifndef PANELMETALCHECKUPHISTORYMODEL_H
#define PANELMETALCHECKUPHISTORYMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"
#include "source/service/devinfoservice.h"
#include "source/service/util/svcconnectutil.h"

class PanelMetalCheckupHistoryModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsLoading      READ getIsLoading      NOTIFY signalEventChangedIsLoading     );
    Q_PROPERTY(QString mMDCheckupCycle READ getMDCheckupCycle NOTIFY signalEventChangedMDCheckupCycle);

private:
    bool    mIsLoading     ;
    QString mMDCheckupCycle;

    bool    getIsLoading     (){ return mIsLoading     ; }
    QString getMDCheckupCycle(){ return mMDCheckupCycle; }

    void setIsLoading     (bool    value){ if(mIsLoading      == value) return; mIsLoading      = value; emit signalEventChangedIsLoading     (mIsLoading     );}
    void setMDCheckupCycle(QString value){ if(mMDCheckupCycle == value) return; mMDCheckupCycle = value; emit signalEventChangedMDCheckupCycle(mMDCheckupCycle);}

signals:
    void signalEventChangedIsLoading     (bool    value);
    void signalEventChangedMDCheckupCycle(QString value);

public slots:
    Q_INVOKABLE int getListSize()
    {
        if(mIsLoading)
            return 0;

        return pDLoaderSvc->mDailyHis.mEH.mCheckupEventList.size();
    }
    Q_INVOKABLE int getPNO(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mEH.mCheckupEventList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mEH.mCheckupEventList[idx].mProductNo;
    }
    Q_INVOKABLE QString getPName(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mEH.mCheckupEventList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mEH.mCheckupEventList[idx].mProductName;
    }
    Q_INVOKABLE QString getTime(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mEH.mCheckupEventList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mEH.mCheckupEventList[idx].mTime.toString(TIME_FMT);
    }
    Q_INVOKABLE QString getLimCriteriaFe(int idx)
    {
        return mDevInfo.getLimFe(pDLoaderSvc->mDailyHis.mEH.mCheckupEventList[idx].mProductSeq);
        //return pLSettingSvc->mMDSettingModel.mLimitCriteriaFe;
    }
    Q_INVOKABLE QString getLimCriteriaSus(int idx)
    {
        return mDevInfo.getLimSus(pDLoaderSvc->mDailyHis.mEH.mCheckupEventList[idx].mProductSeq);
        //return pLSettingSvc->mMDSettingModel.mLimitCriteriaSus;
    }
    Q_INVOKABLE bool getJudgFe01(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mEH.mCheckupEventList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mEH.mCheckupEventList[idx].mIsPassFe01;
    }
    Q_INVOKABLE bool getJudgFe02(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mEH.mCheckupEventList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mEH.mCheckupEventList[idx].mIsPassFe02;
    }
    Q_INVOKABLE bool getJudgFe03(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mEH.mCheckupEventList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mEH.mCheckupEventList[idx].mIsPassFe03;
    }
    Q_INVOKABLE bool getJudgSus01(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mEH.mCheckupEventList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mEH.mCheckupEventList[idx].mIsPassSus01;
    }
    Q_INVOKABLE bool getJudgSus02(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mEH.mCheckupEventList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mEH.mCheckupEventList[idx].mIsPassSus02;
    }
    Q_INVOKABLE bool getJudgSus03(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mEH.mCheckupEventList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mEH.mCheckupEventList[idx].mIsPassSus03;
    }
public slots:
    void onChangedIsLoading(bool value)
    {
        setIsLoading(value);

        mDevInfo = pDevInfoSvc->findDevInfo(pDLoaderSvc->mDevNum);
    }

    void onChangedLimitCriteria(int dNum, QString strLimitCriteria)
    {
        mDevInfo = pDevInfoSvc->findDevInfo(pDLoaderSvc->mDevNum);

        emit signalEventChangedIsLoading(false);
    }

    void onChangedMetalDetectorSetting()
    {
        setMDCheckupCycle(pLSettingSvc->mMDSettingModel.mCheckupCycle    );
    }

public:
    DevInfoDto mDevInfo;

    explicit PanelMetalCheckupHistoryModel(QObject *parent = nullptr):QObject(parent)
    {
        ENABLE_SLOT_DLOAD_CHANGED_IS_LOADING;
        ENABLE_SLOT_LSETTING_CHANGED_MD_SETTING;
        ENABLE_SLOT_DINFO_CHANGED_LIMIT_CRITERIA;

        onChangedIsLoading(pDLoaderSvc->mIsLoading);
        onChangedMetalDetectorSetting();
    }
};

#endif // PANELMETALCHECKUPHISTORYMODEL_H
