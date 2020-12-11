#ifndef REPORTMETALOPMODEL_H
#define REPORTMETALOPMODEL_H

#include <QObject>
#include <QDebug>
#include <QQuickItem>
#include <QtPrintSupport>

#include "source/history/def/datetimeform.h"
#include "source/service/localsettingservice.h"
#include "source/history/dailyhistory.h"

#include "source/qmlmodel/panelmdopreportmodel.h"

class PanelMDOPReportContainerModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool     mIsEditMode       READ getIsEditMode       NOTIFY signalEventChangedIsEditMode      );
    Q_PROPERTY(bool     mIsCheckWrite     READ getIsCheckWrite     NOTIFY signalEventChangedIsCheckWrite    );
    Q_PROPERTY(bool     mIsCheckReview    READ getIsCheckReview    NOTIFY signalEventChangedIsCheckReview   );
    Q_PROPERTY(bool     mIsCheckApproved  READ getIsCheckApproved  NOTIFY signalEventChangedIsCheckApproved );
    Q_PROPERTY(int      mDeviceNum        READ getDeviceNum        NOTIFY signalEventChangedDeviceNum       );
    Q_PROPERTY(QString  mReportTitle      READ getReportTitle      NOTIFY signalEventChangedReportTitle     );
    Q_PROPERTY(QString  mCompany          READ getCompany          NOTIFY signalEventChangedCompany         );
    Q_PROPERTY(QString  mDepartment       READ getDepartment       NOTIFY signalEventChangedDepartment      );
    Q_PROPERTY(QString  mPosition         READ getPosition         NOTIFY signalEventChangedPosition        );
    Q_PROPERTY(QString  mName             READ getName             NOTIFY signalEventChangedName            );

public:
    QPrinter       mPrinter;
    QPainter       *mpPainter = nullptr;

    QDate         mFDate;
    QDate         mTDate;

    QList<PanelMDOPReportModel *> mListDailyReport;

    bool    mIsEditMode         = false;
    bool    mIsCheckWrite       = false;
    bool    mIsCheckReview      = false;
    bool    mIsCheckApproved    = false;
    int     mDeviceNum          = 0;
    QString mReportTitle        = "";
    QString mCompany            = "";
    QString mDepartment         = "";
    QString mPosition           = "";
    QString mName               = "";

    bool    getIsEditMode       (){ return mIsEditMode     ;}
    bool    getIsCheckWrite     (){ return mIsCheckWrite   ;}
    bool    getIsCheckReview    (){ return mIsCheckReview  ;}
    bool    getIsCheckApproved  (){ return mIsCheckApproved;}
    int     getDeviceNum        (){ return mDeviceNum  ; }
    QString getReportTitle      (){ return mReportTitle; }
    QString getCompany          (){ return mCompany    ; }
    QString getDepartment       (){ return mDepartment ; }
    QString getPosition         (){ return mPosition   ; }
    QString getName             (){ return mName       ; }

    void    setIsEditMode       (bool    value){ if(mIsEditMode      == value) return; mIsEditMode      = value; emit signalEventChangedIsEditMode     (mIsEditMode     ); }
    void    setIsCheckWrite     (bool    value){ if(mIsCheckWrite    == value) return; mIsCheckWrite    = value; emit signalEventChangedIsCheckWrite   (mIsCheckWrite   ); }
    void    setIsCheckReview    (bool    value){ if(mIsCheckReview   == value) return; mIsCheckReview   = value; emit signalEventChangedIsCheckReview  (mIsCheckReview  ); }
    void    setIsCheckApproved  (bool    value){ if(mIsCheckApproved == value) return; mIsCheckApproved = value; emit signalEventChangedIsCheckApproved(mIsCheckApproved); }
    void    setDeviceNum        (int     value){ if(mDeviceNum       == value) return; mDeviceNum       = value; emit signalEventChangedDeviceNum      (mDeviceNum      ); }
    void    setReportTitle      (QString value){ if(mReportTitle     == value) return; mReportTitle     = value; emit signalEventChangedReportTitle    (mReportTitle    ); }
    void    setCompany          (QString value){ if(mCompany         == value) return; mCompany         = value; emit signalEventChangedCompany        (mCompany        ); }
    void    setDepartment       (QString value){ if(mDepartment      == value) return; mDepartment      = value; emit signalEventChangedDepartment     (mDepartment     ); }
    void    setPosition         (QString value){ if(mPosition        == value) return; mPosition        = value; emit signalEventChangedPosition       (mPosition       ); }
    void    setName             (QString value){ if(mName            == value) return; mName            = value; emit signalEventChangedName           (mName           ); }

