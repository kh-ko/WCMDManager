#ifndef PANELSYNCMODEL_H
#define PANELSYNCMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"
#include "source/qmlmodel/panelsynclistitemmodel.h"

class PanelSyncModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool mIsSearch      READ getIsSearch  NOTIFY signalEventChangedIsSearch)

public:
    CoreService *  mpCoreService;
    QList<PanelSyncListItemModel *> mListDevice;

    bool mIsSearch = false;

    bool getIsSearch(){ return  mIsSearch;}

    void setIsSearch(bool value){ if(mIsSearch == value) return; mIsSearch = value; emit signalEventChangedIsSearch(mIsSearch);}
signals:
    void signalEventChangedIsCanceling(bool value);
    void signalEventChangedIsSearch(bool value);

public slots:
    Q_INVOKABLE void onCommandOpen()
    {
        clearList();

        setIsSearch(true);

        mpCoreService = CoreService::getInstance();

        connect(&mpCoreService->mDspSearchService, SIGNAL(signalEventCompletedSearch()), this, SLOT(onSignalEventCompletedDeviceSearch()));

        mpCoreService->mDspSearchService.search();
    }

    Q_INVOKABLE void onCommandClose()
    {
        foreach(PanelSyncListItemModel* item, mListDevice)
        {
            if(item->mRSyncError == EnumDefine::RemoteSyncErrorType::RSYNC_ERROR_NONE && item->mState == EnumDefine::RemoteSyncState::RSYNC_STATE_FINISHED)
            {
                mpCoreService->reLoad();
            }
        }
    }

    Q_INVOKABLE void onCommandSync()
    {
        for(int i = 0; i < mListDevice.size(); i ++)
        {
            mListDevice[i]->sync();
        }
    }

    Q_INVOKABLE void onCommandCancle()
    {
        for(int i = 0; i < mListDevice.size(); i ++)
        {
            mListDevice[i]->cancle();
        }
    }
    Q_INVOKABLE int onCommandGetDlistSize()
    {
        return mListDevice.size();
    }

    Q_INVOKABLE PanelSyncListItemModel * onCommandGetDlistItem(int idx)
    {
        if(idx < 0 || idx > mListDevice.size())
            return nullptr;

        return mListDevice[idx];
    }

    Q_INVOKABLE bool onCommandGetIsSyncing()
    {
        for(int i = 0; i < mListDevice.size(); i ++)
        {
            if(mListDevice[i]->mState == EnumDefine::RemoteSyncState::RSYNC_STATE_SYNCING)
                return true;
        }

        return false;
    }

    void onSignalEventCompletedDeviceSearch()
    {
        disconnect(&mpCoreService->mDspSearchService, SIGNAL(signalEventCompletedSearch()), this, SLOT(onSignalEventCompletedDeviceSearch()));

        for(int i = 0; i < mpCoreService->mDspSearchService.mListDeviceInfo.size(); i ++)
        {
            int     dNum  = mpCoreService->mDspSearchService.mListDeviceInfo.at(i)->mNumber;
            QString dName = mpCoreService->mDspSearchService.mListDeviceInfo.at(i)->mName;
            QString dIP   = mpCoreService->mDspSearchService.mListDeviceInfo.at(i)->mIp;

            PanelSyncListItemModel * pItem = new PanelSyncListItemModel(dNum, dName, dIP, this);

            mListDevice.append(pItem);
        }

        setIsSearch(false);
    }

public:
    explicit PanelSyncModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();
    }
    ~PanelSyncModel()
    {
        clearList();
    }

private:
    void clearList()
    {
        for(int i = 0; i < mListDevice.size(); i ++)
        {
            delete mListDevice[i];
        }

        mListDevice.clear();
    }
};
#endif // PANELSYNCMODEL_H
