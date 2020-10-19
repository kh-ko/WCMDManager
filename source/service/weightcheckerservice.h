#ifndef WEIGHTCHECKERSERVICE_H
#define WEIGHTCHECKERSERVICE_H

#include <QObject>

class WeightCheckerService : public QObject
{
    Q_OBJECT
public:
    explicit WeightCheckerService(QObject *parent = nullptr);

signals:

};

#endif // WEIGHTCHECKERSERVICE_H
