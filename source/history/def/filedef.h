#ifndef FILEDEF_H
#define FILEDEF_H

#include <QObject>
#include <QApplication>

class FileDef: public QObject
{
    Q_OBJECT
public:
    explicit FileDef(QObject *parent = nullptr) : QObject(parent){}
    ~FileDef(){}

    static QString DATABASE_DIR()
    {
        static QString dir = QString("%1/database").arg(QApplication::applicationDirPath());
        return dir;
    }
};

#endif // FILEDEF_H
