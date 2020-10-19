#ifndef EVENTITEMMODEL_H
#define EVENTITEMMODEL_H

#include <QObject>

class EventItemModel : QObject
{
    Q_OBJECT

public:
    QString mDate;
    int     mProductHisIdx;
    QString mEventType;
    int     mValue;

signals:

public:
    void setValue(QString value)
    {
        QStringList fields = value.split(",");

        for(int i = 0; i < fields.size(); i ++)
        {
            if(fields[i].contains(":") == false)
                continue;

            int splitIdx = fields[i].indexOf(":");
            QString key = fields[i].left(splitIdx);
            QString value = fields[i].mid(splitIdx+1);

            if     (key == "DT"                ){mDate               = value          ;}
            else if(key == "PDHIS_IDX"         ){mProductHisIdx      = value.toInt()  ;}
            else if(key == "EVENT"             ){mEventType          = value          ;}
            else if(key == "VALUE"             ){mValue              = value.toInt()  ;}
        }
    }
    explicit EventItemModel(QObject *parent = nullptr):QObject(parent){}
};

#endif // EVENTITEMMODEL_H
