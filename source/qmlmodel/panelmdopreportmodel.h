#ifndef PANELMDOPREPORTMODEL_H
#define PANELMDOPREPORTMODEL_H

#include <QObject>
#include <QDate>
#include <QDebug>
#include "source/service/coreservice.h"
#include "source/qmlmodel/panelmdopreportrowmodel.h"

class PanelMDOPReportModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mStrDate READ getStrDate NOTIFY signalEventChangedStrDate);

public:
    CoreService * mpCoreService;

    int mFirstPageRowCnt = 10;
    int mPageRowCnt      = 17;
    QList<PanelMDOPReportRowModel *> mListRow;

    QString mStrDate;
    int     mYear;
    int     mMonth;
    int     mDay;
    QStringList mListStrWeekOfDayKor;
    QStringList mListStrMonthEng;

    QString getStrDate(){ return mStrDate; }

    void    setStrDate(QString value){ if(mStrDate == value) return; mStrDate = value; emit signalEventChangedStrDate(mStrDate);}

signals:
    void signalEventChangedStrDate(QString value);

public slots:
    Q_INVOKABLE int onCommandGetPageCnt()
    {
        if(mListRow.size() <= mFirstPageRowCnt)
            return 1;

        return ((mListRow.size() - mFirstPageRowCnt - 1) / mPageRowCnt) + 2;
    }

    Q_INVOKABLE int onCommandGetFirstPageRowCnt()
    {
        return mFirstPageRowCnt;
    }

    Q_INVOKABLE int onCommandGetPageRowCnt()
    {
        return mPageRowCnt;
    }

    Q_INVOKABLE void onCommandSetStrDate(QString value)
    {
        setStrDate(value);
    }

    Q_INVOKABLE PanelMDOPReportRowModel * onCommandGetRowInPage(int pageIdx, int idxInPage)
    {
        int absIdx;

        if(pageIdx == 0)
            absIdx = idxInPage;
        else
            absIdx = mFirstPageRowCnt + (pageIdx - 1) * mPageRowCnt + idxInPage;

        if(absIdx >= mListRow.size())
        {
            return nullptr;
        }

        return mListRow[absIdx];
    }

    Q_INVOKABLE PanelMDOPReportRowModel * onCommandAddRow(int pageIdx, int idxInPage)
    {
        int absIdx;

        if(pageIdx == 0)
            absIdx = idxInPage;
        else
            absIdx = mFirstPageRowCnt + (pageIdx - 1) * mPageRowCnt + idxInPage;

        if(absIdx >= mListRow.size())
        {
            int addSize = absIdx + 1 - mListRow.size();

            for(int i = 0; i < addSize; i ++)
            {
                mListRow.append(new PanelMDOPReportRowModel(this));
            }
        }

        return mListRow[absIdx];
    }


    Q_INVOKABLE void onCommandRemoveRow(int pageIdx, int rowIdxInPage)
    {
        int absIdx;

        if(pageIdx == 0)
            absIdx = rowIdxInPage;
        else
            absIdx = mFirstPageRowCnt + (pageIdx - 1) * mPageRowCnt + rowIdxInPage;

        if(absIdx < mListRow.size())
            mListRow.removeAt(absIdx);
    }

public:
    void setValue(QString fileName, QString value)
    {
        mListRow.clear();

        QString date = fileName.split("-PS.txt")[0];

        mYear  = date.split("-")[0].toInt();
        mMonth = date.split("-")[1].toInt();
        mDay   = date.split("-")[2].toInt();
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

        ProductStatisticsModel tempModel;
        QStringList rowList = value.split("\n");

        for(int i = 0; i < rowList.size(); i ++)
        {
            if(rowList.at(i) == nullptr || rowList.at(i).length() < 1)
                continue;

            PanelMDOPReportRowModel * row = new PanelMDOPReportRowModel(this);
            tempModel.setValue(rowList.at(i));

            row->mPno = QString::number(tempModel.mProductNo).rightJustified(3,'0');
            row->mPName = tempModel.mProductName;
            row->mTotalCnt = QString("%L1").arg(tempModel.mTotalCnt);
            row->mNGCnt = QString("%L1").arg(tempModel.mMDDetectCnt);
            row->mLimitFe = mpCoreService->mLSettingService.mMDSettingModel.mLimitCriteriaFe;
            row->mLimitSus = mpCoreService->mLSettingService.mMDSettingModel.mLimitCriteriaSus;

            if(tempModel.mTotalCnt == 0)
            {
                row->mNGRate = "0.00";
            }
            else
            {
                float fValue = (float)tempModel.mMDDetectCnt/tempModel.mTotalCnt;
                //row->mNGRate = QString::number(fValue * 100, 'f', 2);
                row->mNGRate = QString("%L1").arg(fValue, 0, 'f', 2);
            }
            row->setIsRemoved(false);
            mListRow.append(row);
        }
    }

    explicit PanelMDOPReportModel(QObject *parent = nullptr):QObject(parent)
    {
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
};
#endif // PANELMDOPREPORTMODEL_H
