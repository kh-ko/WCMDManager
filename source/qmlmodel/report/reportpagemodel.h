#ifndef REPORTPAGEMODEL_H
#define REPORTPAGEMODEL_H

#include <QObject>
#include <QDate>
#include <QDebug>

#include "source/service/devinfoservice.h"
#include "source/globaldef/EnumDefine.h"
#include "source/history/def/datetimeform.h"
#include "source/service/localsettingservice.h"
#include "source/history/dailyhistory.h"

class ReportPageModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mPageNum      READ getPageNum       NOTIFY signalEventChangedPageNum   );
    Q_PROPERTY(QString mReportDate   READ getReportDate    NOTIFY signalEventChangedReportDate);
    Q_PROPERTY(int     mPageType     READ getPageType      NOTIFY signalEventChangedPageType  );
    Q_PROPERTY(QString mTitle        READ getTitle         NOTIFY signalEventChangedTitle     );
    Q_PROPERTY(bool    mWrite        READ getWrite         NOTIFY signalEventChangedWrite     );
    Q_PROPERTY(bool    mReview       READ getReview        NOTIFY signalEventChangedReview    );
    Q_PROPERTY(bool    mApproved     READ getApproved      NOTIFY signalEventChangedApproved  );
    Q_PROPERTY(QString mCompany      READ getCompany       NOTIFY signalEventChangedCompany   );
    Q_PROPERTY(QString mStrDate      READ getStrDate       NOTIFY signalEventChangedStrDate   );
    Q_PROPERTY(QString mCheckCycle   READ getCheckCycle    NOTIFY signalEventChangedCheckCycle);
    Q_PROPERTY(QString mDevNum       READ getDevNum        NOTIFY signalEventChangedDevNum    );
    Q_PROPERTY(QString mDepartment   READ getDepartment    NOTIFY signalEventChangedDepartment);
    Q_PROPERTY(QString mPosition     READ getPosition      NOTIFY signalEventChangedPosition  );
    Q_PROPERTY(QString mName         READ getName          NOTIFY signalEventChangedName      );
    Q_PROPERTY(bool    mIsFirst      READ getIsFirst       NOTIFY signalEventChangedIsFirst   );

public:
    //int mFirstPageRowCnt = 10;
    //int mPageRowCnt      = 17;
    //QList<PanelMDOPReportRowModel *> mListRow;

    QString mPageNum   ;
    QString mReportDate;
    EnumDefine::ReportPageType mPageType;
    QString mTitle     ;
    bool    mWrite     ;
    bool    mReview    ;
    bool    mApproved  ;
    QString mCompany   ;
    QString mStrDate   ;
    QString mCheckCycle;
    QString mDevNum    ;
    QString mDepartment;
    QString mPosition  ;
    QString mName      ;
    bool    mIsFirst   ;

    int     mAddRowIdx = 0;
    QList<QStringList> mRows;

    QStringList mListStrWeekOfDayKor;
    QStringList mListStrMonthEng;

    QString getPageNum   (){ return mPageNum   ;}
    QString getReportDate(){ return mReportDate;}
    int     getPageType  (){ return mPageType  ;}
    QString getTitle     (){ return mTitle     ;}
    bool    getWrite     (){ return mWrite     ;}
    bool    getReview    (){ return mReview    ;}
    bool    getApproved  (){ return mApproved  ;}
    QString getCompany   (){ return mCompany   ;}
    QString getStrDate   (){ return mStrDate   ;}
    QString getCheckCycle(){ return mCheckCycle;}
    QString getDevNum    (){ return mDevNum    ;}
    QString getDepartment(){ return mDepartment;}
    QString getPosition  (){ return mPosition  ;}
    QString getName      (){ return mName      ;}
    int     getIsFirst   (){ return mIsFirst   ;}

    void    setPageNum   (QString value){ if( value == mPageNum   )return; mPageNum    = value; emit signalEventChangedPageNum   (value);}
    void    setReportDate(QString value){ if( value == mReportDate)return; mReportDate = value; emit signalEventChangedReportDate(value);}
    void    setPageType  (int     value){ if( value == mPageType  )return; mPageType   = (EnumDefine::ReportPageType)value; emit signalEventChangedPageType  (value);}
    void    setTitle     (QString value){ if( value == mTitle     )return; mTitle      = value; emit signalEventChangedTitle     (value);}
    void    setWrite     (bool    value){ if( value == mWrite     )return; mWrite      = value; emit signalEventChangedWrite     (value);}
    void    setReview    (bool    value){ if( value == mReview    )return; mReview     = value; emit signalEventChangedReview    (value);}
    void    setApproved  (bool    value){ if( value == mApproved  )return; mApproved   = value; emit signalEventChangedApproved  (value);}
    void    setCompany   (QString value){ if( value == mCompany   )return; mCompany    = value; emit signalEventChangedCompany   (value);}
    void    setStrDate   (QString value){ if( value == mStrDate   )return; mStrDate    = value; emit signalEventChangedStrDate   (value);}
    void    setCheckCycle(QString value){ if( value == mCheckCycle)return; mCheckCycle = value; emit signalEventChangedCheckCycle(value);}
    void    setDevNum    (QString value){ if( value == mDevNum    )return; mDevNum     = value; emit signalEventChangedDevNum    (value);}
    void    setDepartment(QString value){ if( value == mDepartment)return; mDepartment = value; emit signalEventChangedDepartment(value);}
    void    setPosition  (QString value){ if( value == mPosition  )return; mPosition   = value; emit signalEventChangedPosition  (value);}
    void    setName      (QString value){ if( value == mName      )return; mName       = value; emit signalEventChangedName      (value);}
    void    setIsFirst   (int     value){ if( value == mIsFirst   )return; mIsFirst    = value; emit signalEventChangedIsFirst   (value);}

    explicit ReportPageModel(QObject *parent = nullptr):QObject(parent)
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
    }

    void setHeader(QString reportDate, EnumDefine::ReportPageType pageType, bool bFirst, int pageNum, QString title, bool write, bool review, bool approved, QString company, QDate date, QString checkCycle, int devNum, QString department, QString position, QString name)
    {
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

        setPageNum    (QString::number(pageNum));
        setReportDate (reportDate);
        setPageType   (pageType  );
        setIsFirst    (bFirst    );
        setTitle      (title     );
        setWrite      (write     );
        setReview     (review    );
        setApproved   (approved  );
        setCompany    (company   );
        setCheckCycle (checkCycle);
        setDevNum     (QString::number(devNum).rightJustified(2,'0'));
        setDepartment (department);
        setPosition   (position  );
        setName       (name      );
    }

    void setMetrix(int rowCnt, int colCnt)
    {
        QStringList col;

        for(int ri = 0; ri < rowCnt; ri ++)
        {
            col.clear();
            for(int ci = 0; ci < colCnt; ci++)
            {
                col.append("");
            }
            mRows.append(col);
        }
    }

    void setColumnValue(int rowIdx, int colIdx, QString value)
    {
        (mRows[rowIdx])[colIdx] = value;
    }

    void addRow(QStringList row)
    {

        for(int i = 0; i < row.size(); i ++)
        {
            setColumnValue(mAddRowIdx, i, row[i]);
        }

        mAddRowIdx++;
    }

    bool isFull()
    {
        if(mAddRowIdx >= mRows.size())
            return true;
        return false;
    }


