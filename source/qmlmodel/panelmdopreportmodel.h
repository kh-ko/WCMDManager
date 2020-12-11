#ifndef PANELMDOPREPORTMODEL_H
#define PANELMDOPREPORTMODEL_H

#include <QObject>
#include <QDate>
#include <QDebug>

#include "source/qmlmodel/panelmdopreportrowmodel.h"

class PanelMDOPReportModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mStrDate READ getStrDate NOTIFY signalEventChangedStrDate);

public:
    int mFirstPageRowCnt = 10;
    int mPageRowCnt      = 17;
    QList<PanelMDOPReportRowModel *> mListRow;

    QString mStrDate;
    DailyHistory mDailyHis;

    QStringList mListStrWeekOfDayKor;
    QStringList mListStrMonthEng;

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

        connect(&mDailyHis, SIGNAL(signalEventLoadCompleted(int)), this, SLOT(onLoaded(int)));
    }

    void load(int devNum, QDate date)
    {
        mDailyHis.load(devNum, QString("%1/%2").arg(FileDef::DATABASE_DIR()).arg(devNum), date.toString(DATE_FILE_NAME_FMT));

        QString weekOfDay = mListStrWeekOfDayKor[date.dayOfWeek() - 1];

        if(pLSettingSvc->mLanguage == EnumDefine::Language::LANG_KOR){
            mStrDate = QString("%1 년 %2 월 %3 일 %4요일").arg(QString::number(date.year()).rightJustified(4, '0'))
                                                        .arg(QString::number(date.month()).rightJustified(2, '0'))
                                                        .arg(QString::number(date.day()).rightJustified(2, '0'))
                                                        .arg(weekOfDay);
        }
        else
        {
            QString month = mListStrMonthEng[date.month() - 1];

            mStrDate = QString("%1 %2th, %3").arg(month)
                                             .arg(QString::number(date.day()).rightJustified(2, '0'))
                                             .arg(QString::number(date.year()).rightJustified(4, '0'));
        }
    }

    QString getStrDate(){ return mStrDate; }

    void    setStrDate(QString value){ if(mStrDate == value) return; mStrDate = value; emit signalEventChangedStrDate(mStrDate);}

signals:
    void signalEventChangedStrDate(QString value);
    void signalEventLoadCompleted();

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

    void onLoaded(int err)
    {
        foreach(PDStatsDto stats, mDailyHis.mPS.mPSList)
        {
            PanelMDOPReportRowModel * row = new PanelMDOPReportRowModel(this);

            row->mPno       = QString::number(stats.mNum).rightJustified(3,'0');
            row->mPName     = stats.mName;
            row->mTotalCnt  = QString("%L1").arg(stats.mMDTotalCnt);
            row->mNGCnt     = QString("%L1").arg(stats.mMDFailCnt);
            row->mLimitFe   = pLSettingSvc->mMDSettingModel.mLimitCriteriaFe;
            row->mLimitSus  = pLSettingSvc->mMDSettingModel.mLimitCriteriaSus;

            if(stats.mMDTotalCnt == 0)
            {
                row->mNGRate = "0.00";
            }
            else
            {
                float fValue = (float)stats.mMDFailCnt/stats.mMDTotalCnt;
                //row->mNGRate = QString::number(fValue * 100, 'f', 2);
                row->mNGRate = QString("%L1").arg(fValue, 0, 'f', 2);
            }
            row->setIsRemoved(false);

            mListRow.append(row);
        }

        emit signalEventLoadCompleted();
    }

};
#endif // PANELMDOPREPORTMODEL_H
