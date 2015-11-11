#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H
#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QDebug>

class SettingsHandler
{
public:
    static SettingsHandler *getSettingsHandler();
    void initSettings();
    void setCurrentBoard(const QString &board);
    QString getCurrentBoard();
    QString getBoardUrl();
    QString getImageUrl();
    QString getImageDirectory();
private:
    static SettingsHandler *m_settingsHandler;
    QString m_settingsFile;
    QSettings m_settings;
    SettingsHandler();
    SettingsHandler(SettingsHandler const&)               = delete;
    void operator=(SettingsHandler const&)  = delete;
};

#endif // SETTINGSHANDLER_H
