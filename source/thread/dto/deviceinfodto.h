#ifndef DEVICEINFODTO_H
#define DEVICEINFODTO_H

#include <QObject>

class DeviceInfoDto
{
public:
    quint32 mIPv4Address = 0;
    int mDeviceNum=0;
    QString mIp   ="";
    QString mDeviceName = "";

    DeviceInfoDto(){}
    DeviceInfoDto(int deviceNum, QString ip, QString deviceName):mDeviceNum (deviceNum ),
                                                                 mIp        (ip        ),
                                                                 mDeviceName(deviceName){}
    DeviceInfoDto(const DeviceInfoDto& copy):mIPv4Address(copy.mIPv4Address),
                                             mDeviceNum (copy.mDeviceNum ),
                                             mIp        (copy.mIp        ),
                                             mDeviceName(copy.mDeviceName){}
    ~DeviceInfoDto(){}

    DeviceInfoDto& operator=(const DeviceInfoDto& other)
    {
        mIPv4Address= other.mIPv4Address;
        mDeviceNum  = other.mDeviceNum  ;
        mIp         = other.mIp         ;
        mDeviceName = other.mDeviceName ;

        return *this;
    }
};

Q_DECLARE_METATYPE(DeviceInfoDto);

#endif // DEVICEINFODTO_H
