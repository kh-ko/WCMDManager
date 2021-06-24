#ifndef SVCCONNECTUTIL_H
#define SVCCONNECTUTIL_H

#define ENABLE_SLOT_CORE_CHANGED_SEL_MENU          connect(CoreService::getInstance()        , SIGNAL(signalEventChangedSelMenu()              ), this, SLOT(onChangedSelMenu()                ))

#define ENABLE_SLOT_LSETTING_CHANGED_LANG          connect(LocalSettingService::getInstance(), SIGNAL(signalEventChangedLanguage()              ), this, SLOT(onChangedLanguage()              ))
#define ENABLE_SLOT_LSETTING_CHANGED_PWD           connect(LocalSettingService::getInstance(), SIGNAL(signalEventChangedPassword()              ), this, SLOT(onChangedPassword()              ))
#define ENABLE_SLOT_LSETTING_CHANGED_MONITOR_CYCLE connect(LocalSettingService::getInstance(), SIGNAL(signalEventChangedMoniteringRefreshCycle()), this, SLOT(onChangedMoniteringRefreshCycle()))
#define ENABLE_SLOT_LSETTING_CHANGED_SEL_DATE      connect(LocalSettingService::getInstance(), SIGNAL(signalEventChangedSelectDate()            ), this, SLOT(onChangedSelectDate()            ))
#define ENABLE_SLOT_LSETTING_CHANGED_SEL_DEV       connect(LocalSettingService::getInstance(), SIGNAL(signalEventChangedDeviceNumber()          ), this, SLOT(onChangedDeviceNumber()          ))
#define ENABLE_SLOT_LSETTING_CHANGED_SEL_WC_PD     connect(LocalSettingService::getInstance(), SIGNAL(signalEventChangedWCProductSeq()          ), this, SLOT(onChangedWCProductSeq()          ))
#define ENABLE_SLOT_LSETTING_CHANGED_MAN_SETTING   connect(LocalSettingService::getInstance(), SIGNAL(signalEventChangedManagerSetting()        ), this, SLOT(onChangedManagerSetting()        ))
#define ENABLE_SLOT_LSETTING_CHANGED_MD_SETTING    connect(LocalSettingService::getInstance(), SIGNAL(signalEventChangedMetalDetectorSetting()  ), this, SLOT(onChangedMetalDetectorSetting()  ))
#define ENABLE_SLOT_LSETTING_CHANGED_SIGN_SETTING  connect(LocalSettingService::getInstance(), SIGNAL(signalEventChangedSignSetting()           ), this, SLOT(onChangedSignSetting()           ))

#define ENABLE_SLOT_DLOAD_LOAD_COMPLETE            connect(DataLoaderService::getInstance()  , SIGNAL(signalEventLoadComplete()                 ), this, SLOT(onLoadComplete()                 ))
#define ENABLE_SLOT_DLOAD_CHANGED_IS_LOADING       connect(DataLoaderService::getInstance()  , SIGNAL(signalEventChangedIsLoading(bool)         ), this, SLOT(onChangedIsLoading(bool)         ))

#define ENABLE_SLOT_DINFO_CHANGED_LIMIT_CRITERIA   connect(DevInfoService::getInstance()     , SIGNAL(signalEventChangedDevMDLimit(int, QString)), this, SLOT(onChangedLimitCriteria(int, QString)))

#define ENABLE_SLOT_DEVSEARCH_COMPLETED            connect   (DevSearchService::getInstance()   , SIGNAL(signalEventCompletedSearch()              ), this, SLOT(onCompletedSearch()           ))
#define DISABLE_SLOT_DEVSEARCH_COMPLETED           disconnect(DevSearchService::getInstance()   , SIGNAL(signalEventCompletedSearch()              ), this, SLOT(onCompletedSearch()           ))
#endif // SVCCONNECTUTIL_H
