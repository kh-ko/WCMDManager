#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2/QQuickStyle>

#include "source/globaldef/EnumDefine.h"
#include "source/qmlmodel/samplemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
	
	qmlRegisterUncreatableType<EnumDefine>("EnumDefine", 1, 0, "EnumDefine", "");
	
    qmlRegisterType<SampleModel>("SampleModel", 1, 0, "SampleModel");

	qmlRegisterSingletonType(QUrl("qrc:/uiengine/ViewManager.qml"), "ViewManager", 1, 0, "ViewManager");
    qmlRegisterSingletonType(QUrl("qrc:/uiengine/FontManager.qml"), "FontManager", 1, 0, "FontManager");
	
    engine.load(url);

    return app.exec();
}
