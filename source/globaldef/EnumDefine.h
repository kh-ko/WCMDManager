#ifndef ENUMDEFINE_H
#define ENUMDEFINE_H

#include <QObject>
class EnumDefine: public QObject{
  Q_OBJECT
  Q_ENUMS(Language)
  Q_ENUMS(SensorMode)
  Q_ENUMS(NGMotion)
  Q_ENUMS(EventType)
  Q_ENUMS(Company)


public:

  enum Language{
    LANG_ENG = 0,
    LANG_KOR = 1
  };

  enum SensorMode{
    SENSOR_MODE_INDEPENDENT = 0,
    SENSOR_MODE_NOISE_REDUCTION_MODE = 1,
    SENSOR_MODE_PARALLEL = 2
  };

  enum NGMotion{
      NG_MOTION_NON = 0,
      NG_MOTION_STOP = 1,
      NG_MOTION_REJECT_01 = 2,
      NG_MOTION_REJECT_02 = 3,
  };

  enum EventType
  {
      EVENT_TYPE_NONE                   = -1,
      EVENT_TYPE_WEIGHT_NORMAL                = 0,
      EVENT_TYPE_WEIGHT_UNDER_WARNING         = 1,
      EVENT_TYPE_WEIGHT_OVER_WARNING          = 2,
      EVENT_TYPE_WEIGHT_UNDER                 = 3,
      EVENT_TYPE_WEIGHT_OVER                  = 4,
      EVENT_TYPE_WEIGHT_ETCERROR              = 5,
      EVENT_TYPE_APP_START                    = 6,
      EVENT_TYPE_APP_EXIT                     = 7,
      EVENT_TYPE_METAL_CHECKUP                = 8,
      EVENT_TYPE_WEIGHT_STATIC_CARI           = 9,
      EVENT_TYPE_WEIGHT_DYNAMIC_CARI          = 10,
      EVENT_TYPE_RUN                          = 11,
      EVENT_TYPE_STOP                         = 12,
      EVENT_TYPE_METAL_PASS                   = 13,
      EVENT_TYPE_METAL_NG                     = 14,
      EVENT_TYPE_CHECK_METAL_NONE_DETECT      = 15,
      EVENT_TYPE_CHECK_METAL_DETECT           = 16,
      EVENT_TYPE_WEIGHT_CALIB_NORMAL          = 17,
      EVENT_TYPE_WEIGHT_CALIB_UNDER_WARNING   = 18,
      EVENT_TYPE_WEIGHT_CALIB_OVER_WARNING    = 19,
      EVENT_TYPE_WEIGHT_CALIB_UNDER           = 20,
      EVENT_TYPE_WEIGHT_CALIB_OVER            = 21,
      EVENT_TYPE_WEIGHT_CALIB_ETCERROR        = 22,
      EVENT_TYPE_WEIGHT_ETC_METAL_ERROR       = 23
  };


  enum Company{
      COMPANY_NOVASEN = 0,
      COMPANY_DONGNAM = 1
  };
};

#endif // ENUMDEFINE_H