signals:
    void signalEventChangedIsEditMode     (bool    value);
    void signalEventChangedIsCheckWrite   (bool    value);
    void signalEventChangedIsCheckReview  (bool    value);
    void signalEventChangedIsCheckApproved(bool    value);
    void signalEventChangedDeviceNum      (int     value);
    void signalEventChangedReportTitle    (QString value);
    void signalEventChangedCompany        (QString value);
    void signalEventChangedDepartment     (QString value);
    void signalEventChangedPosition       (QString value);
    void signalEventChangedName           (QString value);

    void signalEventCompletedLoad();
    void signalEventSelectedPrint();
    void signalEventSelectedPrintCancle();
    void signalEventPrintNextDate();

    void signalCommandReadFile(QString path, QString fileName);

public slots:
    Q_INVOKABLE void onCommandLoadData(int fYear, int fMonth, int fDay, int tYear, int tMonth, int tDay)
    {
        reset();

        mFDate = QDate(fYear, fMonth, fDay);
        mTDate = QDate(tYear, tMonth, tDay);

        load();
    }

    Q_INVOKABLE int                     onCommandGetDailyListCnt   (       ){ return mListDailyReport.size();                                                               }
    Q_INVOKABLE QString                 onCommandGetDailyListDate  (int idx)
    {
        if(idx >= mListDailyReport.size())
            return ""     ;

        return mListDailyReport[idx]->mDailyHis.mStrDate;
    }
    Q_INVOKABLE PanelMDOPReportModel *  onCommandGetDailyListReport(int idx)
    {
        if(idx >= mListDailyReport.size()) return nullptr; return mListDailyReport[idx];
    }

    Q_INVOKABLE void onCommandRemoveRow(int dailyIdx, int pageIdx, int rowIdxInPage)
    {
        PanelMDOPReportModel * pDailyReport = onCommandGetDailyListReport(dailyIdx);

        if(pDailyReport == nullptr)
            return;

        pDailyReport->onCommandRemoveRow(pageIdx, rowIdxInPage);
    }
    Q_INVOKABLE void onCommandSelectPrint()
    {
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
    }
    Q_INVOKABLE void onCommandPrint(QVariant data)
    {
        QImage img = qvariant_cast<QImage>(data);

        mpPainter->drawImage(QPoint(0,0),img);

        mPrinter.newPage();
    }
    Q_INVOKABLE void onCommandPrintEnd()
    {
        mpPainter->end();
    }

    Q_INVOKABLE void    onCommandSetIsEditMode     (bool value)   { setIsEditMode     (value);}
    Q_INVOKABLE void    onCommandSetIsCheckWrite   (bool value)   { setIsCheckWrite   (value); pLSettingSvc->setSignSetting(mIsCheckWrite, mIsCheckReview, mIsCheckApproved);}
    Q_INVOKABLE void    onCommandSetIsCheckReview  (bool value)   { setIsCheckReview  (value); pLSettingSvc->setSignSetting(mIsCheckWrite, mIsCheckReview, mIsCheckApproved);}
    Q_INVOKABLE void    onCommandSetIsCheckApproved(bool value)   { setIsCheckApproved(value); pLSettingSvc->setSignSetting(mIsCheckWrite, mIsCheckReview, mIsCheckApproved);}
    Q_INVOKABLE void    onCommandSetDeviceNum      (QString value){ setDeviceNum      (value.toInt()); }
    Q_INVOKABLE void    onCommandSetReportTitle    (QString value){ setReportTitle    (value); }
    Q_INVOKABLE void    onCommandSetCompany        (QString value){ setCompany        (value); }
    Q_INVOKABLE void    onCommandSetDepartment     (QString value){ setDepartment     (value); }
    Q_INVOKABLE void    onCommandSetPosition       (QString value){ setPosition       (value); }
    Q_INVOKABLE void    onCommandSetName           (QString value){ setName           (value); }

    void onLoaded()
    {
        load();
    }

    void onPrintPreview(QPrinter * printer)
    {
        /*
        qDebug() << "[debug]onPrintPreview";

        printer->setColorMode(QPrinter::ColorMode::GrayScale);
        printer->setPaperSize(QPrinter::A4);
        printer->setPageMargins(0,0,0,0, QPrinter::Millimeter);
        mpPreviewPrinter = printer;
        if(mpPainter != nullptr){ delete mpPainter; mpPainter = nullptr;}
        mpPainter = new QPainter();
        mpPainter->begin(mpPreviewPrinter);
        double xscale = mpPreviewPrinter->pageRect().width() / double(840);
        double yscale = mpPreviewPrinter->pageRect().height() / double(1188);
        double scale = qMin(xscale, yscale);
        mpPainter->scale(scale, scale);

        emit signalEventSelectedPrint();
        */
    }


    /*
    void onSignalReadedFile(int error, QString content)
    {
        if(error != EnumDefine::FileErrorType::FILE_ERROR_NONE)
        {
            qDebug() << "[PanelMDOPReportContainerModel::onSignalReadedFile]error = " << error;
        }
        else
        {
            PanelMDOPReportModel * pModel = new PanelMDOPReportModel(this);
            pModel->setValue(mAllFileList[0], content);
            mListDailyReport.append(pModel);
        }

        mAllFileList.removeAt(0);

        if(mAllFileList.size() > 0)
        {
            emit signalCommandReadFile(mDirPath, mAllFileList.at(0));
        }
        else
        {
            emit signalEventCompletedLoad();
        }
    }
    */

