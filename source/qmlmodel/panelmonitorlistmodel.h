#ifndef PANELMONITORLISTMODEL_H
#define PANELMONITORLISTMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"
#include "source/service/devsearchservice.h"
#include "source/service/devinfoservice.h"
#include "source/qmlmodel/panelmonitoritemmodel.h"
#include "source/service/util/svcconnectutil.h"

class PanelMonitorListModel : public QObject
{
    Q_OBJECT
public:
    QTimer         mTimer;
    CoreService *  mpCoreService;
    QList<PanelMonitorItemModel *> mListItem;

signals:
    void signalEventCompletedDeviceSearch();

public slots:
    Q_INVOKABLE int onCommandGetMonitorListSize()
    {
        return mListItem.size();
    }

    Q_INVOKABLE PanelMonitorItemModel * onCommandGetMonitorListItem(int idx)
    {
        if(idx < 0 || idx > mListItem.size())
            return nullptr;

        return mListItem[idx];
    }

    void onCompletedSearch()
    {
        DISABLE_SLOT_DEVSEARCH_COMPLETED;

        pDevInfoSvc->refreshList();


        foreach(DevInfoDto devInfo ,pDevSearchSvc->mSearcher.mDevInfoList)
        {
            devInfo.mName = pDevInfoSvc->findDevInfo(devInfo.mNumber).mName;

            mListItem.append(new PanelMonitorItemModel(devInfo.mNumber, devInfo.mName, devInfo.mIp, this));
        }

        int cycleTime = pLSettingSvc->mMoniteringRefreshCycle;
        mTimer.setInterval(cycleTime < 100 ? 100 : cycleTime);
        mTimer.start();
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeTick()));

        emit signalEventCompletedDeviceSearch();
    }

    void onTimeTick()
    {
        for(int i = 0; i < mListItem.size(); i ++)
        {
            mListItem[i]->reqRStatus();
        }
    }

public:
    explicit PanelMonitorListModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        pDevSearchSvc->search();

        ENABLE_SLOT_DEVSEARCH_COMPLETED;
    }
    ~PanelMonitorListModel()
    {
        clearList();
    }

private:
    void clearList()
    {
        for(int i = 0; i < mListItem.size(); i ++)
        {
            delete mListItem[i];
        }

        mListItem.clear();
    }
};
#endif // PANELMONITORLISTMODEL_H
