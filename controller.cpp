#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent),
    m_currentBoardDirectory("tv"),
    m_baseDirectory("C:/tmp"),
    m_postParser(),
    m_dataBaseHandler(),
    m_wc(parent),
    m_currentFrontPage(),
    m_currentThread()
{
    connect(&m_wc,
            SIGNAL (threadDownloaded(bool)),
            this,
            SLOT (threadDownloaded(bool)));
    connect(&m_wc,
            SIGNAL (frontPageDownloaded(bool)),
            this,
            SLOT (frontPageDownloaded(bool)));
}

void Controller::downloadFrontPage()
{
    qDebug() << "downloadFrontPage";
    m_wc.downloadFrontPageJson("");//TODO: take argument from settings
}

void Controller::downloadThread(QString threadId)
{
    qDebug() << "downloadThread";
    m_wc.downloadThreadJson(threadId);
}

QJsonArray Controller::getFrontPage()
{
    return m_currentFrontPage;
}

QJsonArray Controller::getThread()
{
    return m_currentThread;
}

QString Controller::currentBoardDirectory() const
{
    return "todo";
}

void Controller::setCurrentBoardDirectory(const QString &currentBoardDirectory)
{

}

QString Controller::baseDirectory() const
{
    return "todo";
}

void Controller::setBaseDirectory(const QString &baseDirectory)
{

}

void Controller::threadDownloaded(bool success)
{
    if(success)
    {
        m_currentThread = m_wc.getThreadJson();
        emit threadDownloaded();
    }
}

void Controller::frontPageDownloaded(bool success)
{
    if(success)
    {
        m_currentFrontPage = m_wc.getFrontPageJson();
        emit frontPageDownloaded();
    }
}
