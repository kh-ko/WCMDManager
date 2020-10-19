#ifndef CORESERVICE_H
#define CORESERVICE_H

#include <QObject>
#include <QApplication>
#include <QDir>

#include "source/globaldef/EnumDefine.h"
#include "source/service/localsettingservice.h"
#include "source/service/dataloaderservice.h"
#include "source/thread/deviceinfocollector.h"
#include "source/util/myalloc.h"

class CoreService : public QObject
{
    Q_OBJECT
public:
    static CoreService  *mpSelf;
    MyAlloc              mAllocUtil;

    QString              mAppDirPath;
    LocalSettingService  mLSettingService;
    DataLoaderService    mDataLoader;
    DeviceInfoCollector  mDeviceInfoCollector;

    int  mSelMenu   = EnumDefine::Menu::MENU_METAL_DETECTOR;

    void setSelMenu  (int  value){ if(mSelMenu   == value) return; mSelMenu   = value; emit signalEventChangedSelMenu  (mSelMenu  ); }

signals:
    void signalEventChangedSelMenu  (int  value);

public:
    void onCommandSelectMainMenu(int value);
    void onCommandAddHistoryFile(QStringList fileList);

public slots:
    void onSignalEventChangedSelectDate  ();
    void onSignalEventChangedDeviceNumber();

public:

    void reLoad(        );
    static CoreService * getInstance();
    explicit CoreService(QObject *parent = nullptr);


};

#endif // CORESERVICE_H
