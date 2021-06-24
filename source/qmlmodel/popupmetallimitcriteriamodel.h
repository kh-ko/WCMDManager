#ifndef POPUPMETALLIMITCRITERIAMODEL_H
#define POPUPMETALLIMITCRITERIAMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h"
#include "source/service/devsearchservice.h"
#include "source/service/devinfoservice.h"
#include "source/qmlmodel/panelmonitoritemmodel.h"
#include "source/service/util/svcconnectutil.h"

class PopupMetalLimitCriteriaModel : public QObject
{
    Q_OBJECT

public:
    QString        mStrLimitCriteriaList;

    CoreService *  mpCoreService;
    QList<quint64> mPDSeqList;
    QList<quint16> mPDNumList;
    QList<QString> mPDNameList;
    QList<QString> mLimitFeList;
    QList<QString> mLimitSusList;

    DevInfoDto     mDevInfo;
    QString        getStrLimitCriteriaList(){ return mStrLimitCriteriaList;}
    void           setStrLimitCriteriaList(QString value) { if(mStrLimitCriteriaList == value) return; mStrLimitCriteriaList = value; emit signalEventChangedStrLimitCriteriaList(mStrLimitCriteriaList);}
signals:
    void signalEventChangedStrLimitCriteriaList(QString value);

public slots:
    Q_INVOKABLE void onCommandLoad()
    {
        pDevInfoSvc->refreshList();

        mDevInfo = pDevInfoSvc->findDevInfo(pLSettingSvc->mDeviceNumber);

        mPDSeqList.clear();
        mPDNumList.clear();
        mPDNameList.clear();
        mLimitFeList.clear();
        mLimitSusList.clear();

        for(int i = 0; i < pDLoaderSvc->mMonthlyStatsHis.mPDList.size(); i ++)
        {
            mPDSeqList.append(pDLoaderSvc->mMonthlyStatsHis.mPDList[i].mSeq);
            mPDNumList.append(pDLoaderSvc->mMonthlyStatsHis.mPDList[i].mNum);
            mPDNameList.append(pDLoaderSvc->mMonthlyStatsHis.mPDList[i].mName);
            mLimitFeList.append(mDevInfo.getLimFe(pDLoaderSvc->mMonthlyStatsHis.mPDList[i].mSeq));
            mLimitSusList.append(mDevInfo.getLimSus(pDLoaderSvc->mMonthlyStatsHis.mPDList[i].mSeq));
        }
    }

    Q_INVOKABLE int onCommandGetLimitCriteriaCnt()
    {
        return mPDSeqList.size();
    }

    Q_INVOKABLE quint16 onCommandGetPDNum(int idx)
    {
        return mPDNumList.at(idx);
    }

    Q_INVOKABLE QString onCommandGetPDName(int idx)
    {
        return mPDNameList.at(idx);
    }

    Q_INVOKABLE QString onCommandGetlimitCriteriaFe(int idx)
    {
        return mLimitFeList.at(idx);
    }

    Q_INVOKABLE QString onCommandGetlimitCriteriaSus(int idx)
    {
        return mLimitSusList.at(idx);
    }

    Q_INVOKABLE void onCommandSetLimitCriteriaFe(int idx, QString limFe)
    {
        mLimitFeList[idx] = limFe;
    }

    Q_INVOKABLE void onCommandSetLimitCriteriaSus(int idx, QString limSus)
    {
        mLimitSusList[idx] = limSus;
    }

    Q_INVOKABLE void onCommandApply()
    {
        QString strLimCriteria;

        for(int i = 0; i < mPDSeqList.size(); i ++)
        {
            strLimCriteria.append(QString(" %1;%2;%3").arg(mPDSeqList[i]).arg(mLimitFeList[i]).arg(mLimitSusList[i]));
        }

        pDevInfoSvc->editDevMDLimit(pLSettingSvc->mDeviceNumber, strLimCriteria);

        return;
    }

public:
    explicit PopupMetalLimitCriteriaModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();
    }
    ~PopupMetalLimitCriteriaModel()
    {
    }

};

#endif // POPUPMETALLIMITCRITERIAMODEL_H
