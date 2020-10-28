#include "coreservice.h"

CoreService * CoreService::mpSelf = nullptr;

void CoreService::onCommandSelectMainMenu(int value)
{
    setSelMenu(value);
}

void CoreService::onCommandAddHistoryFile(QStringList fileList)
{

}

void CoreService::onSignalEventChangedSelectDate  ()
{
    mDataLoader.loadData(mLSettingService.mDeviceNumber, mLSettingService.mSelectedYear, mLSettingService.mSelectedMonth, mLSettingService.mSelectedDay);
}

void CoreService::onSignalEventChangedDeviceNumber()
{
    mDataLoader.loadData(mLSettingService.mDeviceNumber, mLSettingService.mSelectedYear, mLSettingService.mSelectedMonth, mLSettingService.mSelectedDay);
}

void CoreService::reLoad()
{
    mDataLoader.loadData(mLSettingService.mDeviceNumber, mLSettingService.mSelectedYear, mLSettingService.mSelectedMonth, mLSettingService.mSelectedDay, true);
}

CoreService * CoreService::getInstance()
{
    return mpSelf;
}

CoreService::CoreService(QObject *parent) : QObject(parent)
{
    mpSelf = this;

    mAppDirPath = QApplication::applicationDirPath();

    QDir dir(QString("%1/database").arg(mAppDirPath));

    QStringList dirList = dir.entryList(QDir::Dirs, QDir::SortFlag::Name);

    for(int i = 0; i < dirList.size(); i++)
    {
        if(dirList.at(i).toInt() != 0)
        {
            mLSettingService.addDeviceInfo(dirList.at(i).toInt());
            //mDeviceInfoCollector.addDeviceNumber(dirList.at(i).toInt());
        }
    }

    /*
    if(mLSettingService.mDeviceNumber == 0 && mDeviceInfoCollector.mListDeviceInfo.size() > 0 )
    {
        mLSettingService.setDeviceNumber(mDeviceInfoCollector.mListDeviceInfo[0]->mDeviceNum);
    }*/
    if(mLSettingService.mDeviceNumber == 0 && mLSettingService.mDeviceListModel.size() > 0 )
    {
        mLSettingService.setDeviceNumber(mLSettingService.mDeviceListModel.at(0)->mNumber);
    }

    connect(&mLSettingService, SIGNAL(signalEventChangedSelectDate  ()), this, SLOT(onSignalEventChangedSelectDate  ()));
    connect(&mLSettingService, SIGNAL(signalEventChangedDeviceNumber()), this, SLOT(onSignalEventChangedDeviceNumber()));

    onSignalEventChangedDeviceNumber();

}
