#ifndef PANELWCREPORTMODEL_H
#define PANELWCREPORTMODEL_H

#include <QObject>
#include <QDate>
#include <QDebug>
#include "source/service/coreservice.h"
#include "source/qmlmodel/panelwcreportproductmodel.h"

class PanelWCReportModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mStrDate  READ getStrDate  NOTIFY signalEventChangedStrDate );
    Q_PROPERTY(quint16 mSelPNum  READ getSelPNum  NOTIFY signalEventChangedSelPNum );
    Q_PROPERTY(QString mSelPName READ getSelPName NOTIFY signalEventChangedSelPName);

public:
    CoreService * mpCoreService;
    QString mPSFileName  ;
    QString mPHisFileName;
    QString mEHisFileName;

    QString mStrDate ;
    quint16 mSelPNum ;
    QString mSelPName;

    QList<PanelWCReportProductModel *> mListProduct;

    int     mYear;
    int     mMonth;
    int     mDay;
    QStringList mListStrWeekOfDayKor;
    QStringList mListStrMonthEng;

    QString getStrDate (){ return mStrDate ;}
    quint16 getSelPNum (){ return mSelPNum ;}
    QString getSelPName(){ return mSelPName;}

    void    setStrDate (QString value){ if(mStrDate  == value) return; mStrDate  = value; emit signalEventChangedStrDate (mStrDate );}
    void    setSelPNum (quint16 value){ if(mSelPNum  == value) return; mSelPNum  = value; emit signalEventChangedSelPNum (mSelPNum );}
    void    setSelPName(QString value){ if(mSelPName == value) return; mSelPName = value; emit signalEventChangedSelPName(mSelPName);}

signals:
    void signalEventChangedStrDate (QString value);
    void signalEventChangedSelPNum (quint16 value);
    void signalEventChangedSelPName(QString value);
    void signalEventLoaded();

    void signalCommandReadProductStatistics(QString path, QString fileName);
    void signalCommandReadProductHistory(QString path, QString fileName);
    void signalCommandReadEventHistory(QString path, QString fileName, int lineCnt);

public slots:
    Q_INVOKABLE PanelWCReportProductModel * onCommandGetProductModel(quint64 seq)
    {
        return findProductBySeq(seq);
    }

    Q_INVOKABLE PanelWCReportProductModel * onCommandGetProductModel(int idx)
    {
        return mListProduct[idx];
    }
    Q_INVOKABLE void onCommandSetStrDate(QString value)
    {
        setStrDate(value);
    }

public:
    void setFileName(QString fileName)
    {
        mPSFileName   = QString("%1-PS.txt").arg(fileName.split("-EH.txt")[0]);
        mPHisFileName = QString("%1-PH.txt").arg(fileName.split("-EH.txt")[0]);
        mEHisFileName = fileName; //QString("%1-EH.txt").arg(fileName.split("-EH.txt")[0]);
        setDateByFileName(fileName);
    }

    void setDateByFileName(QString fileName)
    {
        /*
        QString date = fileName.split("-EH.txt")[0];

        mYear     = date.split("-")[0].toInt();
        mMonth    = date.split("-")[1].toInt();
        mDay      = date.split("-")[2].toInt();
        QDate   temp(mYear, mMonth, mDay);
        QString weekOfDay = mListStrWeekOfDayKor[temp.dayOfWeek() - 1];

        if(mpCoreService->mLSettingService.mLanguage == EnumDefine::Language::LANG_KOR){
            mStrDate = QString("%1 년 %2 월 %3 일 %4요일").arg(QString::number(mYear).rightJustified(4, '0'))
                                                        .arg(QString::number(mMonth).rightJustified(2, '0'))
                                                        .arg(QString::number(mDay).rightJustified(2, '0'))
                                                        .arg(weekOfDay);
        }
        else
        {
            QString month = mListStrMonthEng[mMonth - 1];

            mStrDate = QString("%1 %2th, %3").arg(month)
                                             .arg(QString::number(mDay).rightJustified(2, '0'))
                                             .arg(QString::number(mYear).rightJustified(4, '0'));
        }
        */
    }

    void load()
    {
        /*
        qDebug() << "[debug]wc report load";

        connect(this, SIGNAL(signalCommandReadProductStatistics(QString, QString)), &mFileLoader, SLOT(onCommandReadAll(QString, QString)));
        connect(&mFileLoader, SIGNAL(signalReadAll(int, QString)), this, SLOT(onSignalReadProductStatistics(int, QString)));

        QString path = QString("%1/database/%2").arg(QApplication::applicationDirPath()).arg(mpCoreService->mLSettingService.mDeviceNumber);

        emit signalCommandReadProductStatistics(path, mPSFileName);
        */
    }

