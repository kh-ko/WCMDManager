#ifndef WEIGHTCHECKERSETTINGMODEL_H
#define WEIGHTCHECKERSETTINGMODEL_H

#include <QObject>

class WeightCheckerSettingModel : QObject
{
    Q_OBJECT
public:
    explicit WeightCheckerSettingModel(QObject *parent = nullptr):QObject(parent)
    {

    }
};

#endif // WEIGHTCHECKERSETTINGMODEL_H
