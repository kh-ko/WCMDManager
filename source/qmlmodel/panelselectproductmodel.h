#ifndef PANELSELECTPRODUCTMODEL_H
#define PANELSELECTPRODUCTMODEL_H

#include <QObject>
#include <QDebug>

#include "source/service/util/svcconnectutil.h"
#include "source/service/coreservice.h"

class CheckProductModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsChecked      READ getIsChecked      NOTIFY signalEventChangedIsChecked     );
    Q_PROPERTY(int     mPSeq           READ getPSeq           NOTIFY signalEventChangedPSeq          );
    Q_PROPERTY(QString mPName          READ getPName          NOTIFY signalEventChangedPName         );

private:
    bool    mIsChecked = true;
    int     mPSeq      = 0;
    int     mPNum      = 0;
    QString mPName     = "";


public:
    bool    getIsChecked(){ return mIsChecked; }
    int     getPSeq     (){ return mPSeq     ; }
    int     getPNum     (){ return mPNum     ; }
    QString getPName    (){ return mPName    ; }

    void    setIsChecked(bool    value){ if(mIsChecked == value) return; mIsChecked = value; emit signalEventChangedIsChecked(mIsChecked); }
    void    setPSeq     (int     value){ if(mPSeq      == value) return; mPSeq      = value; emit signalEventChangedPSeq     (mPSeq     ); }
    void    setPNum     (int     value){ if(mPNum      == value) return; mPNum      = value;                                               }
    void    setPName    (QString value){ if(mPName     == value) return; mPName     = value; emit signalEventChangedPName    (mPName    ); }

signals:
    void signalEventChangedIsChecked(bool    value);
    void signalEventChangedPSeq     (int     value);
    void signalEventChangedPName    (QString value);

public:
    explicit CheckProductModel(QObject *parent = nullptr):QObject(parent)
    {}

};

class PanelSelectProductModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsAllChecked      READ getIsAllChecked      NOTIFY signalEventChangedIsAllChecked     );

private:
    bool    mIsAllChecked = true;

public:
    bool    getIsAllChecked(){ return mIsAllChecked; }
    void    setIsAllChecked(bool value){ if(mIsAllChecked == value) return; mIsAllChecked = value; emit signalEventChangedIsAllChecked(mIsAllChecked); }

signals:
    void signalEventChangedIsAllChecked(bool    value);

private:
    QList<CheckProductModel *> mListProduct;


public slots:
    Q_INVOKABLE void onCommandSetAllSelect(bool value)
    {
        setIsAllChecked(value);

        foreach(CheckProductModel * pProductModel, mListProduct)
        {
            pProductModel->setIsChecked(getIsAllChecked());
        }
    }

    Q_INVOKABLE void onCommandSetSelect(int idx, bool value)
    {
        mListProduct.at(idx)->setIsChecked(value);

        foreach(CheckProductModel * pProductModel, mListProduct)
        {
            if(pProductModel->getIsChecked() == false)
            {
                setIsAllChecked(false);
                return;
            }
        }

        setIsAllChecked(true);
    }


    Q_INVOKABLE int onCommandGetProductListSize()
    {
        return mListProduct.size();
    }

    Q_INVOKABLE CheckProductModel * onCommandGetProductModel(int idx)
    {
        return mListProduct.at(idx);
    }

    Q_INVOKABLE QString onCommandGetSelectProductList()
    {
        QString selectProductSeq;

        foreach(CheckProductModel * pProductModel, mListProduct)
        {
            if(pProductModel->getIsChecked())
            {
                selectProductSeq.append(QString("%1,").arg(pProductModel->getPSeq()));
            }
        }

        return selectProductSeq;
    }

public:
    explicit PanelSelectProductModel(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[PanelSelectProductModel] create instance";

        foreach(PDSettingDto setting, pDLoaderSvc->mDailyHis.mPH.mPDList)
        {
            int insertIdx = 0;
            CheckProductModel * pProductModel = new CheckProductModel(this);
            pProductModel->setIsChecked(true);
            pProductModel->setPSeq(setting.mSeq);
            pProductModel->setPNum(setting.mProductNum);
            pProductModel->setPName(QString("%1 %2").arg(setting.mProductNum,3,10,QChar('0')).arg(setting.mName));

            for(insertIdx = 0; insertIdx < mListProduct.size(); insertIdx ++)
            {
                if(mListProduct[insertIdx]->getPNum() > pProductModel->getPNum())
                    break;
            }
            mListProduct.insert(insertIdx,pProductModel);
        }
    }
};
#endif // PANELSELECTPRODUCTMODEL_H
