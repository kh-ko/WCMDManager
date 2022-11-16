#ifndef PANELREPORTCONTAINERMODEL_H
#define PANELREPORTCONTAINERMODEL_H

#include <QObject>
#include <QDebug>
#include <QQuickItem>
#include <QtPrintSupport>

#include "source/globaldef/EnumDefine.h"
#include "source/history/def/datetimeform.h"
#include "source/service/localsettingservice.h"
#include "source/history/dailyhistory.h"
#include "source/service/dataloaderservice.h"

#include "source/qmlmodel/report/reportpagemodel.h"

class PanelReportWindowModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool     mIsCheckWrite     READ getIsCheckWrite     NOTIFY signalEventChangedIsCheckWrite    );
    Q_PROPERTY(bool     mIsCheckReview    READ getIsCheckReview    NOTIFY signalEventChangedIsCheckReview   );
    Q_PROPERTY(bool     mIsCheckApproved  READ getIsCheckApproved  NOTIFY signalEventChangedIsCheckApproved );

public:
    QString        mStrOver;
    QString        mStrUnder;
    QString        mStrEtc;
    QString        mStrStaticCalib;
    QString        mStrDynamicCalib;
    QString        mStrMetalDetect;

    QPrinter       mPrinter;
    QPainter       *mpPainter = nullptr;

    QDate          mFDate;
    QDate          mTDate;
    QDate          mLoadingDate;
    DailyHistory   mDailyHis;

    DevInfoDto     mDevInfo;
    EnumDefine::ReportType     mReportType;
    QList<int>     mSelectedPSeqList;

    bool    mIsCheckWrite       = false;
    bool    mIsCheckReview      = false;
    bool    mIsCheckApproved    = false;

    bool getIsCheckWrite   (){ return mIsCheckWrite   ;}
    bool getIsCheckReview  (){ return mIsCheckReview  ;}
    bool getIsCheckApproved(){ return mIsCheckApproved;}

    void setIsCheckWrite   (bool isOn){ if(isOn == mIsCheckWrite   )return; mIsCheckWrite    = isOn; emit signalEventChangedIsCheckWrite   (isOn);}
    void setIsCheckReview  (bool isOn){ if(isOn == mIsCheckReview  )return; mIsCheckReview   = isOn; emit signalEventChangedIsCheckReview  (isOn);}
    void setIsCheckApproved(bool isOn){ if(isOn == mIsCheckApproved)return; mIsCheckApproved = isOn; emit signalEventChangedIsCheckApproved(isOn);}

signals:
    void signalEventChangedIsCheckWrite   (bool isOn);
    void signalEventChangedIsCheckReview  (bool isOn);
    void signalEventChangedIsCheckApproved(bool isOn);
    void signalEventLoadedPage(ReportPageModel *pageModel);
    void signalEventAddedDate(QString date);
    void signalEventCompletedLoad();

    void signalEventSelectedPrint();