public:
    explicit PanelMDOPReportContainerModel(QObject *parent = nullptr):QObject(parent)
    {
        QString reportTitle;

        if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_ENG)
        {
            reportTitle = QString("%1 (Metal detector) operate report").arg(pLSettingSvc->mMDSettingModel.mHACCP);
        }
        else if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_KOR)
        {
            reportTitle = QString("%1 (금속검출) 운전 일지").arg(pLSettingSvc->mMDSettingModel.mHACCP);
        }

        setIsCheckWrite   (pLSettingSvc->mSignSettingModel.mIsCheckWrite   );
        setIsCheckReview  (pLSettingSvc->mSignSettingModel.mIsCheckReview  );
        setIsCheckApproved(pLSettingSvc->mSignSettingModel.mIsCheckApproved);

        setDeviceNum  (pLSettingSvc->mDeviceNumber                     );
        setReportTitle(reportTitle                                                       );
        setCompany    (pLSettingSvc->mManagerSettingModel.mCompany     );
        setDepartment (pLSettingSvc->mManagerSettingModel.mMDDepartment);
        setPosition   (pLSettingSvc->mManagerSettingModel.mMDPosition  );
        setName       (pLSettingSvc->mManagerSettingModel.mMDName      );
    }
    ~PanelMDOPReportContainerModel()
    {
        reset();

        if(mpPainter != nullptr)
            delete mpPainter;
    }

private:
    void reset()
    {
        for(int i = 0; i < mListDailyReport.size(); i ++)
        {
            delete mListDailyReport.at(i);
        }

        mListDailyReport.clear();
    }

    void load()
    {
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

        PanelMDOPReportModel * pModel = new PanelMDOPReportModel(this);
        mListDailyReport.append(pModel);

        connect(pModel, SIGNAL(signalEventLoadCompleted()), this, SLOT(onLoaded()));
        pModel->load(pLSettingSvc->mDeviceNumber, mFDate);

        mFDate = mFDate.addDays(1);

    }

    void loadComplete()
    {
        emit signalEventCompletedLoad();
    }
};
#endif // REPORTMETALOPMODEL_H
