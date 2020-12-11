#ifndef CORESERVICE_H
#define CORESERVICE_H

#include <QObject>
#include <QApplication>
#include <QDir>

#include "source/globaldef/EnumDefine.h"
#include "source/service/localsettingservice.h"
#include "source/service/dataloaderservice.h"
#include "source/util/myalloc.h"

#define pCoreSvc CoreService::getInstance()

class CoreService : public QObject
{
    Q_OBJECT
public:
    static CoreService * getInstance()
    {
        static CoreService  *pSelf = nullptr;

        if(pSelf == nullptr)
        {
            pSelf = new CoreService();
        }

        return pSelf;
    }

    explicit CoreService(QObject *parent = nullptr)
    {
    }

    void start()
    {
        pLSettingSvc->start();
        pDLoaderSvc->start(pLSettingSvc->mDeviceNumber, pLSettingSvc->mSelectedDate);
    }

    void setSelMenu(EnumDefine::Menu menu)
    {
        int * pSelMenu = getSelMenuPtr();
        *pSelMenu = (int)menu;

        emit signalEventChangedSelMenu();
    }

    int getSelMenu()
    {
        return * getSelMenuPtr();
    }
signals:
    void signalEventChangedSelMenu();

private:
    int * getSelMenuPtr()
    {
        static int selMenu = EnumDefine::MENU_METAL_DETECTOR;

        return &selMenu;
    }
};

#endif // CORESERVICE_H
