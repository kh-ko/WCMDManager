#ifndef PANELSYNCLISTITEMMODEL_H
#define PANELSYNCLISTITEMMODEL_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include "source/service/coreservice.h"
#include "source/thread/remotehistorydatasyncer.h"

class PanelSyncListItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mDeviceNO       READ getDeviceNO       NOTIFY signalEventChangedDeviceNO      );
    Q_PROPERTY(QString mDeviceName     READ getDeviceName     NOTIFY signalEventChangedDeviceName    );
    Q_PROPERTY(QString mDeviceIP       READ getDeviceIP       NOTIFY signalEventChangedDeviceIP      );
    Q_PROPERTY(QString mLastSyncDate   READ getLastSyncDate   NOTIFY signalEventChangedLastSyncDate  );
    Q_PROPERTY(float   mProgressValue  READ getProgressValue  NOTIFY signalEventChangedProgressValue );
    Q_PROPERTY(bool    mIsDisconnected READ getIsDisconnected NOTIFY signalEventChangedIsDisconnected);
    Q_PROPERTY(int     mState          READ getState          NOTIFY signalEventChangedState         );
    Q_PROPERTY(int     mRSyncError     READ getRSyncError     NOTIFY signalEventChangedRSyncError    );

public:
    RemoteHistoryDataSyncer mSyncer;

    int     mDeviceNO              ;
    QString mDeviceName            ;
    QString mDeviceIP              ;
    QString mLastSyncDate          ;
    float   mProgressValue  = 0    ;
    bool    mIsDisconnected = false;
    int     mState          = EnumDefine::RemoteSyncState::RSYNC_STATE_READY;
    int     mRSyncError     = EnumDefine::RemoteSyncErrorType::RSYNC_ERROR_NONE;

public:
    int     getDeviceNO      (){ return mDeviceNO      ;}
    QString getDeviceName    (){ return mDeviceName    ;}
    QString getDeviceIP      (){ return mDeviceIP      ;}
    QString getLastSyncDate  (){ return mLastSyncDate  ;}
    float   getProgressValue (){ return mProgressValue ;}
    bool    getIsDisconnected(){ return mIsDisconnected;}
    int     getState         (){ return mState         ;}
    int     getRSyncError    (){ return mRSyncError    ;}

    void setDeviceNO      (int     value){ if(mDeviceNO      == value) return; mDeviceNO      = value; emit signalEventChangedDeviceNO      (mDeviceNO      );}
    void setDeviceName    (QString value){ if(mDeviceName    == value) return; mDeviceName    = value; emit signalEventChangedDeviceName    (mDeviceName    );}
    void setDeviceIP      (QString value){ if(mDeviceIP      == value) return; mDeviceIP      = value; emit signalEventChangedDeviceIP      (mDeviceIP      );}
    void setLastSyncDate  (QString value){ if(mLastSyncDate  == value) return; mLastSyncDate  = value; emit signalEventChangedLastSyncDate  (mLastSyncDate  );}
    void setProgressValue (float   value){ if(mProgressValue == value) return; mProgressValue = value; emit signalEventChangedProgressValue (mProgressValue );}
    void setIsDisconnected(bool    value){ if(mIsDisconnected== value) return; mIsDisconnected= value; emit signalEventChangedIsDisconnected(mIsDisconnected);}
    void setState         (int     value){ if(mState         == value) return; mState         = value; emit signalEventChangedState         (mState         );}
    void setRSyncError    (int     value){ if(mRSyncError    == value) return; mRSyncError    = value; emit signalEventChangedRSyncError    (mRSyncError    );}

signals:
    void signalEventChangedDeviceNO      (int     value);
    void signalEventChangedDeviceName    (QString value);
    void signalEventChangedDeviceIP      (QString value);
    void signalEventChangedLastSyncDate  (QString value);
    void signalEventChangedProgressValue (float   value);
    void signalEventChangedIsDisconnected(bool    value);
    void signalEventChangedState         (int     value);
    void signalEventChangedRSyncError    (int     value);

public slots:
    void onSignalEventProgress(float value)
    {
        setProgressValue(value);
    }

    void onSignalEventFinished(int error)
    {
        qDebug() << "[onSignalEventFinished]" << error;
        setState(EnumDefine::RemoteSyncState::RSYNC_STATE_FINISHED);
        setRSyncError(error);
    }

public:
    void sync()
    {
        if(mIsDisconnected)
        {
            setState(EnumDefine::RemoteSyncState::RSYNC_STATE_FINISHED);
        }
        else
        {
            setState(EnumDefine::RemoteSyncState::RSYNC_STATE_SYNCING);
            qDebug() << "[PanelSyncListItemModel::onSignalEventFinished] sync date" << mLastSyncDate;

            mSyncer.sync(mDeviceNO,mDeviceIP, mLastSyncDate, mDeviceNO);
        }
    }

    void cancle()
    {
        mSyncer.cancle();
    }
    explicit PanelSyncListItemModel(QObject *parent = nullptr):QObject(parent)
    {
    }

    PanelSyncListItemModel(int deviceNo, QString deviceName, QString deviceIp, QObject *parent = nullptr):QObject(parent)
    {
        setDeviceNO(deviceNo);
        setDeviceIP(deviceIp);
        setDeviceName(deviceName);

        if(deviceIp == "")
            setIsDisconnected(true);

        QDir dir(QString("%1/database/%2").arg(QApplication::applicationDirPath()).arg(deviceNo));

        QStringList dirList = dir.entryList(QStringList() << "*-EH.txt", QDir::Files, QDir::SortFlag::Name);

        if(dirList.size() > 0)
        {
            QString date = dirList.at(dirList.size() - 1).split(".")[0];

            if(date.contains("-") == false)
                return ;

            setLastSyncDate(date.replace('-', ".").left(10));
        }

        connect(&mSyncer, SIGNAL(signalEventProgress(float)), this, SLOT(onSignalEventProgress(float)));
        connect(&mSyncer, SIGNAL(signalEventFinished(int  )), this, SLOT(onSignalEventFinished(int  )));
    }
};
#endif // PANELSYNCLISTITEMMODEL_H
