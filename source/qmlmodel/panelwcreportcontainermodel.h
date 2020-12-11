#ifndef PANELWCREPORTCONTAINERMODEL_H
#define PANELWCREPORTCONTAINERMODEL_H

#include <QObject>
#include <QDebug>
#include <QQuickItem>
#include <QtPrintSupport>

#include "source/service/coreservice.h"
#include "source/qmlmodel/panelwcreportmodel.h"

class PanelWCReportContainerModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool     mIsEditMode       READ getIsEditMode       NOTIFY signalEventChangedIsEditMode      );
    Q_PROPERTY(bool     mIsCheckWrite     READ getIsCheckWrite     NOTIFY signalEventChangedIsCheckWrite    );
    Q_PROPERTY(bool     mIsCheckReview    READ getIsCheckReview    NOTIFY signalEventChangedIsCheckReview   );
    Q_PROPERTY(bool     mIsCheckApproved  READ getIsCheckApproved  NOTIFY signalEventChangedIsCheckApproved );
    Q_PROPERTY(int      mDeviceNum        READ getDeviceNum        NOTIFY signalEventChangedDeviceNum       );
    Q_PROPERTY(QString  mCompany          READ getCompany          NOTIFY signalEventChangedCompany         );
    Q_PROPERTY(QString  mDepartment       READ getDepartment       NOTIFY signalEventChangedDepartment      );
    Q_PROPERTY(QString  mPosition         READ getPosition         NOTIFY signalEventChangedPosition        );
    Q_PROPERTY(QString  mName             READ getName             NOTIFY signalEventChangedName            );
    Q_PROPERTY(quint64  mSelPSeq          READ getSelPSeq          NOTIFY signalEventChangedSelPSeq         );
    Q_PROPERTY(QString  mSelPNumName      READ getSelPNumName      NOTIFY signalEventChangedSelPNumName     );

public:
    CoreService *  mpCoreService;
    QPrinter       mPrinter;
    QPainter       *mpPainter = nullptr;

    QDate         mFDate;
    QDate         mTDate;

    QList<PanelWCReportModel *> mListDailyReport;

    bool    mIsEditMode         = false;
    bool    mIsCheckWrite       = false;
    bool    mIsCheckReview      = false;
    bool    mIsCheckApproved    = false;
    int     mDeviceNum          = 0;
    QString mCompany            = "";
    QString mDepartment         = "";
    QString mPosition           = "";
    QString mName               = "";
    quint64 mSelPSeq            = 0;
    QString mSelPNumName        = "";


    bool    getIsEditMode       (){ return mIsEditMode     ;}
    bool    getIsCheckWrite     (){ return mIsCheckWrite   ;}
    bool    getIsCheckReview    (){ return mIsCheckReview  ;}
    bool    getIsCheckApproved  (){ return mIsCheckApproved;}
    int     getDeviceNum        (){ return mDeviceNum      ; }
    QString getCompany          (){ return mCompany        ; }
    QString getDepartment       (){ return mDepartment     ; }
    QString getPosition         (){ return mPosition       ; }
    QString getName             (){ return mName           ; }
    quint64 getSelPSeq          (){ return mSelPSeq        ;}
    QString getSelPNumName      (){ return mSelPNumName    ;}


    void    setIsEditMode       (bool    value){ if(mIsEditMode      == value) return; mIsEditMode      = value; emit signalEventChangedIsEditMode     (mIsEditMode     ); }
    void    setIsCheckWrite     (bool    value){ if(mIsCheckWrite    == value) return; mIsCheckWrite    = value; emit signalEventChangedIsCheckWrite   (mIsCheckWrite   ); }
    void    setIsCheckReview    (bool    value){ if(mIsCheckReview   == value) return; mIsCheckReview   = value; emit signalEventChangedIsCheckReview  (mIsCheckReview  ); }
    void    setIsCheckApproved  (bool    value){ if(mIsCheckApproved == value) return; mIsCheckApproved = value; emit signalEventChangedIsCheckApproved(mIsCheckApproved); }
    void    setDeviceNum        (int     value){ if(mDeviceNum       == value) return; mDeviceNum       = value; emit signalEventChangedDeviceNum      (mDeviceNum      ); }
    void    setCompany          (QString value){ if(mCompany         == value) return; mCompany         = value; emit signalEventChangedCompany        (mCompany        ); }
    void    setDepartment       (QString value){ if(mDepartment      == value) return; mDepartment      = value; emit signalEventChangedDepartment     (mDepartment     ); }
    void    setPosition         (QString value){ if(mPosition        == value) return; mPosition        = value; emit signalEventChangedPosition       (mPosition       ); }
    void    setName             (QString value){ if(mName            == value) return; mName            = value; emit signalEventChangedName           (mName           ); }
    void    setSelPSeq          (quint64 value){ if(mSelPSeq         == value) return; mSelPSeq         = value; emit signalEventChangedSelPSeq        (mSelPSeq        ); }
    void    setSelPNumName      (QString value){ if(mSelPNumName     == value) return; mSelPNumName     = value; emit signalEventChangedSelPNumName    (mSelPNumName    ); }
