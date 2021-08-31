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
    Q_ENUMS(Menu)
    Q_ENUMS(ButtonColorType)
    Q_ENUMS(FileErrorType)
    Q_ENUMS(RemoteSyncErrorType)
    Q_ENUMS(RemoteSyncState)
    Q_ENUMS(FuncCode)
    Q_ENUMS(ConnectState)
    Q_ENUMS(ReportType)
    Q_ENUMS(ReportPageType)
    Q_ENUMS(MachineMode)

public:

    enum Language{
        LANG_ENG = 0,
        LANG_KOR = 1
    };

    enum SensorMode{
        SENSOR_MODE_INDEPENDENT             = 0,
        SENSOR_MODE_NOISE_REDUCTION_MODE    = 1,
        SENSOR_MODE_PARALLEL                = 2
    };

    enum NGMotion{
        NG_MOTION_NON       = 0,
        NG_MOTION_STOP      = 1,
        NG_MOTION_REJECT_01 = 2,
        NG_MOTION_REJECT_02 = 3,
    };

    enum EventType
    {
        EVENT_TYPE_NONE                         = -1,
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

    enum Menu{
        MENU_METAL_DETECTOR = 0,
        MENU_WEIGHT_CHECKER = 1,
    };

    enum ButtonColorType{
        BTN_COLOR_TYPE_DEFAULT = 0,
        BTN_COLOR_TYPE_BLUE    = 1
    };

    enum FileErrorType{
        FILE_ERROR_NONE      = 0,
        FILE_ERROR_NOT_EXIST = 1,
        FILE_ERROR_OPEN      = 2
    };

    enum RemoteSyncErrorType{
        RSYNC_ERROR_NONE            = 0,
        RSYNC_ERROR_CANCLE          = 1,
        RSYNC_ERROR_NETWORK         = 2,
        RSYNC_ERROR_FILE_INFO       = 3,
        RSYNC_ERROR_ALREADY_SYNCING = 4,
        RSYNC_ERROR_CLOSE           = 5
    };

    enum RemoteSyncState{
        RSYNC_STATE_READY           = 0,
        RSYNC_STATE_SYNCING         = 1,
        RSYNC_STATE_FINISHED        = 2
    };

    enum FuncCode{
        FUNC_CODE_INFO                  = 1,
        FUNC_CODE_RSYNC_LIST            = 2,
        FUNC_CODE_RSYNC_INIT            = 3,
        FUNC_CODE_RSYNC_ALREADY_SYNCING = 4,
        FUNC_CODE_RSYNC_FILE_INFO       = 5,
        FUNC_CODE_RSYNC_FILE_CONTENT    = 6,
        FUNC_CODE_RSYNC_COMPLETE        = 7,
        FUNC_CODE_MONITOR_STATUS        = 8
    };

    enum ConnectState{
        CONN_STATE_DISCONNECT   = 0,
        CONN_STATE_CONNECTING   = 1,
        CONN_STATE_CONNECT      = 2
    };

    enum ReportType{
        REPORT_MD_OPERATE = 0,
        REPORT_MD_CHECKUP = 1,
        REPORT_WC_OPERATE = 2
    };

    enum ReportPageType{
        REPORT_PAGE_MD_OP = 0,
        REPORT_PAGE_MD_CHECKUP = 1,
        REPORT_PAGE_MD_DETECT = 2,
        REPORT_PAGE_WC_OP = 3,
        REPORT_PAGE_WC_DETECT = 4,
    };

    enum MachineMode{
        MACHINE_MODE_ALU   = 1,
        MACHINE_MODE_WC    = 2,
        MACHINE_MODE_COMBI = 3
    };
};

#endif // ENUMDEFINE_H
