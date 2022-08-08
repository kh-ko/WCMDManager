#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include <QDebug>
#include <QUrl>

#include "source/service/dataloaderservice.h"
#include "source/service/localsettingservice.h"
#include "source/service/coreservice.h"
#include "source/service/util/svcconnectutil.h"

#include "source/history/historycopy.h"

#include "source/helper/languagehelper.h"


class MainModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mVersion READ getVersion   NOTIFY signalEventChangedVersion  )
    Q_PROPERTY(int mSelMenu     READ getSelMenu   NOTIFY signalEventChangedSelMenu  )
    Q_PROPERTY(bool mIsLoading  READ getIsLoading NOTIFY signalEventChangedIsLoading)

private:
    HistoryCopy                 mHisCopy;
    LanguageHelper              mLanguageHelper ;

    QString mVersion;
    int     mSelMenu;
    bool    mIsLoading;

    QString getVersion  (){return mVersion  ;}
    int     getSelMenu  (){return mSelMenu  ;}
    bool    getIsLoading(){return mIsLoading;}

    void setVersion  (QString value){ if(mVersion   == value) return; mVersion   = value; emit signalEventChangedVersion  (mVersion  );}
    void setSelMenu  (int     value){ if(mSelMenu   == value) return; mSelMenu   = value; emit signalEventChangedSelMenu  (mSelMenu  );}
    void setIsLoading(bool    value){ if(mIsLoading == value) return; mIsLoading = value; emit signalEventChangedIsLoading(mIsLoading);}

signals:
    void signalEventChangedVersion  (QString value);
    void signalEventChangedSelMenu  (int     value);
    void signalEventChangedIsLoading(bool    value);
    void signalEventCopyProgress(int procIdx, int totalCnt);
    void signalEventCopyComplete();

public slots:
    Q_INVOKABLE void onCommandAddHistory(QUrl url)
    {
        qDebug() << "[debug]" << url;

        mHisCopy.copy(url.toLocalFile());
    }
    Q_INVOKABLE void onCommandSelMenu(int value)
    {
        pCoreSvc->setSelMenu((EnumDefine::Menu)value);
    }
    Q_INVOKABLE int onCommandGetSelDay()
    {
        return pLSettingSvc->mSelectedDate.day();
    }
    Q_INVOKABLE int onCommandGetSelMonth()
    {
        return pLSettingSvc->mSelectedDate.month();
    }
    Q_INVOKABLE int onCommandGetSelYear()
    {
        return pLSettingSvc->mSelectedDate.year();
    }
    Q_INVOKABLE void onCommandLoadLanguage()
    {
        mLanguageHelper.setContext(this);
        mLanguageHelper.loadLanguage((EnumDefine::Language)pLSettingSvc->mLanguage);
    }

public slots:
    void onChangedSelMenu  (          ){setSelMenu  (pCoreSvc->getSelMenu());}
    void onChangedIsLoading(bool value){setIsLoading(value                 ); mLanguageHelper.loadLanguage((EnumDefine::Language)pLSettingSvc->mLanguage);}
    void onSignalEventCopyProgress(int procIdx, int totalCnt){ emit signalEventCopyProgress(procIdx, totalCnt);}
    void onSignalEventCopyComplete(bool isSucc)
    {
        pDLoaderSvc->load(pLSettingSvc->mDeviceNumber, pLSettingSvc->mSelectedDate);
        emit signalEventCopyComplete();
    }

public:
    explicit MainModel(QObject *parent = nullptr):QObject(parent)
    {
        QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

        connect(&mHisCopy, SIGNAL(signalEventProgress(int, int)), this, SLOT(onSignalEventCopyProgress(int, int)));
        connect(&mHisCopy, SIGNAL(signalEventComplete(bool)), this, SLOT(onSignalEventCopyComplete(bool)));

        pCoreSvc->start();

        ENABLE_SLOT_CORE_CHANGED_SEL_MENU;
        ENABLE_SLOT_DLOAD_CHANGED_IS_LOADING;

        mLanguageHelper.setContext(this);

        setVersion(pLSettingSvc->mVersion);
        onChangedSelMenu();
        onChangedIsLoading(pDLoaderSvc->mIsLoading);
    }
};

#endif // MAINMODEL_H
