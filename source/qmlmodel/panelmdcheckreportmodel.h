#ifndef PANELMDCHECKREPORTMODEL_H
#define PANELMDCHECKREPORTMODEL_H

#include <QObject>
#include <QDate>
#include <QDebug>
#include "source/service/coreservice.h"
#include "source/qmlmodel/panelmdcheckreportrowmodel.h"

class PanelMDCheckReportModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mStrDate READ getStrDate NOTIFY signalEventChangedStrDate);

public:
    CoreService * mpCoreService;

    int mFirstPageRowCnt = 16;
    int mPageRowCnt      = 23;
    QList<PanelMDCheckReportRowModel *> mListRow;

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

    Q_INVOKABLE PanelMDCheckReportRowModel * onCommandGetRowInPage(int pageIdx, int idxInPage)
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

    Q_INVOKABLE PanelMDCheckReportRowModel * onCommandAddRow(int pageIdx, int idxInPage)
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
                mListRow.append(new PanelMDCheckReportRowModel(this));
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
    void setDateByFileName(QString fileName)
    {
        QString date = fileName.split("-EH.txt")[0];

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
    }

    void addRowValue(QString value)
    {
        if(value.size() < 3)
            return;

        MDCheckupItemModel checkItem;
        checkItem.setValue(value);

        PanelMDCheckReportRowModel * pRow = new PanelMDCheckReportRowModel(this);

        pRow->mPno = QString::number(checkItem.mProductNo).rightJustified(3,'0');
        pRow->mPName = checkItem.mProductName;
        pRow->mCheckTime = checkItem.mTime;
        pRow->mFe01      = checkItem.mIsPassFe01  == true ? "O" : "X";
        pRow->mFe02      = checkItem.mIsPassFe02  == true ? "O" : "X";
        pRow->mFe03      = checkItem.mIsPassFe03  == true ? "O" : "X";
        pRow->mSus01     = checkItem.mIsPassSus01 == true ? "O" : "X";
        pRow->mSus02     = checkItem.mIsPassSus02 == true ? "O" : "X";
        pRow->mSus03     = checkItem.mIsPassSus03 == true ? "O" : "X";
        pRow->mLimitFe = mpCoreService->mLSettingService.mMDSettingModel.mLimitCriteriaFe;
        pRow->mLimitSus = mpCoreService->mLSettingService.mMDSettingModel.mLimitCriteriaSus;

        mListRow.append(pRow);
    }

    explicit PanelMDCheckReportModel(QObject *parent = nullptr):QObject(parent)
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
#endif // PANELMDCHECKREPORTMODEL_H
