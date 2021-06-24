#ifndef DEVINFODTO_H
#define DEVINFODTO_H

#include <QObject>

class DevInfoDto
{
public:
    int     mNumber;
    QString mName  = "";
    QString mIp    = "";
    QList<quint64> mPDSeq;
    QList<QString> mLimFe;
    QList<QString> mLimSus;

    DevInfoDto(){}
    DevInfoDto(const DevInfoDto& copy) :
        mNumber(copy.mNumber),
        mName  (copy.mName  ),
        mIp    (copy.mIp    ),
        mPDSeq (copy.mPDSeq ),
        mLimFe (copy.mLimFe ),
        mLimSus(copy.mLimSus){}
    ~DevInfoDto(){}

    DevInfoDto& operator=(const DevInfoDto& other)
    {
        mNumber = other.mNumber;
        mName   = other.mName  ;
        mIp     = other.mIp    ;

        mPDSeq  = other.mPDSeq;
        mLimFe  = other.mLimFe;
        mLimSus = other.mLimSus;

        return *this;
    }

    QString getLimFe(quint64 pdSeq)
    {
        for(int i = 0; i < mPDSeq.size(); i ++)
        {
            if(mPDSeq.at(i) == pdSeq)
                return mLimFe.at(i);
        }

        return "2.5";
    }

    QString getLimSus(quint64 pdSeq)
    {
        for(int i = 0; i < mPDSeq.size(); i ++)
        {
            if(mPDSeq.at(i) == pdSeq)
                return mLimSus.at(i);
        }

        return "2.5";
    }
};
Q_DECLARE_METATYPE(DevInfoDto);
#endif // DEVINFODTO_H
