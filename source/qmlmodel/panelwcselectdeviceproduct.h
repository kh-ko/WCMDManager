#ifndef PANELWCSELECTDEVICEPRODUCT_H
#define PANELWCSELECTDEVICEPRODUCT_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"

class PanelWCSelectDeviceProductModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mDNum           READ getDNum           NOTIFY signalEventChangedDNum          );
    Q_PROPERTY(QString mDName          READ getDName          NOTIFY signalEventChangedDName         );
    Q_PROPERTY(int     mPNum           READ getPNum           NOTIFY signalEventChangedPNum          );
    Q_PROPERTY(QString mPName          READ getPName          NOTIFY signalEventChangedPName         );

private:
    CoreService * mpCoreService;

    int     mDNum          = 0;
    QString mDName         = "";
    int     mPNum          = 0;
    QString mPName         = "";

    int     getDNum (){ return mDNum ; }
    QString getDName(){ return mDName; }
    int     getPNum (){ return mPNum ; }
    QString getPName(){ return mPName; }

    void    setDNum (int     value){ if(mDNum  == value) return; mDNum  = value; emit signalEventChangedDNum (mDNum ); }
    void    setDName(QString value){ if(mDName == value) return; mDName = value; emit signalEventChangedDName(mDName); }
    void    setPNum (int     value){ if(mPNum  == value) return; mPNum  = value; emit signalEventChangedPNum (mPNum ); }
    void    setPName(QString value){ if(mPName == value) return; mPName = value; emit signalEventChangedPName(mPName); }

signals:
    void signalEventChangedDNum (int     value);
    void signalEventChangedDName(QString value);
    void signalEventChangedPNum (int     value);
    void signalEventChangedPName(QString value);

public slots:
    Q_INVOKABLE int onCommandGetDListSize()
    {
        return mpCoreService->mLSettingService.mDeviceListModel.size();
    }
    Q_INVOKABLE int onCommandGetDNum(int idx)
    {
        return mpCoreService->mLSettingService.mDeviceListModel.at(idx)->mNumber ;
    }
    Q_INVOKABLE QString onCommandGetDName(int idx)
    {
        return mpCoreService->mLSettingService.mDeviceListModel.at(idx)->mName;
    }

    Q_INVOKABLE int onCommandGetProductListSize()
    {
        return mpCoreService->mDataLoader.mWCModel.mListProduct.size();
    }
    Q_INVOKABLE int onCommandGetPNum(int idx)
    {
        return mpCoreService->mDataLoader.mWCModel.mListProduct.at(idx)->mNo;
    }
    Q_INVOKABLE QString onCommandGetPName(int idx)
    {
        return mpCoreService->mDataLoader.mWCModel.mListProduct.at(idx)->mName;
    }
    Q_INVOKABLE quint64 onCommandGetPSeq(int idx)
    {
        return mpCoreService->mDataLoader.mWCModel.mListProduct.at(idx)->mSeq;
    }

    Q_INVOKABLE void onCommandSelDevice(int dNum)
    {
        mpCoreService->mLSettingService.setDeviceNumber(dNum);
    }

    Q_INVOKABLE void onCommandSelProduct(quint64 pSeq)
    {
        mpCoreService->mLSettingService.setWCProductSeq(pSeq);
    }


public slots:
    void onSignalEventChangedDeviceNum()
    {
        int dNum = mpCoreService->mLSettingService.mDeviceNumber;
        setDNum(dNum);

        DeviceInfoModel * pInfo = mpCoreService->mLSettingService.mDeviceListModel.findDeviceInfo(dNum);

        if(pInfo != nullptr)
        {
            setDName(pInfo->mName);
        }
        else
        {
            setDName("");
        }
    }

    void onSignalEventChangedWCProductSeq()
    {
        quint64 value = mpCoreService->mLSettingService.mWCProductSeq;

        for(int i = 0; i < onCommandGetProductListSize(); i ++)
        {
            if(value == onCommandGetPSeq(i))
            {
                setPNum(onCommandGetPNum(i));
                setPName(onCommandGetPName(i));
                return;
            }
        }

        setPNum(0);
        setPName("");
    }

    void onSignalEventChangedIsLoading(bool value)
    {
        if(value == true || mpCoreService->mLSettingService.mWCProductSeq != 0)
            return;

        if(onCommandGetProductListSize() < 1)
            return;

        onCommandSelProduct(onCommandGetPSeq(0));
    }

public:
    explicit PanelWCSelectDeviceProductModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        connect(&mpCoreService->mLSettingService, SIGNAL(signalEventChangedWCProductSeq(    )), this, SLOT(onSignalEventChangedWCProductSeq(    )));
        connect(&mpCoreService->mLSettingService, SIGNAL(signalEventChangedDeviceNumber(    )), this, SLOT(onSignalEventChangedDeviceNum   (    )));
        connect(&mpCoreService->mDataLoader     , SIGNAL(signalEventChangedIsLoading   (bool)), this, SLOT(onSignalEventChangedIsLoading   (bool)));

        onSignalEventChangedDeviceNum();
        onSignalEventChangedWCProductSeq();
    }
};
#endif // PANELWCSELECTDEVICEPRODUCT_H
