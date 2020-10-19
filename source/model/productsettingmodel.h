#ifndef PRODUCTSETTINGMODEL_H
#define PRODUCTSETTINGMODEL_H

#include <QObject>

class ProductSettingModel : QObject
{
    Q_OBJECT

public:
    quint64 mSeq                ;
    int     mNo                 ;
    QString mName               ;
    int     mUnderWeight        ;
    int     mUnderWarningWeight ;
    int     mNormalWeight       ;
    int     mOverWeight         ;
    int     mOverWarningWeight  ;
    int     mTareWeight         ;
    int     mMDSenstivity       ;

public:
    void setValue(QString value)
    {
        QStringList fields = value.split(",");

        for(int i = 0; i < fields.size(); i ++)
        {
            QString key   = fields.at(i).split(":")[0];
            QString value = fields.at(i).split(":")[1];

            if     (key == "Seq"               ){mSeq                = value.toULongLong();}
            else if(key == "No"                ){mNo                 = value.toInt()      ;}
            else if(key == "Name"              ){mName               = value              ;}
            else if(key == "UnderWeight"       ){mUnderWeight        = value.toInt()      ;}
            else if(key == "UnderWarningWeight"){mUnderWarningWeight = value.toInt()      ;}
            else if(key == "NormalWeight"      ){mNormalWeight       = value.toInt()      ;}
            else if(key == "OverWarningWeight" ){mOverWeight         = value.toInt()      ;}
            else if(key == "OverWeight"        ){mOverWarningWeight  = value.toInt()      ;}
            else if(key == "TareWeight"        ){mTareWeight         = value.toInt()      ;}
            else if(key == "MDSenstivity"      ){mMDSenstivity       = value.toInt()      ;}
        }
    }
    explicit ProductSettingModel(QObject *parent = nullptr):QObject(parent){}
};

#endif // PRODUCTSETTINGMODEL_H
