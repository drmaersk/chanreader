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

}

void Controller::downloadFrontPage()
{
  qDebug() << "downloadFrontPage";
  QThread::sleep(10);
  emit frontPageDownloaded();
}

void Controller::downloadThread(QString threadId)
{
  qDebug() << "downloadThread";
  emit threadDownloaded();
}

QJsonArray Controller::getFrontPage()
{
    return m_currentFrontPage;
}

QJsonValue Controller::getThread()
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

}

void Controller::frontPageDownloaded(bool success)
{

}
