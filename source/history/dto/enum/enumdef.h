#ifndef ENUMDEF_H
#define ENUMDEF_H
#include <QObject>

class EnumDef: public QObject{
    Q_OBJECT
    Q_ENUMS(eLang)
    Q_ENUMS(eEventType)
    Q_ENUMS(eDailyErr)
    Q_ENUMS(eDailyKind)

public:
    enum eLang{
        LANG_ENG = 0,
        LANG_KOR = 1
    };

    enum eEventType
    {
        ET_NONE                         = -1,
        ET_WEIGHT_NORMAL                = 0,
        ET_WEIGHT_UNDER_WARNING         = 1,
        ET_WEIGHT_OVER_WARNING          = 2,
        ET_WEIGHT_UNDER                 = 3,
        ET_WEIGHT_OVER                  = 4,
        ET_WEIGHT_ETCERROR              = 5,
        ET_APP_START                    = 6,
        ET_APP_EXIT                     = 7,
        ET_METAL_CHECKUP                = 8,
        ET_WEIGHT_STATIC_CARI           = 9,
        ET_WEIGHT_DYNAMIC_CARI          = 10,
        ET_RUN                          = 11,
        ET_STOP                         = 12,
        ET_METAL_TRADE                  = 13,
        ET_METAL_DETECT                 = 14,
        ET_METAL_TRADE_CHECK            = 15,
        ET_METAL_DETECT_CHECK           = 16,
        ET_WEIGHT_NORMAL_CHECK          = 17,
        ET_WEIGHT_UNDER_WARNING_CHECK   = 18,
        ET_WEIGHT_OVER_WARNING_CHECK    = 19,
        ET_WEIGHT_UNDER_CHECK           = 20,
        ET_WEIGHT_OVER_CHECK            = 21,
        ET_WEIGHT_ETCERROR_CHECK        = 22,
        ET_WEIGHT_ETC_METAL_ERROR       = 23
    };

    enum eDailyErr{
        DAILY_ERR_NONE = 0,
    };

    enum eDailyKind{
        DAILY_PH = 0,
        DAILY_PS = 1,
        DAILY_EH = 2,
        DAILY_CH = 3,
    };
};
#endif // ENUMDEF_H
