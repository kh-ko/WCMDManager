#ifndef PANELMETALDETECTHISTORYMODEL_H
#define PANELMETALDETECTHISTORYMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"
#include "source/service/util/svcconnectutil.h"

class PanelMetalDetectHistoryModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsLoading      READ getIsLoading      NOTIFY signalEventChangedIsLoading     );

private:
    bool    mIsLoading     ;

    bool    getIsLoading     (){ return mIsLoading     ; }

    void setIsLoading     (bool    value){ if(mIsLoading      == value) return; mIsLoading      = value; emit signalEventChangedIsLoading     (mIsLoading     );}

signals:
    void signalEventChangedIsLoading     (bool    value);

public slots:
    Q_INVOKABLE int getListSize()
    {
        if(mIsLoading)
            return 0;

        return pDLoaderSvc->mDailyHis.mEH.mMDFailList.size();
    }
    Q_INVOKABLE int getPNO(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mEH.mMDFailList.size() <= idx)
            return 0;

        PDSettingDto setting = pDLoaderSvc->mDailyHis.mEH.findSettingDto(pDLoaderSvc->mDailyHis.mEH.mMDFailList[idx].mPDSeq, pDLoaderSvc->mDailyHis.mEH.mMDFailList[idx].mPDHisIdx);

        return setting.mProductNum;
    }
    Q_INVOKABLE QString getPName(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mEH.mMDFailList.size() <= idx)
            return 0;

        PDSettingDto setting = pDLoaderSvc->mDailyHis.mEH.findSettingDto(pDLoaderSvc->mDailyHis.mEH.mMDFailList[idx].mPDSeq, pDLoaderSvc->mDailyHis.mEH.mMDFailList[idx].mPDHisIdx);

        return setting.mName;
    }
    Q_INVOKABLE QString getTime(int idx)
    {
        if(mIsLoading)
            return 0;

        if(pDLoaderSvc->mDailyHis.mEH.mMDFailList.size() <= idx)
            return 0;

        return pDLoaderSvc->mDailyHis.mEH.mMDFailList[idx].mDateTime.toString(TIME_FMT);
    }

public slots:
    void onChangedIsLoading(bool value)
    {
        setIsLoading(value);
    }

public:
    explicit PanelMetalDetectHistoryModel(QObject *parent = nullptr):QObject(parent)
    {
        ENABLE_SLOT_DLOAD_CHANGED_IS_LOADING;

        onChangedIsLoading(pDLoaderSvc->mIsLoading);
    }
};

#endif // PANELMETALDETECTHISTORYMODEL_H
