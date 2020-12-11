#ifndef PANELSYNCMODEL_H
#define PANELSYNCMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"
#include "source/service/devsearchservice.h"
#include "source/service/devinfoservice.h"
#include "source/service/util/svcconnectutil.h"

#include "source/qmlmodel/panelsynclistitemmodel.h"

class PanelSyncModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool mIsSearch      READ getIsSearch  NOTIFY signalEventChangedIsSearch)

public:
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

        pDevSearchSvc->search();

        ENABLE_SLOT_DEVSEARCH_COMPLETED;
    }

    Q_INVOKABLE void onCommandClose()
    {
        pDLoaderSvc->load(pLSettingSvc->mDeviceNumber, pLSettingSvc->mSelectedDate);
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

    Q_INVOKABLE void onCommandDlistRefresh()
    {
        pDevInfoSvc->refreshList();
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

    void onCompletedSearch()
    {
        DISABLE_SLOT_DEVSEARCH_COMPLETED;

        pDevInfoSvc->refreshList();


        foreach(DevInfoDto devInfo ,pDevSearchSvc->mSearcher.mDevInfoList)
        {
            devInfo.mName = pDevInfoSvc->findDevInfo(devInfo.mNumber).mName;

            mListDevice.append(new PanelSyncListItemModel(devInfo.mNumber, devInfo.mName, devInfo.mIp, this));
        }

        setIsSearch(false);
    }

public:
    explicit PanelSyncModel(QObject *parent = nullptr):QObject(parent)
    {
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
