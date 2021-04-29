#ifndef PANELWCHISTORYMODEL_H
#define PANELWCHISTORYMODEL_H
#include <QObject>
#include <QDebug>
#include <QtMath>

#include "source/service/util/svcconnectutil.h"
#include "source/service/coreservice.h"

class PanelWCHistoryModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int    mTotalCnt           READ getTotalCnt)


private:
    QList<EventDto> mEventList;

public:
    int  mTotalCnt = 0;
    int  getTotalCnt(){ return mTotalCnt; }
    void setTotalCnt(int value){ if(mTotalCnt == value) return; mTotalCnt = value;}

signals:
    void signalEventChangedHistory();

public slots:
    Q_INVOKABLE int onCommandGetListSize()
    {
        return mEventList.size();
    }

    Q_INVOKABLE QString onCommandGetTime(int idx)
    {
        if(mEventList.size() - 1< idx)
            return "";

        return QString("%1").arg(mEventList[idx].mDateTime.toString(TIME_FMT));
    }


    Q_INVOKABLE int onCommandGetType(int idx)
    {
        if(mEventList.size() - 1< idx)
            return 0;

        return mEventList[idx].mEType;
    }

    Q_INVOKABLE int onCommandGetValue(int idx)
    {
        if(mEventList.size() - 1< idx)
            return 0;

        return mEventList[idx].mEValue;
    }

    void onChangedIsLoading(bool value)
    {
        if(value)
        {
            mEventList.clear();
            return;
        }

        loadData();
    }

    void onChangedWCProductSeq()
    {
        loadData();
    }


public:
    void loadData()
    {
        mEventList.clear();

        for(int i = 0; i < pDLoaderSvc->mDailyHis.mEH.mWCEventList.size(); i ++)
        {
            if(pDLoaderSvc->mDailyHis.mEH.mWCEventList[i].mPDSeq == pLSettingSvc->mWCProductSeq)
            {
                mEventList.append(pDLoaderSvc->mDailyHis.mEH.mWCEventList[i]);
            }
        }

        setTotalCnt(mEventList.size());

        emit signalEventChangedHistory();
    }

    explicit PanelWCHistoryModel(QObject *parent = nullptr):QObject(parent)
    {
        ENABLE_SLOT_DLOAD_CHANGED_IS_LOADING;
        ENABLE_SLOT_LSETTING_CHANGED_SEL_WC_PD;

        onChangedIsLoading(pDLoaderSvc->mIsLoading);
        onChangedWCProductSeq();
    }
};
#endif // PANELWCHISTORYMODEL_H
