#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QQmlContext>
#include <controller.h>

int main(int argc, char *argv[])
{
    //TODO: see if you can fix ssl instead of hiding problem
    qputenv("QT_LOGGING_RULES", "qt.network.ssl.warning=false");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Controller c;

    engine.rootContext()->setContextProperty("controllerCpp",&c);

    engine.load(QUrl(QStringLiteral("qrc:/4chanPrototype.qml")));

    return app.exec();
}