signals:
    void signalEventChangedPageNum   (QString value);
    void signalEventChangedReportDate(QString value);
    void signalEventChangedPageType  (int     value);
    void signalEventChangedTitle     (QString value);
    void signalEventChangedWrite     (bool    value);
    void signalEventChangedReview    (bool    value);
    void signalEventChangedApproved  (bool    value);
    void signalEventChangedCompany   (QString value);
    void signalEventChangedStrDate   (QString value);
    void signalEventChangedCheckCycle(QString value);
    void signalEventChangedDevNum    (QString value);
    void signalEventChangedDepartment(QString value);
    void signalEventChangedPosition  (QString value);
    void signalEventChangedName      (QString value);
    void signalEventChangedIsFirst   (bool    value);

public slots:
    Q_INVOKABLE void onCommandSetTitle     (QString value){ setTitle     (value);}
    Q_INVOKABLE void onCommandSetWrite     (bool    value){ setWrite     (value);}
    Q_INVOKABLE void onCommandSetReview    (bool    value){ setReview    (value);}
    Q_INVOKABLE void onCommandSetApproved  (bool    value){ setApproved  (value);}
    Q_INVOKABLE void onCommandSetCompany   (QString value){ setCompany   (value);}
    Q_INVOKABLE void onCommandSetStrDate   (QString value){ setStrDate   (value);}
    Q_INVOKABLE void onCommandSetCheckCycle(QString value){ setCheckCycle(value);}
    Q_INVOKABLE void onCommandSetDevNum    (QString value){ setDevNum    (value);}
    Q_INVOKABLE void onCommandSetDepartment(QString value){ setDepartment(value);}
    Q_INVOKABLE void onCommandSetPosition  (QString value){ setPosition  (value);}
    Q_INVOKABLE void onCommandSetName      (QString value){ setName      (value);}
    Q_INVOKABLE void onCommandSetIsFirst   (bool    value){ setIsFirst   (value);}
    Q_INVOKABLE int onCommandGetRowCnt()
    {
        return mRows.size();
    }
    Q_INVOKABLE QString onCommandGetColumnValue(int rowIdx, int colIdx)
    {
        return (mRows[rowIdx])[colIdx];
    }
    Q_INVOKABLE void onCommandDelete()
    {
        deleteLater();
    }


};
#endif // REPORTPAGEMODEL_H
