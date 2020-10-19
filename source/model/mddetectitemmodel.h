#ifndef MDDETECTITEMMODEL_H
#define MDDETECTITEMMODEL_H

#include <QObject>
#include "source/model/eventitemmodel.h"
class MDDetectItemModel : QObject
{
    Q_OBJECT

public:
    int     mProductNo;
    QString mProductName;
    QString mTime;

public:
    void setValue(EventItemModel * event, int productNo, QString productName)
    {
        mProductNo = productNo;
        mProductName = productName;
        mTime = event->mDate.split(" ")[1].split(".")[0];
    }
    explicit MDDetectItemModel(QObject *parent = nullptr):QObject(parent){}
};
#endif // MDDETECTITEMMODEL_H