public slots:
    Q_INVOKABLE void onCommandSetIsCheckWrite   (bool isOn){ setIsCheckWrite   (isOn); }
    Q_INVOKABLE void onCommandSetIsCheckReview  (bool isOn){ setIsCheckReview  (isOn); }
    Q_INVOKABLE void onCommandSetIsCheckApproved(bool isOn){ setIsCheckApproved(isOn); }
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

    Q_INVOKABLE void onCommandLoadData(int reportType, int fYear, int fMonth, int fDay, int tYear, int tMonth, int tDay, QString selectedPSeqList)
    {
        mReportType = (EnumDefine::ReportType)reportType;
        mLoadingDate = QDate(fYear, fMonth, fDay);
        mTDate = QDate(tYear, tMonth, tDay);

        QStringList tempPSeqList = selectedPSeqList.split(",");

        foreach(QString pseq, tempPSeqList)
        {
            if(pseq.length() > 0)
            {
                mSelectedPSeqList.append(pseq.toInt());
            }
        }
        load();
    }

    void onLoaded(int err)
    {
        int pageNum = 1;
        ReportPageModel * pPage = nullptr;
        switch(mReportType)
        {
        case EnumDefine::REPORT_MD_CHECKUP:
            if(getCountMDCheckupEventSelectedProduct() == 0 && getCountMDFailEventSelectedProduct() == 0)
                break;
//            if(mDailyHis.mEH.mCheckupEventList.size() == 0 && mDailyHis.mEH.mMDFailList.size() == 0)
//                break;

            emit signalEventAddedDate(mDailyHis.mEH.mStrDate);

            pPage = buildPageModel(true, mDailyHis.mEH.mStrDate, EnumDefine::REPORT_PAGE_MD_CHECKUP, pageNum++);

            foreach(PDCheckupDto checkup, mDailyHis.mEH.mCheckupEventList)
            {
                if(isSelectedProduct(checkup.mProductSeq) == false)
                    continue;

                if(pPage->isFull())
                {
                    emit signalEventLoadedPage(pPage);
                    pPage= buildPageModel(false, mDailyHis.mEH.mStrDate, EnumDefine::REPORT_PAGE_MD_CHECKUP, pageNum++);
                }
                QStringList row;
                row.append(QString::number(checkup.mProductNo).rightJustified(3,'0'));
                row.append(checkup.mTime.toString(TIME_FMT));
                row.append(checkup.mProductName);
                row.append(mDevInfo.getLimFe(checkup.mProductSeq));
                row.append(mDevInfo.getLimSus(checkup.mProductSeq));
                row.append(checkup.mIsPassFe01  == true ? "O" : "X");
                row.append(checkup.mIsPassFe02  == true ? "O" : "X");
                row.append(checkup.mIsPassFe03  == true ? "O" : "X");
                row.append(checkup.mIsPassSus01 == true ? "O" : "X");
                row.append(checkup.mIsPassSus02 == true ? "O" : "X");
                row.append(checkup.mIsPassSus03 == true ? "O" : "X");
                row.append("");
                pPage->addRow(row);
            }
            emit signalEventLoadedPage(pPage);

            pPage = buildPageModel(true, mDailyHis.mEH.mStrDate, EnumDefine::REPORT_PAGE_MD_DETECT, pageNum++);

            foreach(EventDto detect, mDailyHis.mEH.mMDFailList)
            {
                if(isSelectedProduct(detect.mPDSeq) == false)
                    continue;

                if(pPage->isFull())
                {
                    emit signalEventLoadedPage(pPage);
                    pPage = buildPageModel(false, mDailyHis.mEH.mStrDate, EnumDefine::REPORT_PAGE_MD_DETECT, pageNum++);
                }
                QStringList row;
                PDSettingDto setting = mDailyHis.mEH.findSettingDto(detect.mPDSeq, detect.mPDHisIdx);
                row.append(QString::number(setting.mProductNum).rightJustified(3,'0'));
                row.append(detect.mDateTime.toString(TIME_FMT));
                row.append(setting.mName);
                row.append("");
                row.append("");
                row.append("");
                row.append("");

                pPage->addRow(row);
            }
            emit signalEventLoadedPage(pPage);

            break;

        case EnumDefine::REPORT_MD_OPERATE:
            if(getCountMDPSSelectedProduct() == 0)
                break;
//            if(mDailyHis.mPS.mPSList.size() == 0)
//                break;

            emit signalEventAddedDate(mDailyHis.mEH.mStrDate);

            pPage = buildPageModel(true, mDailyHis.mEH.mStrDate, EnumDefine::REPORT_PAGE_MD_OP, pageNum++);

            foreach(PDStatsDto stats, mDailyHis.mPS.mPSList)
            {
                if(isSelectedProduct(stats.mSeq) == false)
                    continue;

                if(pPage->isFull())
                {
                    emit signalEventLoadedPage(pPage);
                    pPage= buildPageModel(false, mDailyHis.mEH.mStrDate, EnumDefine::REPORT_PAGE_MD_OP, pageNum++);
                }

                if(stats.mMDTotalCnt < 1)
                    continue;

                QStringList row;
                row.append(QString::number(stats.mNum).rightJustified(3,'0'));
                row.append(stats.mName);
                row.append(mDevInfo.getLimFe(stats.mSeq));
                row.append(mDevInfo.getLimSus(stats.mSeq));
                row.append(QString("%L1").arg(stats.mMDTotalCnt));
                row.append(QString("%L1").arg(stats.mMDFailCnt));

                if(stats.mMDTotalCnt == 0)
                {
                    row.append("0.00");
                }
                else
                {
                    float fValue = ((float)stats.mMDFailCnt/stats.mMDTotalCnt) * 100.0;
                    row.append(QString("%L1").arg(fValue, 0, 'f', 2));
                }
                pPage->addRow(row);
            }
            emit signalEventLoadedPage(pPage);
            break;

        case EnumDefine::REPORT_WC_OPERATE:
            if(getCountWCPSSelectedProduct() == 0 && getCountWCEventSelectedProduct() == 0)
                break;
//            if(mDailyHis.mPS.mPSList.size() == 0)
//                break;

            emit signalEventAddedDate(mDailyHis.mEH.mStrDate);

            pPage = buildPageModel(true, mDailyHis.mEH.mStrDate, EnumDefine::REPORT_PAGE_WC_OP, pageNum++);

            foreach(PDWCStatsDto stats, mDailyHis.mEH.mPDWCStatsList)
            {
                if(isSelectedProduct(stats.mSeq) == false)
                    continue;

                if(pPage->isFull())
                {
                    emit signalEventLoadedPage(pPage);
                    pPage= buildPageModel(false, mDailyHis.mEH.mStrDate, EnumDefine::REPORT_PAGE_WC_OP, pageNum++);
                }
                QStringList row;
                PDSettingDto setting = mDailyHis.mEH.findSettingDto(stats.mSeq, 0);
                row.append(QString::number(setting.mProductNum).rightJustified(3,'0'));
                row.append(setting.mName);
                row.append(QString("%L1").arg(stats.mWCOCnt));
                row.append(QString("%L1").arg(stats.mWCUCnt));
                row.append(QString("%L1").arg((stats.mWCEtcCnt + stats.mWCMDCnt)));
                row.append(QString("%L1").arg(stats.mWCTotalCnt));

                if(stats.mWCTotalCnt == 0)
                {
                    row.append("0.00");
                }
                else
                {
                    float fValue = ((float)(stats.mWCOCnt + stats.mWCUCnt + stats.mWCEtcCnt + stats.mWCMDCnt)/(float)stats.mWCTotalCnt) * 100.0;
                    row.append(QString("%L1").arg(fValue, 0, 'f', 2));
                }
                pPage->addRow(row);
            }
            emit signalEventLoadedPage(pPage);

            pPage = buildPageModel(true, mDailyHis.mEH.mStrDate, EnumDefine::REPORT_PAGE_WC_DETECT, pageNum++);

            foreach(EventDto detect, mDailyHis.mEH.mWCEventList)
            {
                if(isSelectedProduct(detect.mPDSeq) == false)
                    continue;

                if(!detect.isNGEvent() && !detect.isCalibEvent())
                    continue;

                if(pPage->isFull())
                {
                    emit signalEventLoadedPage(pPage);
                    pPage = buildPageModel(false, mDailyHis.mEH.mStrDate, EnumDefine::REPORT_PAGE_WC_DETECT, pageNum++);
                }

                QStringList row;
                PDSettingDto setting = mDailyHis.mEH.findSettingDto(detect.mPDSeq, detect.mPDHisIdx);
                row.append(QString::number(setting.mProductNum).rightJustified(3,'0'));
                row.append(detect.mDateTime.toString(TIME_FMT));
                row.append(setting.mName);

                if(detect.mEType == EnumDef::ET_WEIGHT_OVER)
                    row.append(QString("%1g (%2)").arg(QString::number(((double)detect.mEValue/1000.0), 'f', 1)).arg(mStrOver));
                else if(detect.mEType == EnumDef::ET_WEIGHT_UNDER)
                    row.append(QString("%1g (%2)").arg(QString::number(((double)detect.mEValue/1000.0), 'f', 1)).arg(mStrUnder));//row.append(mStrUnder);
                else if(detect.mEType == EnumDef::ET_WEIGHT_ETCERROR)
                    row.append(QString("%1g (%2)").arg(QString::number(((double)detect.mEValue/1000.0), 'f', 1)).arg(mStrEtc));//row.append(mStrEtc);
                else if(detect.mEType == EnumDef::ET_WEIGHT_ETC_METAL_ERROR)
                    row.append(QString("%1").arg(mStrMetalDetect));
                else if(detect.mEType == EnumDef::ET_WEIGHT_STATIC_CARI)
                    row.append(QString("%1").arg(mStrStaticCalib));
                else if(detect.mEType == EnumDef::ET_WEIGHT_DYNAMIC_CARI)
                    row.append(QString("%1").arg(mStrDynamicCalib));

                row.append("");
                row.append("");
                row.append("");

                pPage->addRow(row);
            }
            emit signalEventLoadedPage(pPage);

            break;
        }

        mDailyHis.clear();
        mLoadingDate = mLoadingDate.addDays(1);
        load();
    }

