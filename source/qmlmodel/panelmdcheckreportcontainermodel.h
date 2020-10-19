#ifndef PANELMDCHECKREPORTCONTAINERMODEL_H
#define PANELMDCHECKREPORTCONTAINERMODEL_H

#include <QObject>
#include <QDebug>
#include <QQuickItem>
#include <QtPrintSupport>

#include "source/service/coreservice.h"
#include "source/qmlmodel/panelmdcheckreportmodel.h"

class PanelMDCheckReportContainerModel : public QObject
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
    Q_PROPERTY(QString  mCheckupCycle     READ getCheckupCycle     NOTIFY signalEventChangedCheckupCycle    );

public:
    CoreService *  mpCoreService;
    QPrinter       mPrinter;
    QPainter       *mpPainter = nullptr;
    FileLoaderThread   mFileLoader;
    QString mDirPath;
    QStringList mAllFileList;
    QList<PanelMDCheckReportModel *> mListDailyReport;

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
    QString mCheckupCycle       = "";

    bool    getIsEditMode       (){ return mIsEditMode     ;}
    bool    getIsCheckWrite     (){ return mIsCheckWrite   ;}
    bool    getIsCheckReview    (){ return mIsCheckReview  ;}
    bool    getIsCheckApproved  (){ return mIsCheckApproved;}
    int     getDeviceNum        (){ return mDeviceNum      ; }
    QString getReportTitle      (){ return mReportTitle    ; }
    QString getCompany          (){ return mCompany        ; }
    QString getDepartment       (){ return mDepartment     ; }
    QString getPosition         (){ return mPosition       ; }
    QString getName             (){ return mName           ; }
    QString getCheckupCycle     (){ return mCheckupCycle   ; }

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
    void    setCheckupCycle     (QString value){ if(mCheckupCycle    == value) return; mCheckupCycle    = value; emit signalEventChangedCheckupCycle   (mCheckupCycle   ); }

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
    void signalEventChangedCheckupCycle   (QString value);

    void signalEventCompletedLoad();
    void signalEventSelectedPrint();
    void signalEventSelectedPrintCancle();
    void signalEventPrintNextDate();

    void signalCommandReadFile(QString path, QString fileName, int lineCnt);

