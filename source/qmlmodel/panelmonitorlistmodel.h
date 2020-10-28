#ifndef PANELMONITORLISTMODEL_H
#define PANELMONITORLISTMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"
#include "source/qmlmodel/panelmonitoritemmodel.h"

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

    void onSignalEventCompletedDeviceSearch()
    {
        disconnect(&mpCoreService->mDspSearchService, SIGNAL(signalEventCompletedSearch()), this, SLOT(onSignalEventCompletedDeviceSearch()));

        for(int i = 0; i < mpCoreService->mDspSearchService.mListDeviceInfo.size(); i ++)
        {
            int     dNum  = mpCoreService->mDspSearchService.mListDeviceInfo.at(i)->mNumber;
            QString dName = mpCoreService->mDspSearchService.mListDeviceInfo.at(i)->mName;
            QString dIP   = mpCoreService->mDspSearchService.mListDeviceInfo.at(i)->mIp;

            mListItem.append(new PanelMonitorItemModel(dNum, dName, dIP,this));
        }

        int cycleTime = mpCoreService->mLSettingService.mMoniteringRefreshCycle;
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

        connect(&mpCoreService->mDspSearchService, SIGNAL(signalEventCompletedSearch()), this, SLOT(onSignalEventCompletedDeviceSearch()));

        mpCoreService->mDspSearchService.search();
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