public:
    explicit PanelReportWindowModel(QObject *parent = nullptr):QObject(parent)
    {
        if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_KOR){
            mStrOver = "초과"; mStrUnder = "미달"; mStrEtc = "기타"; mStrStaticCalib = "정보정"; mStrDynamicCalib = "동보정"; mStrMetalDetect = "금속검출";
        }
        else
        {
            mStrOver = "Over"; mStrUnder = "Under"; mStrEtc = "Etc"; mStrStaticCalib = "Static calibration"; mStrDynamicCalib = "Dynamic calibration"; mStrMetalDetect = "Metal detect";
        }

        mDevInfo = pDevInfoSvc->findDevInfo(pDLoaderSvc->mDevNum);

        setIsCheckWrite(pLSettingSvc->mSignSettingModel.getIsCheckWrite());
        setIsCheckReview(pLSettingSvc->mSignSettingModel.getIsCheckReview());
        setIsCheckApproved(pLSettingSvc->mSignSettingModel.getIsCheckApproved());

        connect(&mDailyHis, SIGNAL(signalEventLoadCompleted(int)), this, SLOT(onLoaded(int)));
    }
    ~PanelReportWindowModel()
    {
        if(mpPainter != nullptr)
            delete mpPainter;
    }

private:
    void load()
    {
        if(mLoadingDate > mTDate)
        {
            loadComplete();
            return;
        }

        qDebug() << "load report : " << mLoadingDate.toString(DATE_FILE_NAME_FMT);

        mDailyHis.load(pLSettingSvc->mDeviceNumber, QString("%1/%2").arg(FileDef::DATABASE_DIR()).arg(pLSettingSvc->mDeviceNumber), mLoadingDate.toString(DATE_FILE_NAME_FMT));
    }

    void loadComplete()
    {
        emit signalEventCompletedLoad();
    }

    ReportPageModel * buildPageModel(bool bFirstPage, QString reportDate, EnumDefine::ReportPageType pageType, int pageNum)
    {
       QString reportTitle;
       ReportPageModel * pPage = nullptr;

       pPage = new ReportPageModel(this);

       if(pageType == EnumDefine::REPORT_PAGE_MD_CHECKUP)
       {
            if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_ENG)
            {
                reportTitle = QString("%1 (Metal detector) checkup report").arg(pLSettingSvc->mMDSettingModel.mHACCP);
            }
            else if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_KOR)
            {
                reportTitle = QString("%1 (금속검출) 점검 일지").arg(pLSettingSvc->mMDSettingModel.mHACCP);
            }
            pPage->setHeader(reportDate, pageType, bFirstPage, pageNum,
                             reportTitle,
                             pLSettingSvc->mSignSettingModel.mIsCheckWrite,
                             pLSettingSvc->mSignSettingModel.mIsCheckReview,
                             pLSettingSvc->mSignSettingModel.mIsCheckApproved,
                             pLSettingSvc->mManagerSettingModel.mCompany,
                             mLoadingDate,
                             pLSettingSvc->mMDSettingModel.mCheckupCycle,
                             pLSettingSvc->mDeviceNumber,
                             pLSettingSvc->mManagerSettingModel.mMDDepartment,
                             pLSettingSvc->mManagerSettingModel.mMDPosition,
                             pLSettingSvc->mManagerSettingModel.mMDName);
            if(bFirstPage)
                pPage->setMetrix(10, 12);
            else
                pPage->setMetrix(17, 12);
       }
       else if(pageType == EnumDefine::REPORT_PAGE_MD_OP)
       {
           if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_ENG)
           {
               reportTitle = QString("%1 (Metal detector) operate report").arg(pLSettingSvc->mMDSettingModel.mHACCP);
           }
           else if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_KOR)
           {
               reportTitle = QString("%1 (금속검출) 운전 일지").arg(pLSettingSvc->mMDSettingModel.mHACCP);
           }

           pPage->setHeader(reportDate, pageType, bFirstPage, pageNum,
                            reportTitle,
                            pLSettingSvc->mSignSettingModel.mIsCheckWrite,
                            pLSettingSvc->mSignSettingModel.mIsCheckReview,
                            pLSettingSvc->mSignSettingModel.mIsCheckApproved,
                            pLSettingSvc->mManagerSettingModel.mCompany,
                            mLoadingDate,
                            pLSettingSvc->mMDSettingModel.mCheckupCycle,
                            pLSettingSvc->mDeviceNumber,
                            pLSettingSvc->mManagerSettingModel.mMDDepartment,
                            pLSettingSvc->mManagerSettingModel.mMDPosition,
                            pLSettingSvc->mManagerSettingModel.mMDName);

           if(bFirstPage)
               pPage->setMetrix(10, 8);
           else
               pPage->setMetrix(17, 8);
       }
       else if(pageType == EnumDefine::REPORT_PAGE_MD_DETECT)
       {
           if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_ENG)
           {
               reportTitle = QString("%1 (Metal detector) monitoring report").arg(pLSettingSvc->mMDSettingModel.mHACCP);
           }
           else if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_KOR)
           {
               reportTitle = QString("%1 (금속검출) 모니터링 일지").arg(pLSettingSvc->mMDSettingModel.mHACCP);
           }
           pPage->setHeader(reportDate, pageType, bFirstPage, pageNum,
                            reportTitle,
                            pLSettingSvc->mSignSettingModel.mIsCheckWrite,
                            pLSettingSvc->mSignSettingModel.mIsCheckReview,
                            pLSettingSvc->mSignSettingModel.mIsCheckApproved,
                            pLSettingSvc->mManagerSettingModel.mCompany,
                            mLoadingDate,
                            pLSettingSvc->mMDSettingModel.mCheckupCycle,
                            pLSettingSvc->mDeviceNumber,
                            pLSettingSvc->mManagerSettingModel.mMDDepartment,
                            pLSettingSvc->mManagerSettingModel.mMDPosition,
                            pLSettingSvc->mManagerSettingModel.mMDName);

           if(bFirstPage)
               pPage->setMetrix(11, 7);
           else
               pPage->setMetrix(18, 7);
       }
       else if(pageType == EnumDefine::REPORT_PAGE_WC_OP)
       {
           if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_ENG)
           {
               reportTitle = QString("Weight checker operate report");
           }
           else if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_KOR)
           {
               reportTitle = QString("중량선별기 운전 일지");
           }

           pPage->setHeader(reportDate, pageType, bFirstPage, pageNum,
                            reportTitle,
                            pLSettingSvc->mSignSettingModel.mIsCheckWrite,
                            pLSettingSvc->mSignSettingModel.mIsCheckReview,
                            pLSettingSvc->mSignSettingModel.mIsCheckApproved,
                            pLSettingSvc->mManagerSettingModel.mCompany,
                            mLoadingDate,
                            pLSettingSvc->mMDSettingModel.mCheckupCycle,
                            pLSettingSvc->mDeviceNumber,
                            pLSettingSvc->mManagerSettingModel.mWCDepartment,
                            pLSettingSvc->mManagerSettingModel.mWCPosition,
                            pLSettingSvc->mManagerSettingModel.mWCName);

           if(bFirstPage)
               pPage->setMetrix(11, 8);
           else
               pPage->setMetrix(18, 8);
       }
       else if(pageType == EnumDefine::REPORT_PAGE_WC_DETECT)
       {
           if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_ENG)
           {
               reportTitle = QString("Weight checker monitoring report");
           }
           else if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_KOR)
           {
               reportTitle = QString("중량선별기 모니터링 일지");
           }
           pPage->setHeader(reportDate, pageType, bFirstPage, pageNum,
                            reportTitle,
                            pLSettingSvc->mSignSettingModel.mIsCheckWrite,
                            pLSettingSvc->mSignSettingModel.mIsCheckReview,
                            pLSettingSvc->mSignSettingModel.mIsCheckApproved,
                            pLSettingSvc->mManagerSettingModel.mCompany,
                            mLoadingDate,
                            pLSettingSvc->mMDSettingModel.mCheckupCycle,
                            pLSettingSvc->mDeviceNumber,
                            pLSettingSvc->mManagerSettingModel.mWCDepartment,
                            pLSettingSvc->mManagerSettingModel.mWCPosition,
                            pLSettingSvc->mManagerSettingModel.mWCName);

           if(bFirstPage)
               pPage->setMetrix(11, 7);
           else
               pPage->setMetrix(18, 7);
       }
       return pPage;
    }

    bool isSelectedProduct(int qseq)
    {
        foreach(int seq, mSelectedPSeqList)
        {
            if(qseq == seq)
                return true;
        }
        return false;
    }

    int getCountMDCheckupEventSelectedProduct()
    {
        int count = 0;

        foreach(PDCheckupDto checkup, mDailyHis.mEH.mCheckupEventList)
        {
            if(isSelectedProduct(checkup.mProductSeq))
                count++;
        }

        return count;
    }

    int getCountMDFailEventSelectedProduct()
    {
        int count = 0;

         foreach(EventDto detect, mDailyHis.mEH.mMDFailList)
         {
             if(isSelectedProduct(detect.mPDSeq))
                 count++;
         }

        return count;
    }

    int getCountMDPSSelectedProduct()
    {
        int count = 0;

        foreach(PDStatsDto stats, mDailyHis.mPS.mPSList)
        {
            if(isSelectedProduct(stats.mSeq))
                count++;
        }

        return count;
    }

    int getCountWCPSSelectedProduct()
    {
        int count = 0;

        foreach(PDWCStatsDto stats, mDailyHis.mEH.mPDWCStatsList)
        {
            if(isSelectedProduct(stats.mSeq))
                count++;
        }

        return count;
    }

    int getCountWCEventSelectedProduct()
    {
        int count = 0;

        foreach(EventDto detect, mDailyHis.mEH.mWCEventList)
        {
            if(!detect.isNGEvent() && !detect.isCalibEvent())
                continue;

            if(isSelectedProduct(detect.mPDSeq))
                count++;
        }

        return count;
    }
};

#endif // PANELREPORTCONTAINER_H
