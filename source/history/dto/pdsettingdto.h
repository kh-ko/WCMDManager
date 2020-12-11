#ifndef PDSETTINGDTO_H
#define PDSETTINGDTO_H
#include <QObject>

class PDSettingDto
{
public:
    quint64 mSeq                      =0;
    QString mName                     ;
    quint16 mProductNum               =0;
    quint16 mLength                   =0;
    quint16 mSpeed                    =0;
    int      mMotorAccelerationTime   =0;
    int      mWCNormalWeight          =0;
    int      mWCUnderWarningWeight    =0;
    int      mWCOverWarningWeight     =0;
    int      mWCUnderWeight           =0;
    int      mWCOverWeight            =0;
    int      mWCTareWeight            =0;
    quint16  mWCNGMotion              =0;
    int      mWCDynamicFactor         =0;
    quint16  mWCEnableEtcError        =0;
    quint16  mMDSenstivity            =0;
    quint16  mMDNGMotion              =0;

    PDSettingDto(){}
    PDSettingDto(const PDSettingDto& copy) :
        mSeq                  (copy.mSeq                   ),
        mName                 (copy.mName                  ),
        mProductNum           (copy.mProductNum            ),
        mLength               (copy.mLength                ),
        mSpeed                (copy.mSpeed                 ),
        mMotorAccelerationTime(copy. mMotorAccelerationTime),
        mWCNormalWeight       (copy. mWCNormalWeight       ),
        mWCUnderWarningWeight (copy. mWCUnderWarningWeight ),
        mWCOverWarningWeight  (copy. mWCOverWarningWeight  ),
        mWCUnderWeight        (copy. mWCUnderWeight        ),
        mWCOverWeight         (copy. mWCOverWeight         ),
        mWCTareWeight         (copy. mWCTareWeight         ),
        mWCNGMotion           (copy. mWCNGMotion           ),
        mWCDynamicFactor      (copy. mWCDynamicFactor      ),
        mWCEnableEtcError     (copy. mWCEnableEtcError     ),
        mMDSenstivity         (copy. mMDSenstivity         ),
        mMDNGMotion           (copy. mMDNGMotion           ){}
    ~PDSettingDto(){}

    PDSettingDto& operator=(const PDSettingDto& other)
    {
         mSeq                   = other.mSeq                   ;
         mName                  = other.mName                  ;
         mProductNum            = other.mProductNum            ;
         mLength                = other.mLength                ;
         mSpeed                 = other.mSpeed                 ;
         mMotorAccelerationTime = other. mMotorAccelerationTime;
         mWCNormalWeight        = other. mWCNormalWeight       ;
         mWCUnderWarningWeight  = other. mWCUnderWarningWeight ;
         mWCOverWarningWeight   = other. mWCOverWarningWeight  ;
         mWCUnderWeight         = other. mWCUnderWeight        ;
         mWCOverWeight          = other. mWCOverWeight         ;
         mWCTareWeight          = other. mWCTareWeight         ;
         mWCNGMotion            = other. mWCNGMotion           ;
         mWCDynamicFactor       = other. mWCDynamicFactor      ;
         mWCEnableEtcError      = other. mWCEnableEtcError     ;
         mMDSenstivity          = other. mMDSenstivity         ;
         mMDNGMotion            = other. mMDNGMotion           ;

        return *this;
    }

    bool setValue(QString value)
    {
        int findFieldCnt = 0;

        QStringList fieldList = value.split(",");

        foreach(QString field ,fieldList)
        {
            if(field.contains(":") == false)
                continue;

            int splitIdx  = field.indexOf(":");
            QString key   = field.left(splitIdx);
            QString value = field.mid(splitIdx+1);

            if     (key.contains("Seq")           ){ findFieldCnt++; mSeq                   = value.toULongLong();}
            else if(key == "No"                   ){ findFieldCnt++; mProductNum            = value.toUInt()     ;}
            else if(key == "Name"                 ){ findFieldCnt++; mName                  = value              ;}
            else if(key == "Length"               ){ findFieldCnt++; mLength                = value.toUInt()     ;}
            else if(key == "Speed"                ){ findFieldCnt++; mSpeed                 = value.toUInt()     ;}
            else if(key == "MotorAccelerationTime"){ findFieldCnt++; mMotorAccelerationTime = value.toUInt()     ;}
            else if(key == "UnderWeight"          ){ findFieldCnt++; mWCUnderWeight         = value.toUInt()     ;}
            else if(key == "UnderWarningWeight"   ){ findFieldCnt++; mWCUnderWarningWeight  = value.toUInt()     ;}
            else if(key == "NormalWeight"         ){ findFieldCnt++; mWCNormalWeight        = value.toUInt()     ;}
            else if(key == "OverWarningWeight"    ){ findFieldCnt++; mWCOverWarningWeight   = value.toUInt()     ;}
            else if(key == "OverWeight"           ){ findFieldCnt++; mWCOverWeight          = value.toUInt()     ;}
            else if(key == "TareWeight"           ){ findFieldCnt++; mWCTareWeight          = value.toUInt()     ;}
            else if(key == "WCNGMotion"           ){ findFieldCnt++; mWCNGMotion            = value.toUInt()     ;}
            else if(key == "WCEnableEtcError"     ){ findFieldCnt++; mWCEnableEtcError      = value.toUInt()     ;}
            else if(key == "DynamicFactor"        ){ findFieldCnt++; mWCDynamicFactor       = value.toUInt()     ;}
            else if(key == "MDSenstivity"         ){ findFieldCnt++; mMDSenstivity          = value.toUInt()     ;}
            else if(key == "MDNGMotion"           ){ findFieldCnt++; mMDNGMotion            = value.toUInt()     ;}
        }

        return findFieldCnt == 0 ? false : true;
    }

    QString toString(){
        QString divider = ",";

        return QString("Seq:%1%2No:%3%4Name:%5%6Length:%7%8Speed:%9%10MotorAccelerationTime:%11%12UnderWeight:%13%14UnderWarningWeight:%15%16NormalWeight:%17%18OverWarningWeight:%19%20OverWeight:%21%22TareWeight:%23%24WCNGMotion:%25%26WCEnableEtcError:%27%28DynamicFactor:%29%30MDSenstivity:%31%32MDNGMotion:%33")
                .arg(mSeq                  ).arg(divider)
                .arg(mProductNum           ).arg(divider)
                .arg(mName                 ).arg(divider)
                .arg(mLength               ).arg(divider)
                .arg(mSpeed                ).arg(divider)
                .arg(mMotorAccelerationTime).arg(divider)
                .arg(mWCUnderWeight        ).arg(divider)
                .arg(mWCUnderWarningWeight ).arg(divider)
                .arg(mWCNormalWeight       ).arg(divider)
                .arg(mWCOverWarningWeight  ).arg(divider)
                .arg(mWCOverWeight         ).arg(divider)
                .arg(mWCTareWeight         ).arg(divider)
                .arg(mWCNGMotion           ).arg(divider)
                .arg(mWCEnableEtcError     ).arg(divider)
                .arg(mWCDynamicFactor      ).arg(divider)
                .arg(mMDSenstivity         ).arg(divider)
                .arg(mMDNGMotion           );
    }
};

Q_DECLARE_METATYPE(PDSettingDto);

#endif // PDSETTINGDTO_H
