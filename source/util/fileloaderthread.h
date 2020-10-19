#ifndef FILELOADERTHREAD_H
#define FILELOADERTHREAD_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QThread>

class FileLoakerThreadWorker : public QObject
{
    Q_OBJECT
public:
    QFile   *mpFile = nullptr;
    QTextStream *mpOutStream = nullptr;

    explicit FileLoakerThreadWorker(QObject *parent = nullptr);
    ~FileLoakerThreadWorker();

public slots:
    void onCommandReadAll(QString path, QString fileName);
    void onCommandReadLine(QString path, QString fileName, int lineCnt);

signals:
    void signalReadAll (int error, QString content  );
    void signalReadLine(int error, QStringList lines);
    void signalReadEof (                            );

private:
    void close();
};

class FileLoaderThread : public QObject
{
    Q_OBJECT
public:
    FileLoakerThreadWorker * mpWoker;
    QThread mThread;

    explicit FileLoaderThread(QObject *parent = nullptr) : QObject(parent)
    {
        mpWoker = new FileLoakerThreadWorker;
        mpWoker->moveToThread(&mThread);

        connect(&mThread, &QThread::finished, mpWoker, &QObject::deleteLater);
        connect(this, SIGNAL(signalCommandReadAll  (QString, QString     )), mpWoker, SLOT(onCommandReadAll (QString, QString     )));
        connect(this, SIGNAL(signalCommandReadLine (QString, QString, int)), mpWoker, SLOT(onCommandReadLine(QString, QString, int)));

        connect(mpWoker, SIGNAL(signalReadAll (int, QString    )), this, SLOT(onSignalReadAll (int, QString    )));
        connect(mpWoker, SIGNAL(signalReadLine(int, QStringList)), this, SLOT(onSignalReadLine(int, QStringList)));
        connect(mpWoker, SIGNAL(signalReadEof (                )), this, SLOT(onSignalReadEof (                )));

        mThread.start();
    }
    ~FileLoaderThread()
    {
        mThread.quit();
        mThread.wait();
    }

signals:
    void signalReadAll (int error, QString content  );
    void signalReadLine(int error, QStringList lines);
    void signalReadEof (                            );

public slots:
    void onCommandReadAll(QString path, QString fileName)              {emit signalCommandReadAll (path, fileName);}
    void onCommandReadLine(QString path, QString fileName, int lineCnt){emit signalCommandReadLine(path, fileName, lineCnt);}

signals:
    void signalCommandReadAll (QString path, QString fileName);
    void signalCommandReadLine(QString path, QString fileName, int lineCnt);

public slots:
    void onSignalReadAll (int error, QString     content){emit signalReadAll (error, content);}
    void onSignalReadLine(int error, QStringList lines  ){emit signalReadLine(error, lines);}
    void onSignalReadEof (                              ){emit signalReadEof();}
};

#endif // FILELOADERTHREAD_H
