#include "productstatisticsservice.h"

#include <QDebug>

void ProductStatisticsService::reset()
{
    for(int i = 0; i < mListMonthStatistics.size(); i ++)
    {
        delete mListMonthStatistics.at(i);
    }

    mListMonthStatistics.clear();

    for(int day = 0; day < 31; day++)
    {
        for(int i = 0; i < mListDailyStatistics[day].size(); i ++)
        {
            delete mListDailyStatistics[day].at(i);
        }
        mListDailyStatistics[day].clear();
    }
}
void ProductStatisticsService::addDailyStatistics(int day, QStringList valueList)
{
    for(int i = 0; i < valueList.size(); i ++)
    {
        addMonthStatistics(valueList.at(i));

        ProductStatisticsModel * pModel = new ProductStatisticsModel(this);
        pModel->setValue(valueList.at(i));

        mListDailyStatistics[day - 1].append(pModel);
    }

}

void ProductStatisticsService::addMonthStatistics(QString value)
{
    ProductStatisticsModel * pNewModel = new ProductStatisticsModel(this);
    pNewModel->setValue(value);

    ProductStatisticsModel * pModel = findMonthStatistcs(pNewModel->mProductSeq);

    if(pModel == nullptr)
    {
        for(int i = 0; i < mListMonthStatistics.size(); i ++)
        {
            if(pNewModel->mProductNo < mListMonthStatistics.at(i)->mProductNo)
            {
                mListMonthStatistics.insert(i, pNewModel);
                return;
            }
        }

        mListMonthStatistics.append(pNewModel);
        return;
    }

    pModel->addValue(pNewModel);
}

ProductStatisticsModel * ProductStatisticsService::findMonthStatistcs(quint64 seq)
{
    for(int i = 0; i < mListMonthStatistics.size(); i ++)
    {
        if(mListMonthStatistics.at(i)->mProductSeq == seq)
        {
            return mListMonthStatistics.at(i);
        }
    }
    return nullptr;
}

void ProductStatisticsService::sort()
{
    for(int i = 0; i < mListMonthStatistics.size(); i ++)
    {
        ProductStatisticsModel * pMin = mListMonthStatistics.at(i);

        for(int j = i; j < mListMonthStatistics.size(); j ++)
        {
             ProductStatisticsModel * pTemp = mListMonthStatistics.at(j);

             if(pTemp->mProductNo < pMin->mProductNo)
             {
                 mListMonthStatistics.replace(j, pMin);
                 pMin = pTemp;
             }
        }
        mListMonthStatistics.replace(i, pMin);
    }
}

QList<ProductStatisticsModel *> * ProductStatisticsService::getStatistics(int day)
{
    if(day < 1 || day > 31)
        return nullptr;

    return &mListDailyStatistics[day - 1];
}
ProductStatisticsService::ProductStatisticsService(QObject *parent) : QObject(parent)
{
}
