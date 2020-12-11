#ifndef DEVINFODTO_H
#define DEVINFODTO_H

#include <QObject>

class DevInfoDto
{
public:
    int     mNumber;
    QString mName  = "";
    QString mIp    = "";

    DevInfoDto(){}
    DevInfoDto(const DevInfoDto& copy) :
        mNumber(copy.mNumber),
        mName  (copy.mName  ),
        mIp    (copy.mIp    ){}
    ~DevInfoDto(){}

    DevInfoDto& operator=(const DevInfoDto& other)
    {
        mNumber = other.mNumber;
        mName   = other.mName  ;
        mIp     = other.mIp    ;

        return *this;
    }
};
Q_DECLARE_METATYPE(DevInfoDto);
#endif // DEVINFODTO_H
