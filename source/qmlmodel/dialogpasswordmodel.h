#ifndef DIALOGPASSWORDMODEL_H
#define DIALOGPASSWORDMODEL_H

#include <QObject>

#include "source/service/coreservice.h"

class DialogPasswordModel : public QObject
{
    Q_OBJECT

public slots:
    Q_INVOKABLE QString onCommandGetPassword()
    {
        return CoreService::getInstance()->mLSettingService.mPassword;
    }
public:
    explicit DialogPasswordModel(QObject *parent = nullptr):QObject(parent)
    {
    }
};
#endif // DIALOGPASSWORDMODEL_H