public slots:
    void onSignalReadProductStatistics(int error, QString content)
    {
        /*
        if(error != EnumDefine::FileErrorType::FILE_ERROR_NONE)
        {
            qDebug() << "[debug]onSignalReadProductStatistics : error";

            emit signalEventLoaded();
            return;
        }

        qDebug() << "[debug]onSignalReadProductStatistics : content = " << content;

        QStringList tempList = content.split("\n");
        tempList.removeLast();

        setProductList(tempList);

        disconnect(this, SIGNAL(signalCommandReadProductStatistics(QString, QString)), &mFileLoader, SLOT(onCommandReadAll(QString, QString)));
        disconnect(&mFileLoader, SIGNAL(signalReadAll(int, QString)), this, SLOT(onSignalReadProductStatistics(int, QString)));

        connect(this, SIGNAL(signalCommandReadProductHistory(QString, QString)), &mFileLoader, SLOT(onCommandReadAll(QString, QString)));
        connect(&mFileLoader, SIGNAL(signalReadAll(int, QString)), this, SLOT(onSignalReadProductHistory(int, QString)));

        QString path = QString("%1/database/%2").arg(QApplication::applicationDirPath()).arg(mpCoreService->mLSettingService.mDeviceNumber);
        emit signalCommandReadProductHistory(path, mPHisFileName);
        */
    }

    void onSignalReadProductHistory(int error, QString content)
    {
        /*
        if(error != EnumDefine::FileErrorType::FILE_ERROR_NONE)
        {
            qDebug() << "[debug]onSignalReadProductHistory : error";

            reset();
            emit signalEventLoaded();
            return;
        }

        QStringList tempList = content.split("\n");
        tempList.removeLast();

        for(int i = 0; i < tempList.size(); i ++)
        {
            ProductSettingModel * ps = new ProductSettingModel(this);
            ps->setValue(tempList.at(i));
            mListProductHis.append(ps);
            setProductSetting(ps);
        }

        disconnect(this, SIGNAL(signalCommandReadProductHistory(QString, QString)), &mFileLoader, SLOT(onCommandReadAll(QString, QString)));
        disconnect(&mFileLoader, SIGNAL(signalReadAll(int, QString)), this, SLOT(onSignalReadProductHistory(int, QString)));
        connect(this, SIGNAL(signalCommandReadEventHistory(QString, QString, int)), &mFileLoader, SLOT(onCommandReadLine(QString, QString, int)));
        connect(&mFileLoader, SIGNAL(signalReadLine(int, QStringList)), this, SLOT(onSignalReadEventHistory(int, QStringList)));
        connect(&mFileLoader, SIGNAL(signalReadEof()), this, SLOT(onSignalReadEofEventHistory()));

        QString path = QString("%1/database/%2").arg(QApplication::applicationDirPath()).arg(mpCoreService->mLSettingService.mDeviceNumber);

        emit signalCommandReadEventHistory(path, mEHisFileName, 3000);
        */
    }

    void onSignalReadEventHistory(int error, QStringList content)
    {
        /*
        if(error == EnumDefine::FileErrorType::FILE_ERROR_NONE)
        {
            for(int i = 0; i < content.size(); i ++)
            {
                EventItemModel event;
                event.setValue(content.at(i));

                if(EventItemModel::isWeightCheckerEvent(event.mEventType))
                {
                    addEvent(mListProductHis[event.mProductHisIdx]->mSeq, event.mEventType, event.mValue);
                }
            }
        }
        QString path = QString("%1/database/%2").arg(QApplication::applicationDirPath()).arg(mpCoreService->mLSettingService.mDeviceNumber);

        emit signalCommandReadEventHistory(path, mEHisFileName, 3000);
        */
    }

    void onSignalReadEofEventHistory()
    {
        finishedAddEvent();

        emit signalEventLoaded();
    }

