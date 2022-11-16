#ifndef PDTIMESDTO_H
#define PDTIMESDTO_H

#include <QObject>
#include <QDebug>

class PDTimeDto
{
public:
    quint64    mSeq                = 0;
    qint64     mTime               = 0;

    PDTimeDto(){}
    PDTimeDto(const PDTimeDto& copy) :
        mSeq               (copy.mSeq               ),
        mTime              (copy.mTime              ){}
    ~PDTimeDto(){}

    PDTimeDto& operator=(const PDTimeDto& other)
    {
        mSeq                = other.mSeq               ;
        mTime               = other.mTime              ;

        return *this;
    }

    QString toString()
    {
        return QString("ProdcutSettingSeq:%1,mTime:%2");
    }
};

Q_DECLARE_METATYPE(PDTimeDto);
#endif // PDTIMESDTO_H