public slots:
    Q_INVOKABLE void onCommandLoadData(int fYear, int fMonth, int fDay, int tYear, int tMonth, int tDay)
    {
        int fDateNumber = fYear * 10000 + fMonth * 100 + fDay;
        int tDateNumber = tYear * 10000 + tMonth * 100 + tDay;

        reset();

        mDirPath = QString("%1/database/%2").arg(QApplication::applicationDirPath()).arg(mpCoreService->mLSettingService.mDeviceNumber);
        QDir dir(mDirPath);
        QStringList allFileList = dir.entryList(QStringList() << "*-CH.txt",QDir::Files,QDir::SortFlag::Name);

        for(int i = 0; i < allFileList.size(); i ++)
        {
            QStringList fileDate = allFileList.at(i).split("-CH.txt")[0].split("-");

            if(fileDate.size() != 3)
                continue;

            int fileDateNumber = fileDate[0].toInt() * 10000 + fileDate[1].toInt() * 100 + fileDate[2].toInt();

            if(fDateNumber <= fileDateNumber && tDateNumber >= fileDateNumber)
            {
                mAllFileList.append(allFileList.at(i));
            }
        }

        if(mAllFileList.size() > 0)
        {
            PanelMDCheckReportModel * pModel = new PanelMDCheckReportModel(this);
            pModel->setDateByFileName(mAllFileList.at(0));
            mListDailyReport.append(pModel);
            emit signalCommandReadFile(mDirPath, mAllFileList.at(0), 3000);
        }
        else
        {
            emit signalEventCompletedLoad();
        }
    }

    Q_INVOKABLE int                     onCommandGetDailyListCnt   (       ){ return mListDailyReport.size();                                                               }
    Q_INVOKABLE QString                 onCommandGetDailyListDate  (int idx)
    {
        if(idx >= mListDailyReport.size())
            return ""     ;

        return QString("%1-%2-%3").arg(mListDailyReport[idx]->mYear).arg(mListDailyReport[idx]->mMonth).arg(mListDailyReport[idx]->mDay);
    }
    Q_INVOKABLE PanelMDCheckReportModel *  onCommandGetDailyListReport(int idx)
    {
        if(idx >= mListDailyReport.size()) return nullptr; return mListDailyReport[idx];
    }

    Q_INVOKABLE void onCommandRemoveRow(int dailyIdx, int pageIdx, int rowIdxInPage)
    {
        PanelMDCheckReportModel * pDailyReport = onCommandGetDailyListReport(dailyIdx);

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
    Q_INVOKABLE void    onCommandSetIsCheckWrite   (bool value)   { setIsCheckWrite   (value); mpCoreService->mLSettingService.setSignSetting(mIsCheckWrite, mIsCheckReview, mIsCheckApproved);}
    Q_INVOKABLE void    onCommandSetIsCheckReview  (bool value)   { setIsCheckReview  (value); mpCoreService->mLSettingService.setSignSetting(mIsCheckWrite, mIsCheckReview, mIsCheckApproved);}
    Q_INVOKABLE void    onCommandSetIsCheckApproved(bool value)   { setIsCheckApproved(value); mpCoreService->mLSettingService.setSignSetting(mIsCheckWrite, mIsCheckReview, mIsCheckApproved);}
    Q_INVOKABLE void    onCommandSetDeviceNum      (QString value){ setDeviceNum      (value.toInt()); }
    Q_INVOKABLE void    onCommandSetReportTitle    (QString value){ setReportTitle    (value); }
    Q_INVOKABLE void    onCommandSetCompany        (QString value){ setCompany        (value); }
    Q_INVOKABLE void    onCommandSetDepartment     (QString value){ setDepartment     (value); }
    Q_INVOKABLE void    onCommandSetPosition       (QString value){ setPosition       (value); }
    Q_INVOKABLE void    onCommandSetName           (QString value){ setName           (value); }
    Q_INVOKABLE void    onCommandSetCheckupCycle   (QString value){ setCheckupCycle   (value); }

    void onSignalReadLine(int error, QStringList lines)
    {
        if(error != EnumDefine::FileErrorType::FILE_ERROR_NONE)
        {
            qDebug() << "[PanelMDCheckReportContainerModel::onSignalReadedFile]error = " << error;
            return;
        }

        for(int i = 0; i < lines.size(); i ++)
        {
            mListDailyReport[mListDailyReport.size() - 1]->addRowValue(lines.at(i));
        }

        emit signalCommandReadFile(mDirPath, mAllFileList.at(0), 3000);
    }

    void onSignalReadEof()
    {
        mAllFileList.removeAt(0);

        if(mAllFileList.size() > 0)
        {
            PanelMDCheckReportModel * pModel = new PanelMDCheckReportModel(this);
            pModel->setDateByFileName(mAllFileList.at(0));
            mListDailyReport.append(pModel);
            emit signalCommandReadFile(mDirPath, mAllFileList.at(0), 3000);
        }
        else
        {
            emit signalEventCompletedLoad();
        }
    }

public:
    explicit PanelMDCheckReportContainerModel(QObject *parent = nullptr):QObject(parent)
    {
        QString reportTitle;

        mpCoreService = CoreService::getInstance();

        if(mpCoreService->mLSettingService.mLanguage == EnumDefine::Language::LANG_ENG)
        {
            reportTitle = QString("%1 (Metal detector) checkup report").arg(mpCoreService->mLSettingService.mMDSettingModel.mHACCP);
        }
        else if(mpCoreService->mLSettingService.mLanguage == EnumDefine::Language::LANG_KOR)
        {
            reportTitle = QString("%1 (금속검출) 점검 일지").arg(mpCoreService->mLSettingService.mMDSettingModel.mHACCP);
        }

        setIsCheckWrite   (mpCoreService->mLSettingService.mSignSettingModel.mIsCheckWrite   );
        setIsCheckReview  (mpCoreService->mLSettingService.mSignSettingModel.mIsCheckReview  );
        setIsCheckApproved(mpCoreService->mLSettingService.mSignSettingModel.mIsCheckApproved);
        setDeviceNum      (mpCoreService->mLSettingService.mDeviceNumber                     );
        setReportTitle    (reportTitle                                                       );
        setCompany        (mpCoreService->mLSettingService.mManagerSettingModel.mCompany     );
        setDepartment     (mpCoreService->mLSettingService.mManagerSettingModel.mDepartment  );
        setPosition       (mpCoreService->mLSettingService.mManagerSettingModel.mPosition    );
        setName           (mpCoreService->mLSettingService.mManagerSettingModel.mName        );
        setCheckupCycle   (mpCoreService->mLSettingService.mMDSettingModel.mCheckupCycle     );

        connect(this, SIGNAL(signalCommandReadFile(QString, QString, int)), &mFileLoader, SLOT(onCommandReadLine(QString, QString, int)));

        connect(&mFileLoader, SIGNAL(signalReadLine(int, QStringList)), this, SLOT(onSignalReadLine(int, QStringList)));
        connect(&mFileLoader, SIGNAL(signalReadEof (                )), this, SLOT(onSignalReadEof (                )));
    }
    ~PanelMDCheckReportContainerModel()
    {
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
        mAllFileList.clear();
    }
};
#endif // PANELMDCHECKREPORTCONTAINERMODEL_H
