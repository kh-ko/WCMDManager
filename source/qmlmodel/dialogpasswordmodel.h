#ifndef DIALOGPASSWORDMODEL_H
#define DIALOGPASSWORDMODEL_H

#include <QObject>

#include "source/service/localsettingservice.h"

class DialogPasswordModel : public QObject
{
    Q_OBJECT

public slots:
    Q_INVOKABLE QString onCommandGetPassword()
    {
        return pLSettingSvc->mPassword;
    }
public:
    explicit DialogPasswordModel(QObject *parent = nullptr):QObject(parent)
    {
    }
};
#endif // DIALOGPASSWORDMODEL_H
