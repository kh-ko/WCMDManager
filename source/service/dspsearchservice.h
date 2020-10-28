#ifndef DSPSEARCHSERVICE_H
#define DSPSEARCHSERVICE_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QUdpSocket>

#include "source/model/deviceinfomodel.h"

class DspSearchService : public QObject
{
    Q_OBJECT
public:
    bool mIsSearch = false;
    QHostAddress mGroupAddress     ;
    quint16      mPort    = 31072  ;
    QTimer       mTimer            ;
    QUdpSocket * mpSocket = nullptr;

    QList<DeviceInfoModel *> mListDeviceInfo;

signals:
    void signalEventCompletedSearch();

public slots:
    void onTimeout();
    void onReceive();
    void onSockError(QAbstractSocket::SocketError error);

public:
    void search();
    explicit DspSearchService(QObject *parent = nullptr);
    ~DspSearchService();

private:
    DeviceInfoModel * findDeviceInfo(int dNum);
    void addDeviceInfo(int dNum, QString name, QString ip);
    void searchComplete();
    void open();
    void close();
    void clear();
};

#endif // DSPSEARCHSERVICE_H
