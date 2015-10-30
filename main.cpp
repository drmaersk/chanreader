#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QQmlContext>
#include <filedownloader.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    FileDownloader fd;

    engine.rootContext()->setContextProperty("fileDownloaderCpp",&fd);

    engine.load(QUrl(QStringLiteral("qrc:/4chanPrototype.qml")));

    return app.exec();
}

