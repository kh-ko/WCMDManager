#ifndef PANELMETALDETECTHISTORYMODEL_H
#define PANELMETALDETECTHISTORYMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"

class PanelMetalDetectHistoryModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsLoading      READ getIsLoading      NOTIFY signalEventChangedIsLoading     );

private:
    CoreService * mpCoreService;

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

        return mpCoreService->mDataLoader.mListMDDetectHis.size();
    }
    Q_INVOKABLE int getPNO(int idx)
    {
        if(mIsLoading)
            return 0;

        if(mpCoreService->mDataLoader.mListMDDetectHis.size() <= idx)
            return 0;

        return mpCoreService->mDataLoader.mListMDDetectHis[idx]->mProductNo;
    }
    Q_INVOKABLE QString getPName(int idx)
    {
        if(mIsLoading)
            return 0;

        if(mpCoreService->mDataLoader.mListMDDetectHis.size() <= idx)
            return 0;

        return mpCoreService->mDataLoader.mListMDDetectHis[idx]->mProductName;
    }
    Q_INVOKABLE QString getTime(int idx)
    {
        if(mIsLoading)
            return 0;

        if(mpCoreService->mDataLoader.mListMDDetectHis.size() <= idx)
            return 0;

        return mpCoreService->mDataLoader.mListMDDetectHis[idx]->mTime;
    }

public slots:
    void onSignalEventChangedIsLoading(bool value)
    {
        setIsLoading(value);
    }

public:
    explicit PanelMetalDetectHistoryModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        connect(&mpCoreService->mDataLoader     , SIGNAL(signalEventChangedIsLoading           (bool)), this, SLOT(onSignalEventChangedIsLoading           (bool)));

        onSignalEventChangedIsLoading(mpCoreService->mDataLoader.mIsLoading);
    }
};

#endif // PANELMETALDETECTHISTORYMODEL_H
