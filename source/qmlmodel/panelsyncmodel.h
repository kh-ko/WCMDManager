#ifndef PANELSYNCMODEL_H
#define PANELSYNCMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"
#include "source/qmlmodel/panelsynclistitemmodel.h"

class PanelSyncModel : public QObject
{
    Q_OBJECT
public:
    CoreService *  mpCoreService;
    QList<PanelSyncListItemModel *> mListDevice;

signals:
    void signalEventChangedIsCanceling(bool value);

public slots:
    Q_INVOKABLE void onCommandOpen()
    {
        clearList();

        for(int i = 0; i < mpCoreService->mDeviceInfoCollector.mListDeviceInfo.size(); i ++)
        {
            DeviceInfoDto * dInfo = mpCoreService->mDeviceInfoCollector.mListDeviceInfo[i];
            PanelSyncListItemModel * pItem = new PanelSyncListItemModel(dInfo->mDeviceNum, dInfo->mDeviceName, dInfo->mIp, this);

            //connect(pItem, SIGNAL(signalEventChangedState(int )), this, SLOT(onSignalEventChangedState(int)));
            mListDevice.append(pItem);
        }
    }

    Q_INVOKABLE void onCommandClose()
    {
        mpCoreService->reLoad();
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
