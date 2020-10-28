#ifndef DATALOADERSERVICE_H
#define DATALOADERSERVICE_H

#include <QObject>

#include "source/model/productsettingmodel.h"
#include "source/model/eventitemmodel.h"
#include "source/model/mdcheckupitemmodel.h"
#include "source/model/mddetectitemmodel.h"
#include "source/model/weightcheckermodel.h"
#include "source/util/fileloaderthread.h"
#include "source/globaldef/EnumDefine.h"
#include "source/service/productstatisticsservice.h"

class DataLoaderService : public QObject
{
    Q_OBJECT
public:

    FileLoaderThread   mFileLoader;
    QStringList mAllFileList;
    QString mAppDirPath;
    int mDeviceNumber= -1;
    int mYear        = -1;
    int mMonth       = -1;
    int mDay         = -1;
    int mProcDay     = 1;

    bool mIsLoading                 = false;
    ProductStatisticsService mProductStatistics;
    WeightCheckerModel           mWCModel;
    QList<ProductSettingModel *> mListProductHis;
    QList<MDCheckupItemModel *>  mListMDCheckupHis;
    QList<MDDetectItemModel *>   mListMDDetectHis;

    void setIsLoading               (bool value){ if(mIsLoading == value) return; mIsLoading = value; emit signalEventChangedIsLoading(mIsLoading); }
signals:
    void signalEventChangedIsLoading               (bool value);

public:
    void loadData(int dNumber, int year, int month, int day, bool reLoad = false);

signals:
    void signalCommandReadProductStatistics(QString path, QString fileName);
    void signalCommandReadProductHistory(QString path, QString fileName);
    void signalCommandReadEventHistory(QString path, QString fileName, int lineCnt);

public slots:
    void onSignalReadProductStatistics(int error, QString content);
    void onSignalReadProductHistory(int error, QString content);
    void onSignalReadEventHistory(int error, QStringList content);
    void onSignalReadEofEventHistory();

private:
    QString getPath();
    QString getProductStatisticsFileName();
    QString getEventHistoryFileName();
    QString getProductHistoryFileName();
    bool    isMetalCheckupEvent(QString value);
    bool    isMetalDetectEvent(QString value);
    bool    isWeightCheckerEvent(QString value);
    void    reset();
public:
    explicit DataLoaderService(QObject *parent = nullptr);


};

#endif // DATALOADERSERVICE_H
