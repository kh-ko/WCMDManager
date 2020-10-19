#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QTextStream>

class FileWriter : public QObject
{
    Q_OBJECT
public:
    QFile * mpFile = nullptr;
    QString mPath = "";
    QString mFileName = "";

    bool appendWrite(QString path, QString fileName, char * content, int size);
    void close();
    void mkdirRecursively(QString path);
    explicit FileWriter(QObject *parent = nullptr);
    ~FileWriter();
};

#endif // FILEWRITER_H
