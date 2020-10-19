#ifndef PRODUCTSTATISTICSSERVICE_H
#define PRODUCTSTATISTICSSERVICE_H

#include <QObject>
#include <QMap>

#include "source/model/productstatisticsmodel.h"

class ProductStatisticsService : public QObject
{
    Q_OBJECT
public:
    QList<ProductStatisticsModel *> mListMonthStatistics;
    QList<ProductStatisticsModel *> mListDailyStatistics[31];

    void reset();
    void addDailyStatistics(int day, QStringList valueList);
    void addMonthStatistics(QString value);
    ProductStatisticsModel * findMonthStatistcs(quint64 seq);
    void sort();
    QList<ProductStatisticsModel *> * getStatistics(int day);
    explicit ProductStatisticsService(QObject *parent = nullptr);

signals:

};

#endif // PRODUCTSTATISTICSSERVICE_H
