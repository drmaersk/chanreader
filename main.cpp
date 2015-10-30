#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QQmlContext>
#include <controller.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Controller c;

    engine.rootContext()->setContextProperty("controllerCpp",&c);

    engine.load(QUrl(QStringLiteral("qrc:/4chanPrototype.qml")));

    return app.exec();
}

