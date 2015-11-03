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
    SettingsHandler();
    void initSettings();
    void setCurrentBoard(const QString &board);
    QString getCurrentBoard();
    QString getBoardUrl();
    QString getImageUrl();
private:
    QString m_settingsFile;
    QSettings m_settings;
};

#endif // SETTINGSHANDLER_H
