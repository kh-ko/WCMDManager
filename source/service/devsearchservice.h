#ifndef DEVSEARCHSERVICE_H
#define DEVSEARCHSERVICE_H

#include <QObject>
#include "source/remote/remotesearcher.h"

#define pDevSearchSvc DevSearchService::getInstance()

class DevSearchService : public QObject
{
    Q_OBJECT
public:
    static DevSearchService * getInstance()
    {
        static DevSearchService  *pSelf = nullptr;

        if(pSelf == nullptr)
        {
            pSelf = new DevSearchService();
        }

        return pSelf;
    }

    bool mIsSearch = false;
    RemoteSearcher mSearcher;

    DevSearchService(QObject *parent = nullptr) : QObject(parent)
    {
        qDebug() << "[DspSearchService] create instance";

        connect(&mSearcher, SIGNAL(signalEventCompletedSearch()), this, SLOT(onCompleted()));
    }
    ~DevSearchService()
    {
    }

    void search()
    {
        if(mIsSearch)
            return;

        mSearcher.search();

        mIsSearch = true;
    }

signals:
    void signalEventCompletedSearch();

public slots:
    void onCompleted()
    {
        mIsSearch = false;
        emit signalEventCompletedSearch();
    }
};
#endif // DEVSEARCHSERVICE_H
