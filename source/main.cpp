#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2/QQuickStyle>

#include "source/globaldef/EnumDefine.h"
#include "source/logger/nsdebug.h"
#include "source/qmlmodel/dialogpasswordmodel.h"
#include "source/qmlmodel/mainmodel.h"
#include "source/qmlmodel/panelmetalmanagementmodel.h"
#include "source/qmlmodel/panelmetalcheckuphistorymodel.h"
#include "source/qmlmodel/panelmetaloperatehistorymodel.h"
#include "source/qmlmodel/panelmetalstatisticsmodel.h"
#include "source/qmlmodel/panelmetaldetecthistorymodel.h"
#include "source/qmlmodel/panelCalendarModel.h"
#include "source/qmlmodel/panelsyncmodel.h"
#include "source/qmlmodel/panelmonitorlistmodel.h"
#include "source/qmlmodel/panelmonitoritemmodel.h"
#include "source/qmlmodel/panelmdopreportcontainermodel.h"
#include "source/qmlmodel/panelmdopreportmodel.h"
#include "source/qmlmodel/panelmdopreportrowmodel.h"
#include "source/qmlmodel/panelmdcheckreportcontainermodel.h"
#include "source/qmlmodel/panelmdcheckreportmodel.h"
#include "source/qmlmodel/panelmdcheckreportrowmodel.h"
#include "source/qmlmodel/panelwcreportcontainermodel.h"
#include "source/qmlmodel/panelwcreportmodel.h"
#include "source/qmlmodel/panelwcreportproductmodel.h"
#include "source/qmlmodel/windowsettingmodel.h"
#include "source/qmlmodel/panelweightmanagementinfomodel.h"
#include "source/qmlmodel/panelwcselectdeviceproduct.h"
#include "source/qmlmodel/panelwcproductsummary.h"
#include "source/qmlmodel/panelwchistogram.h"
#include "source/qmlmodel/panelwctrendsmodel.h"
#include "source/util/mouseeventspy.h"

int main(int argc, char *argv[])
{
    int resultExec = 0;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
	
	qmlRegisterUncreatableType<EnumDefine>("EnumDefine", 1, 0, "EnumDefine", "");


    qmlRegisterType<DialogPasswordModel             >("DialogPasswordModel"             , 1, 0, "DialogPasswordModel"             );
    qmlRegisterType<MainModel                       >("MainModel"                       , 1, 0, "MainModel"                       );
    qmlRegisterType<PanelMetalManagementInfoModel   >("PanelMetalManagementInfoModel"   , 1, 0, "PanelMetalManagementInfoModel"   );
    qmlRegisterType<PanelMetalCheckupHistoryModel   >("PanelMetalCheckupHistoryModel"   , 1, 0, "PanelMetalCheckupHistoryModel"   );
    qmlRegisterType<PanelMetalOperateHistoryModel   >("PanelMetalOperateHistoryModel"   , 1, 0, "PanelMetalOperateHistoryModel"   );
    qmlRegisterType<PanelMetalStatisticsModel       >("PanelMetalStatisticsModel"       , 1, 0, "PanelMetalStatisticsModel"       );
    qmlRegisterType<PanelMetalDetectHistoryModel    >("PanelMetalDetectHistoryModel"    , 1, 0, "PanelMetalDetectHistoryModel"    );
    qmlRegisterType<PanelWCSelectDeviceProductModel >("PanelWCSelectDeviceProductModel" , 1, 0, "PanelWCSelectDeviceProductModel" );
    qmlRegisterType<PanelWeightManagementInfoModel  >("PanelWeightManagementInfoModel"  , 1, 0, "PanelWeightManagementInfoModel"  );
    qmlRegisterType<PanelWCProductSummaryModel      >("PanelWCProductSummaryModel"      , 1, 0, "PanelWCProductSummaryModel"      );
    qmlRegisterType<PanelWCHistogramModel           >("PanelWCHistogramModel"           , 1, 0, "PanelWCHistogramModel"           );
    qmlRegisterType<PanelCalendarModel              >("PanelCalendarModel"              , 1, 0, "PanelCalendarModel"              );
    qmlRegisterType<PanelSyncModel                  >("PanelSyncModel"                  , 1, 0, "PanelSyncModel"                  );
    qmlRegisterType<PanelSyncListItemModel          >("PanelSyncListItemModel"          , 1, 0, "PanelSyncListItemModel"          );
    qmlRegisterType<PanelMonitorListModel           >("PanelMonitorListModel"           , 1, 0, "PanelMonitorListModel"           );
    qmlRegisterType<PanelMonitorItemModel           >("PanelMonitorItemModel"           , 1, 0, "PanelMonitorItemModel"           );
    qmlRegisterType<PanelMDOPReportContainerModel   >("PanelMDOPReportContainerModel"   , 1, 0, "PanelMDOPReportContainerModel"   );
    qmlRegisterType<PanelMDOPReportModel            >("PanelMDOPReportModel"            , 1, 0, "PanelMDOPReportModel"            );
    qmlRegisterType<PanelMDOPReportRowModel         >("PanelMDOPReportRowModel"         , 1, 0, "PanelMDOPReportRowModel"         );
    qmlRegisterType<PanelMDCheckReportContainerModel>("PanelMDCheckReportContainerModel", 1, 0, "PanelMDCheckReportContainerModel");
    qmlRegisterType<PanelMDCheckReportModel         >("PanelMDCheckReportModel"         , 1, 0, "PanelMDCheckReportModel"         );
    qmlRegisterType<PanelMDCheckReportRowModel      >("PanelMDCheckReportRowModel"      , 1, 0, "PanelMDCheckReportRowModel"      );
    qmlRegisterType<PanelWCReportContainerModel     >("PanelWCReportContainerModel"     , 1, 0, "PanelWCReportContainerModel"     );
    qmlRegisterType<PanelWCReportModel              >("PanelWCReportModel"              , 1, 0, "PanelWCReportModel"              );
    qmlRegisterType<PanelWCReportProductModel       >("PanelWCReportProductModel"       , 1, 0, "PanelWCReportProductModel"       );
    qmlRegisterType<PanelWCTrendsModel              >("PanelWCTrendsModel"              , 1, 0, "PanelWCTrendsModel"              );
    qmlRegisterType<WindowSettingModel              >("WindowSettingModel"              , 1, 0, "WindowSettingModel"              );

	qmlRegisterSingletonType(QUrl("qrc:/uiengine/ViewManager.qml"), "ViewManager", 1, 0, "ViewManager");
    qmlRegisterSingletonType(QUrl("qrc:/uiengine/FontManager.qml"), "FontManager", 1, 0, "FontManager");
	
    qmlRegisterSingletonType<MouseEventSpy>("MouseEventSpy", 1, 0, "MouseEventSpy", MouseEventSpy::singletonProvider);

    NSDebug::startService();
    qInstallMessageHandler(NSDebug::debugMessageHandler);

    engine.load(url);

    resultExec = app.exec();

    qInstallMessageHandler(nullptr);
    NSDebug::stopService();

    return resultExec;
}
