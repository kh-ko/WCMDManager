QT += quick widgets network printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use  teststssss
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/helper/languagehelper.cpp \
        source/logger/nsdebug.cpp \
        source/main.cpp \
        source/service/coreservice.cpp \
        source/service/dataloaderservice.cpp \
        source/service/dspsearchservice.cpp \
        source/service/localsettingservice.cpp \
        source/service/metaldetectorservice.cpp \
        source/service/productstatisticsservice.cpp \
        source/service/weightcheckerservice.cpp \
        source/thread/deviceinfocollector.cpp \
        source/thread/remotehistorydatasyncer.cpp \
        source/util/fileloaderthread.cpp \
        source/util/filewriter.cpp \
        source/util/mouseeventspy.cpp \
        source/util/myalloc.cpp

RESOURCES += qml/qml.qrc
RC_FILE = WCMDManager_resource.rc

TRANSLATIONS += Lang_ko_KR.ts
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
#target.path = C:/Work/02.AluScanWeightCheckerIntegratedTouch/04.Source/20201009-v-1-2-0/WCMDManager/$${TARGET}
#INSTALLS += target

HEADERS += \
    source/globaldef/EnumDefine.h \
    source/helper/languagehelper.h \
    source/logger/nsdebug.h \
    source/model/deviceinfolistmodel.h \
    source/model/deviceinfomodel.h \
    source/model/eventitemmodel.h \
    source/model/managersettingmodel.h \
    source/model/mdcheckupitemmodel.h \
    source/model/mddetectitemmodel.h \
    source/model/metaldetectorsettingmodel.h \
    source/model/productsettingmodel.h \
    source/model/productstatisticsmodel.h \
    source/model/signsettingmodel.h \
    source/model/weightcheckermodel.h \
    source/model/weightcheckersettingmodel.h \
    source/qmlmodel/dialogpasswordmodel.h \
    source/qmlmodel/mainmodel.h \
    source/qmlmodel/panelCalendarModel.h \
    source/qmlmodel/panelmdcheckreportcontainermodel.h \
    source/qmlmodel/panelmdcheckreportmodel.h \
    source/qmlmodel/panelmdcheckreportrowmodel.h \
    source/qmlmodel/panelmdopreportcontainermodel.h \
    source/qmlmodel/panelmdopreportmodel.h \
    source/qmlmodel/panelmdopreportrowmodel.h \
    source/qmlmodel/panelmetalcheckuphistorymodel.h \
    source/qmlmodel/panelmetaldetecthistorymodel.h \
    source/qmlmodel/panelmetalmanagementmodel.h \
    source/qmlmodel/panelmetaloperatehistorymodel.h \
    source/qmlmodel/panelmetalstatisticsmodel.h \
    source/qmlmodel/panelmonitoritemmodel.h \
    source/qmlmodel/panelmonitorlistmodel.h \
    source/qmlmodel/panelsynclistitemmodel.h \
    source/qmlmodel/panelsyncmodel.h \
    source/qmlmodel/panelwchistogram.h \
    source/qmlmodel/panelwcproductsummary.h \
    source/qmlmodel/panelwcselectdeviceproduct.h \
    source/qmlmodel/panelwctrendsmodel.h \
    source/qmlmodel/windowsettingmodel.h \
    source/service/coreservice.h \
    source/service/dataloaderservice.h \
    source/service/dspsearchservice.h \
    source/service/localsettingservice.h \
    source/service/metaldetectorservice.h \
    source/service/productstatisticsservice.h \
    source/service/weightcheckerservice.h \
    source/thread/deviceinfocollector.h \
    source/thread/dto/deviceinfodto.h \
    source/thread/dto/devicesocketdto.h \
    source/thread/remotehistorydatasyncer.h \
    source/util/fileloaderthread.h \
    source/util/filewriter.h \
    source/util/mouseeventspy.h \
    source/util/myalloc.h