signals:
    void signalEventChangedIsEditMode     (bool    value);
    void signalEventChangedIsCheckWrite   (bool    value);
    void signalEventChangedIsCheckReview  (bool    value);
    void signalEventChangedIsCheckApproved(bool    value);
    void signalEventChangedDeviceNum      (int     value);
    void signalEventChangedCompany        (QString value);
    void signalEventChangedDepartment     (QString value);
    void signalEventChangedPosition       (QString value);
    void signalEventChangedName           (QString value);
    void signalEventChangedSelPSeq        (quint64 value);
    void signalEventChangedSelPNumName    (QString value);

    void signalEventCompleteLoad();

    void signalEventSelectedPrint();
    void signalEventSelectedPrintCancle();


public slots:
    Q_INVOKABLE void onCommandLoadData(int fYear, int fMonth, int fDay, int tYear, int tMonth, int tDay)
    {
        reset();

        mFDate = QDate(fYear, fMonth, fDay);
        mTDate = QDate(tYear, tMonth, tDay);

        load();
/*
        int fDateNumber = fYear * 10000 + fMonth * 100 + fDay;
        int tDateNumber = tYear * 10000 + tMonth * 100 + tDay;

        reset();

        mDirPath = QString("%1/database/%2").arg(QApplication::applicationDirPath()).arg(mpCoreService->mLSettingService.mDeviceNumber);
        QDir dir(mDirPath);
        QStringList allFileList = dir.entryList(QStringList() << "*-EH.txt",QDir::Files,QDir::SortFlag::Name);

        for(int i = 0; i < allFileList.size(); i ++)
        {
            QStringList fileDate = allFileList.at(i).split("-EH.txt")[0].split("-");

            if(fileDate.size() != 3)
                continue;

            int fileDateNumber = fileDate[0].toInt() * 10000 + fileDate[1].toInt() * 100 + fileDate[2].toInt();

            if(fDateNumber <= fileDateNumber && tDateNumber >= fileDateNumber)
            {
                mAllFileList.append(allFileList.at(i));
            }
        }

        qDebug() << "[debug]onCommandLoadData : " << mAllFileList.size();

        if(mAllFileList.size() > 0)
        {
            PanelWCReportModel * pModel = new PanelWCReportModel(this);
            pModel->setFileName(mAllFileList[0]);
            connect(pModel, SIGNAL(signalEventLoaded()), this, SLOT(onSignalEventLoaded()));
            mListDailyReport.append(pModel);
            pModel->load();
        }*/
    }


    Q_INVOKABLE int                     onCommandGetDailyListCnt   (       ){ return mListDailyReport.size();                                                               }
    Q_INVOKABLE QString                 onCommandGetDailyListDate  (int idx)
    {
        if(idx >= mListDailyReport.size())
            return ""     ;

        return QString("%1-%2-%3").arg(mListDailyReport[idx]->mYear).arg(mListDailyReport[idx]->mMonth).arg(mListDailyReport[idx]->mDay);
    }
    Q_INVOKABLE PanelWCReportModel *  onCommandGetDailyListReport(int idx)
    {
        if(idx >= mListDailyReport.size()) return nullptr; return mListDailyReport[idx];
    }

    Q_INVOKABLE void onCommandSelectDay(int idx)
    {
        /*
        qDebug() << "[debug]onCommandSelectDay : " << idx;
        mSelDayReport = nullptr;
        if(idx >= mListDailyReport.size()) return;

        mSelDayReport =  mListDailyReport[idx];

        if(mSelPSeq == 0 && mSelDayReport->mListProduct.size() > 0)
        {
            onCommandSelectProduct(mSelDayReport->mListProduct[0]->mSeq);
        }
        */
    }

    Q_INVOKABLE void onCommandSelectProduct(quint64 seq)
    {
        /*
        qDebug() << "[debug]onCommandSelectProduct : " << seq;

        if(mSelDayReport == nullptr || mSelDayReport->findProductBySeq(seq) == nullptr)
        {
            setSelPSeq(0);
            setSelPNumName("");
            return;
        }

        qDebug() << "[debug]onCommandSelectProduct : " << mSelDayReport->mListProduct[0]->mSeq;
        setSelPSeq(mSelDayReport->mListProduct[0]->mSeq);
        setSelPNumName(mSelDayReport->mListProduct[0]->mNumName);
        */
    }

    Q_INVOKABLE PanelWCReportModel * onCommandGetSelDayModel()
    {
        //return mSelDayReport;
        return nullptr;
    }

    Q_INVOKABLE int onCommandGetProductCnt()
    {/*
        if(mSelDayReport == nullptr)
            return 0;

        return mSelDayReport->mListProduct.size();
        */
        return 0;
    }

    Q_INVOKABLE int onCommandGetPSeq(int idx)
    {
        /*
        if(mSelDayReport == nullptr)
            return 0;

        return mSelDayReport->mListProduct[idx]->mSeq;
        */
        return 0;
    }
    Q_INVOKABLE QString onCommandGetPNum(int idx)
    {
        /*
        if(mSelDayReport == nullptr)
            return "";

        return mSelDayReport->mListProduct[idx]->mNumName;
        */
        return "";
    }

    Q_INVOKABLE void onCommandSelectPrint()
    {
        /*
        QPrintDialog dlg(&mPrinter,0);

        if(dlg.exec() == QDialog::Accepted)
        {
            if(mpPainter != nullptr){ delete mpPainter; mpPainter = nullptr;}
            mPrinter.setColorMode(QPrinter::ColorMode::GrayScale);
            mPrinter.setPaperSize(QPrinter::A4);
            mPrinter.setPageMargins(0,0,0,0, QPrinter::Millimeter);

            mpPainter = new QPainter();
            mpPainter->begin(&mPrinter);
            double xscale = mPrinter.pageRect().width() / double(840);
            double yscale = mPrinter.pageRect().height() / double(1188);
            double scale = qMin(xscale, yscale);
            mpPainter->scale(scale, scale);

            emit signalEventSelectedPrint();
        }
        else
        {
            emit signalEventSelectedPrintCancle();
        }
        */
    }
    Q_INVOKABLE void onCommandPrint(QVariant data)
    {
        /*
        QImage img = qvariant_cast<QImage>(data);

        mpPainter->drawImage(QPoint(0,0),img);

        mPrinter.newPage();
        */
    }
    Q_INVOKABLE void onCommandPrintEnd()
    {
        //mpPainter->end();
    }

    Q_INVOKABLE void    onCommandSetIsEditMode     (bool value)   { }//setIsEditMode     (value);}
    Q_INVOKABLE void    onCommandSetIsCheckWrite   (bool value)   { }//setIsCheckWrite   (value); mpCoreService->mLSettingService.setSignSetting(mIsCheckWrite, mIsCheckReview, mIsCheckApproved);}
    Q_INVOKABLE void    onCommandSetIsCheckReview  (bool value)   { }//setIsCheckReview  (value); mpCoreService->mLSettingService.setSignSetting(mIsCheckWrite, mIsCheckReview, mIsCheckApproved);}
    Q_INVOKABLE void    onCommandSetIsCheckApproved(bool value)   { }//setIsCheckApproved(value); mpCoreService->mLSettingService.setSignSetting(mIsCheckWrite, mIsCheckReview, mIsCheckApproved);}
    Q_INVOKABLE void    onCommandSetDeviceNum      (QString value){ }//setDeviceNum      (value.toInt()); }
    Q_INVOKABLE void    onCommandSetCompany        (QString value){ }//setCompany        (value); }
    Q_INVOKABLE void    onCommandSetDepartment     (QString value){ }//setDepartment     (value); }
    Q_INVOKABLE void    onCommandSetPosition       (QString value){ }//setPosition       (value); }
    Q_INVOKABLE void    onCommandSetName           (QString value){ }//setName           (value); }

    void onLoaded(){

        load();
    }

