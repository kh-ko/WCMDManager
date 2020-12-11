#ifndef PANELWCSELECTDEVICEPRODUCT_H
#define PANELWCSELECTDEVICEPRODUCT_H

#include <QObject>
#include <QDebug>

#include "source/service/util/svcconnectutil.h"
#include "source/service/coreservice.h"

class PanelWCSelectDeviceProductModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mPNum           READ getPNum           NOTIFY signalEventChangedPNum          );
    Q_PROPERTY(QString mPName          READ getPName          NOTIFY signalEventChangedPName         );

private:
    CoreService * mpCoreService;

    int     mPNum          = 0;
    QString mPName         = "";

    int     getPNum (){ return mPNum ; }
    QString getPName(){ return mPName; }

    void    setPNum (int     value){ if(mPNum  == value) return; mPNum  = value; emit signalEventChangedPNum (mPNum ); }
    void    setPName(QString value){ if(mPName == value) return; mPName = value; emit signalEventChangedPName(mPName); }

signals:
    void signalEventChangedPNum (int     value);
    void signalEventChangedPName(QString value);

public slots:
    Q_INVOKABLE int onCommandGetProductListSize()
    {
        return pDLoaderSvc->mDailyHis.mPH.mPDList.size();
    }
    Q_INVOKABLE int onCommandGetPNum(int idx)
    {
        return pDLoaderSvc->mDailyHis.mPH.mPDList[idx].mProductNum;
    }
    Q_INVOKABLE QString onCommandGetPName(int idx)
    {
        return pDLoaderSvc->mDailyHis.mPH.mPDList[idx].mName;
    }
    Q_INVOKABLE quint64 onCommandGetPSeq(int idx)
    {
        return pDLoaderSvc->mDailyHis.mPH.mPDList[idx].mSeq;
    }

    Q_INVOKABLE void onCommandSelProduct(quint64 pSeq)
    {
        pLSettingSvc->setWCProductSeq(pSeq);
    }


public slots:
    void onChangedWCProductSeq()
    {
        PDSettingDto setting = pDLoaderSvc->mDailyHis.mPH.findSettingDto(pLSettingSvc->mWCProductSeq);

        setPNum(setting.mProductNum);
        setPName(setting.mName);
    }

    void onChangedIsLoading(bool value)
    {
        if(value == true || pLSettingSvc->mWCProductSeq != 0)
            return;

        if(onCommandGetProductListSize() < 1)
            return;

        onCommandSelProduct(onCommandGetPSeq(0));
    }

public:
    explicit PanelWCSelectDeviceProductModel(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[PanelWCSelectDeviceProductModel] create instance";

        ENABLE_SLOT_LSETTING_CHANGED_SEL_WC_PD;
        ENABLE_SLOT_DLOAD_CHANGED_IS_LOADING;

        onChangedIsLoading(pDLoaderSvc->mIsLoading);
        onChangedWCProductSeq();

    }
};
#endif // PANELWCSELECTDEVICEPRODUCT_H
