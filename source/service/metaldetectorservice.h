#ifndef METALDETECTORSERVICE_H
#define METALDETECTORSERVICE_H

#include <QObject>

class MetalDetectorService : public QObject
{
    Q_OBJECT
public:
    explicit MetalDetectorService(QObject *parent = nullptr);

signals:

};

#endif // METALDETECTORSERVICE_H