public:
    explicit PanelWCReportContainerModel(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[PanelWCReportContainerModel] create instance";
/*
        mpCoreService = CoreService::getInstance();

        setIsCheckWrite   (mpCoreService->mLSettingService.mSignSettingModel.mIsCheckWrite   );
        setIsCheckReview  (mpCoreService->mLSettingService.mSignSettingModel.mIsCheckReview  );
        setIsCheckApproved(mpCoreService->mLSettingService.mSignSettingModel.mIsCheckApproved);
        setDeviceNum      (mpCoreService->mLSettingService.mDeviceNumber                     );
        setCompany        (mpCoreService->mLSettingService.mManagerSettingModel.mCompany     );
        setDepartment     (mpCoreService->mLSettingService.mManagerSettingModel.mWCDepartment);
        setPosition       (mpCoreService->mLSettingService.mManagerSettingModel.mWCPosition  );
        setName           (mpCoreService->mLSettingService.mManagerSettingModel.mWCName      );*/
    }
    ~PanelWCReportContainerModel()
    {
        /*
        reset();

        if(mpPainter != nullptr)
            delete mpPainter;*/
    }

private:
    void reset()
    {
        /*
        for(int i = 0; i < mListDailyReport.size(); i ++)
        {
            delete mListDailyReport.at(i);
        }

        mListDailyReport.clear();
        */
    }

    void load()
    {
        /*
        if(mFDate > mTDate)
        {
            loadComplete();
            return;
        }

        while(QFile::exists(QString("%1/%2/%3-EH.txt").arg(FileDef::DATABASE_DIR()).arg(pLSettingSvc->mDeviceNumber).arg(mFDate.toString(DATE_FILE_NAME_FMT))) == false)
        {
            mFDate = mFDate.addDays(1);

            if(mFDate > mTDate)
            {
                loadComplete();
                return;
            }
        }

        PanelWCReportModel * pModel = new PanelWCReportModel(this);
        mListDailyReport.append(pModel);

        connect(pModel, SIGNAL(signalEventLoadCompleted()), this, SLOT(onLoaded()));
        pModel->load(pLSettingSvc->mDeviceNumber, mFDate);
        */
    }

    void loadComplete()
    {
        emit signalEventCompleteLoad();
    }
};

#endif // PANELWCREPORTCONTAINERMODEL_H
