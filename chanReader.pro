TEMPLATE = app

QT += qml quick network sql
CONFIG += c++11

SOURCES += main.cpp \
    filedownloader.cpp \
    postparser.cpp \
    databasehandler.cpp \
    webserviceclient.cpp \
    controller.cpp \
    settingshandler.cpp

RESOURCES += qml.qrc

RC_FILE = pepe.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    filedownloader.h \
    postparser.h \
    databasehandler.h \
    webserviceclient.h \
    controller.h \
    settingshandler.h \
    threaddata.h

DISTFILES +=


