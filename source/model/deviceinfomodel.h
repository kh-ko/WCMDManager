#ifndef DEVICEINFOMODEL_H
#define DEVICEINFOMODEL_H

#include <QObject>

class DeviceInfoModel : QObject
{
    Q_OBJECT

public:
    int     mNumber;
    QString mName = "";
    QString mIp = "";

signals:

public:
    explicit DeviceInfoModel(QObject *parent = nullptr):QObject(parent){}
};
#endif // DEVICEINFOMODEL_H
