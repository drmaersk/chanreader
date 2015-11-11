#include "settingshandler.h"

SettingsHandler::SettingsHandler() :
    m_settingsFile(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + QDir::separator() +"chanReader.ini"),
    m_settings(m_settingsFile,QSettings::IniFormat)
{
    initSettings();
}

//TODO: validate settings
void SettingsHandler::initSettings()
{
    if(!QFile(m_settings.fileName()).exists())
    {
        m_settings.beginGroup("WebApi");
        m_settings.setValue("webServiceUrl", "http://a.4cdn.org/");
        m_settings.endGroup();
        m_settings.beginGroup("UserSettings");
        m_settings.setValue("currentBoard", "tv");
        m_settings.setValue("imageDirectory", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + QDir::separator() + "chanReader") ;
        m_settings.endGroup();
        m_settings.beginGroup("BoardUrl");
        m_settings.setValue("tv",  "4cdn.org/tv/");
        m_settings.setValue("b",   "4cdn.org/b/");
        m_settings.setValue("r9k", "4cdn.org/r9k/");
        m_settings.endGroup();
        //   "http://i.4cdn.org/"
    }
}

void SettingsHandler::setCurrentBoard(const QString& board)
{
    m_settings.beginGroup("UserSettings");
    m_settings.setValue("currentBoard", board);
    m_settings.endGroup();
}

QString SettingsHandler::getCurrentBoard()
{
    m_settings.beginGroup("UserSettings");
    QString currentBoard = m_settings.value("currentBoard").toString();
    m_settings.endGroup();

    return currentBoard;
}
//TODO: refactor to not have "BoardUrl" group
QString SettingsHandler::getImageUrl()
{
    QString boardKey = getCurrentBoard();
    m_settings.beginGroup("BoardUrl");
    QString currentBoardUrlSuffix = m_settings.value(boardKey).toString();
    m_settings.endGroup();

    QString currentImageUrl = "http://i." + currentBoardUrlSuffix;

    return currentImageUrl;
}

//TODO: refactor to not have "BoardUrl" group move url handling to webclient
QString SettingsHandler::getBoardUrl()
{
    QString boardKey = getCurrentBoard();
    m_settings.beginGroup("BoardUrl");
    QString currentBoardUrlSuffix = m_settings.value(boardKey).toString();
    m_settings.endGroup();

    QString currentBoardUrl = "http://a." + currentBoardUrlSuffix;

    return currentBoardUrl;
}

QString SettingsHandler::getImageDirectory()
{
    m_settings.beginGroup("UserSettings");
    QString imageDirectory = m_settings.value("imageDirectory").toString();
    m_settings.endGroup();

    return imageDirectory;
}
