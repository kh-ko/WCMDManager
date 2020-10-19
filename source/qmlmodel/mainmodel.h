#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include <QDebug>
#include <QUrl>

#include "source/service/coreservice.h"
#include "source/helper/languagehelper.h"

class MainModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int mSelMenu    READ getSelMenu   NOTIFY signalEventChangedSelMenu  )
    Q_PROPERTY(bool mIsLoading READ getIsLoading NOTIFY signalEventChangedIsLoading)

private:
    LanguageHelper              mLanguageHelper ;
    CoreService                 mCoreService    ;

    int mSelMenu;
    bool mIsLoading;

    int  getSelMenu  (){return mSelMenu  ;}
    bool getIsLoading(){return mIsLoading;}

    void setSelMenu  (int  value){ if(mSelMenu   == value) return; mSelMenu   = value; emit signalEventChangedSelMenu  (mSelMenu  );}
    void setIsLoading(bool value){ if(mIsLoading == value) return; mIsLoading = value; emit signalEventChangedIsLoading(mIsLoading);}

signals:
    void signalEventChangedSelMenu  (int  value);
    void signalEventChangedIsLoading(bool value);

public slots:
    Q_INVOKABLE void onCommandAddHistory(QList<QUrl> urls)
    {
        for(int i = 0; i < urls.length(); i ++)
        {
            QUrl temp = urls.at(i);
            //mFileService.import(temp.toLocalFile());
        }
    }
    Q_INVOKABLE void onCommandSelMenu(int value)
    {
        mCoreService.onCommandSelectMainMenu(value);
    }
    Q_INVOKABLE int onCommandGetSelDay()
    {
        return mCoreService.mLSettingService.mSelectedDay;
    }
    Q_INVOKABLE int onCommandGetSelMonth()
    {
        return mCoreService.mLSettingService.mSelectedMonth;
    }
    Q_INVOKABLE int onCommandGetSelYear()
    {
        return mCoreService.mLSettingService.mSelectedYear;
    }
    Q_INVOKABLE void onCommandLoadLanguage()
    {
        mLanguageHelper.setContext(this);
        mLanguageHelper.loadLanguage((EnumDefine::Language)mCoreService.mLSettingService.mLanguage);
    }

public slots:
    void onSignalEventChangedSelMenu  (int  value){setSelMenu  (value);}
    void onSignalEventChangedIsLoading(bool value){setIsLoading(value);}

public:
    explicit MainModel(QObject *parent = nullptr):QObject(parent)
    {
        QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

        connect(&mCoreService, SIGNAL(signalEventChangedSelMenu(int)), this, SLOT(onSignalEventChangedSelMenu(int)));
        connect(&mCoreService.mDataLoader, SIGNAL(signalEventChangedIsLoading(bool)), this, SLOT(onSignalEventChangedIsLoading(bool)));

        onSignalEventChangedSelMenu(mCoreService.mSelMenu);
        onSignalEventChangedIsLoading(mCoreService.mDataLoader.mIsLoading);
    }
};

#endif // MAINMODEL_H