public:
    void setProductList(QStringList psList)
    {
        /*
        for(int i = 0; i < psList.size(); i ++)
        {
            PanelWCReportProductModel * pModel = new PanelWCReportProductModel(this);

            if(pModel->setValueFromStrStatistics(psList.at(i)) == false)
            {
                delete pModel;
                continue;
            }

            if(findProductBySeq(pModel->mSeq) == nullptr)
            {
                mListProduct.append(pModel);
            }
        }
        */
    }

    /*
    void setProductSetting(ProductSettingModel * pPs)
    {
        PanelWCReportProductModel * pProduct = nullptr;

        pProduct = findProductBySeq(pPs->mSeq);

        if(pProduct == nullptr)
        {
            return;
        }

        pProduct->mNo                       = pPs->mNo;
        pProduct->mName                     = pPs->mName;
        pProduct->mUnderSettingValue        = pPs->mUnderWeight;
        pProduct->mUnderWarningSettingValue = pPs->mUnderWarningWeight;
        pProduct->mNormalSettingValue       = pPs->mNormalWeight;
        pProduct->mOverSettingValue         = pPs->mOverWeight;
        pProduct->mOverWarningSettingValue  = pPs->mOverWarningWeight;
        pProduct->mTareSettingValue         = pPs->mTareWeight;
    }
    */

    void addEvent(quint64 pseq, QString eventType, int value)
    {
        /*
        PanelWCReportProductModel * pProduct = findProductBySeq(pseq);

        if(pProduct == nullptr)
        {
            qDebug() << "[WeightCheckerModel::addEvent]can not found pseq = " << pseq;
            return;
        }

        pProduct->addEvent(eventType, value);
        */
    }
    PanelWCReportProductModel * findProductBySeq(quint64 seq)
    {
        /*
        for(int i = 0; i < mListProduct.size(); i ++)
        {
            if(mListProduct[i]->mSeq == seq)
                return mListProduct[i];
        }
        return nullptr;
        */
        return nullptr;
    }

    void finishedAddEvent()
    {
        for(int i = 0; i < mListProduct.size(); i ++)
        {
            PanelWCReportProductModel * pMin = mListProduct.at(i);

            for(int j = i; j < mListProduct.size(); j ++)
            {
                 PanelWCReportProductModel * pTemp = mListProduct.at(j);

                 if(pTemp->mNo < pMin->mNo)
                 {
                     mListProduct.replace(j, pMin);
                     pMin = pTemp;
                 }
            }
            pMin->finishedAddEvent();
            mListProduct.replace(i, pMin);
        }
    }

    void reset()
    {
        /*
        foreach(PanelWCReportProductModel * panelModel , mListProduct)
        {
            delete panelModel;
        }
        mListProduct.clear();

        foreach(ProductSettingModel * settingModel , mListProductHis)
        {
            delete settingModel;
        }
        mListProductHis.clear();
        */
    }

    explicit PanelWCReportModel(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[PanelWCReportModel] create instance";

        mListStrWeekOfDayKor.append("월");
        mListStrWeekOfDayKor.append("화");
        mListStrWeekOfDayKor.append("수");
        mListStrWeekOfDayKor.append("목");
        mListStrWeekOfDayKor.append("금");
        mListStrWeekOfDayKor.append("토");
        mListStrWeekOfDayKor.append("일");

        mListStrMonthEng.append("January");
        mListStrMonthEng.append("February");
        mListStrMonthEng.append("March");
        mListStrMonthEng.append("April");
        mListStrMonthEng.append("May");
        mListStrMonthEng.append("June");
        mListStrMonthEng.append("July");
        mListStrMonthEng.append("August");
        mListStrMonthEng.append("September");
        mListStrMonthEng.append("October");
        mListStrMonthEng.append("November");
        mListStrMonthEng.append("December");

        mpCoreService = CoreService::getInstance();
    }

    ~PanelWCReportModel()
    {
        /*
        foreach(PanelWCReportProductModel * product , mListProduct)
        {
            delete product;
        }
        mListProduct.clear();

        foreach(ProductSettingModel * setting , mListProductHis)
        {
            delete setting;
        }
        mListProductHis.clear();
        */
    }
};

#endif // PANELWCREPORTMODEL_H
