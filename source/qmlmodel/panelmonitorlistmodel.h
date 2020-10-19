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
    void signalEventAddedItem(int idx);

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

    void onSignalEventAddedDeviceInfo(DeviceInfoDto dInfoDto)
    {
        mListItem.append(new PanelMonitorItemModel(dInfoDto,this));

        emit signalEventAddedItem(mListItem.size() - 1);
    }

    void onSignalEventUpdateDeviceInfo(DeviceInfoDto dInfoDto)
    {
        for(int i = 0; i < mListItem.size(); i ++)
        {
            if(mListItem[i]->mDeviceNum == dInfoDto.mDeviceNum)
            {
                mListItem[i]->updateDeviceInfo(dInfoDto);
                return;
            }
        }
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

        for(int i = 0; i < mpCoreService->mDeviceInfoCollector.mListDeviceInfo.size(); i ++)
        {
            mListItem.append(new PanelMonitorItemModel(*(mpCoreService->mDeviceInfoCollector.mListDeviceInfo.at(i)),this));
        }

        connect(&mpCoreService->mDeviceInfoCollector, SIGNAL(signalEventAddedDeviceInfo(DeviceInfoDto)),this, SLOT(onSignalEventAddedDeviceInfo(DeviceInfoDto)));
        connect(&mpCoreService->mDeviceInfoCollector, SIGNAL(signalEventUpdateDeviceInfo(DeviceInfoDto)),this, SLOT(onSignalEventUpdateDeviceInfo(DeviceInfoDto)));

        int cycleTime = mpCoreService->mLSettingService.mMoniteringRefreshCycle;
        mTimer.setInterval(cycleTime < 100 ? 100 : cycleTime);
        mTimer.start();
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeTick()));
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
