#ifndef PANELMETALCHECKUPHISTORYMODEL_H
#define PANELMETALCHECKUPHISTORYMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"

class PanelMetalCheckupHistoryModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsLoading      READ getIsLoading      NOTIFY signalEventChangedIsLoading     );
    Q_PROPERTY(QString mMDCheckupCycle READ getMDCheckupCycle NOTIFY signalEventChangedMDCheckupCycle);

private:
    CoreService * mpCoreService;

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

        return mpCoreService->mDataLoader.mListMDCheckupHis.size();
    }
    Q_INVOKABLE int getPNO(int idx)
    {
        if(mIsLoading)
            return 0;

        if(mpCoreService->mDataLoader.mListMDCheckupHis.size() <= idx)
            return 0;

        return mpCoreService->mDataLoader.mListMDCheckupHis[idx]->mProductNo;
    }
    Q_INVOKABLE QString getPName(int idx)
    {
        if(mIsLoading)
            return 0;

        if(mpCoreService->mDataLoader.mListMDCheckupHis.size() <= idx)
            return 0;

        return mpCoreService->mDataLoader.mListMDCheckupHis[idx]->mProductName;
    }
    Q_INVOKABLE QString getTime(int idx)
    {
        if(mIsLoading)
            return 0;

        if(mpCoreService->mDataLoader.mListMDCheckupHis.size() <= idx)
            return 0;

        return mpCoreService->mDataLoader.mListMDCheckupHis[idx]->mTime;
    }
    Q_INVOKABLE QString getLimCriteriaFe()
    {
        return mpCoreService->mLSettingService.mMDSettingModel.mLimitCriteriaFe;
    }
    Q_INVOKABLE QString getLimCriteriaSus()
    {
        return mpCoreService->mLSettingService.mMDSettingModel.mLimitCriteriaSus;
    }
    Q_INVOKABLE bool getJudgFe01(int idx)
    {
        if(mIsLoading)
            return 0;

        if(mpCoreService->mDataLoader.mListMDCheckupHis.size() <= idx)
            return 0;

        return mpCoreService->mDataLoader.mListMDCheckupHis[idx]->mIsPassFe01;
    }
    Q_INVOKABLE bool getJudgFe02(int idx)
    {
        if(mIsLoading)
            return 0;

        if(mpCoreService->mDataLoader.mListMDCheckupHis.size() <= idx)
            return 0;

        return mpCoreService->mDataLoader.mListMDCheckupHis[idx]->mIsPassFe02;
    }
    Q_INVOKABLE bool getJudgFe03(int idx)
    {
        if(mIsLoading)
            return 0;

        if(mpCoreService->mDataLoader.mListMDCheckupHis.size() <= idx)
            return 0;

        return mpCoreService->mDataLoader.mListMDCheckupHis[idx]->mIsPassFe03;
    }
    Q_INVOKABLE bool getJudgSus01(int idx)
    {
        if(mIsLoading)
            return 0;

        if(mpCoreService->mDataLoader.mListMDCheckupHis.size() <= idx)
            return 0;

        return mpCoreService->mDataLoader.mListMDCheckupHis[idx]->mIsPassSus01;
    }
    Q_INVOKABLE bool getJudgSus02(int idx)
    {
        if(mIsLoading)
            return 0;

        if(mpCoreService->mDataLoader.mListMDCheckupHis.size() <= idx)
            return 0;

        return mpCoreService->mDataLoader.mListMDCheckupHis[idx]->mIsPassSus02;
    }
    Q_INVOKABLE bool getJudgSus03(int idx)
    {
        if(mIsLoading)
            return 0;

        if(mpCoreService->mDataLoader.mListMDCheckupHis.size() <= idx)
            return 0;

        return mpCoreService->mDataLoader.mListMDCheckupHis[idx]->mIsPassSus03;
    }
public slots:
    void onSignalEventChangedIsLoading(bool value)
    {
        setIsLoading(value);
    }
    void onSignalEventChangedMetalDetectorSetting()
    {
        setMDCheckupCycle(mpCoreService->mLSettingService.mMDSettingModel.mCheckupCycle    );
    }

public:
    explicit PanelMetalCheckupHistoryModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        connect(&mpCoreService->mDataLoader     , SIGNAL(signalEventChangedIsLoading           (bool)), this, SLOT(onSignalEventChangedIsLoading           (bool)));
        connect(&mpCoreService->mLSettingService, SIGNAL(signalEventChangedMetalDetectorSetting(    )), this, SLOT(onSignalEventChangedMetalDetectorSetting(    )));

        onSignalEventChangedIsLoading(mpCoreService->mDataLoader.mIsLoading);
        onSignalEventChangedMetalDetectorSetting();
    }
};

#endif // PANELMETALCHECKUPHISTORYMODEL_H
