#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent),
    m_postParser(),
    m_dataBaseHandler(),
    m_wc(parent),
    m_currentFrontPage(),
    m_currentThread(),
    m_settings()
{
    connect(&m_wc,
            SIGNAL (threadDownloaded(bool)),
            this,
            SLOT (threadDownloaded(bool)));
    connect(&m_wc,
            SIGNAL (frontPageDownloaded(bool)),
            this,
            SLOT (frontPageDownloaded(bool)));
    m_settings.setCurrentBoard("tv");
    qDebug() << m_settings.getBoardUrl();

}

void Controller::downloadFrontPage()
{
    m_wc.downloadFrontPageJson(m_settings.getBoardUrl());//TODO: take argument from settings
}

void Controller::downloadThread(QString threadId)
{
    qDebug() << "downloadThread";
    m_wc.downloadThreadJson(m_settings.getBoardUrl(), threadId);
}

QJsonArray Controller::getFrontPage()
{
    return m_currentFrontPage;
}

QJsonArray Controller::getThread()
{
    return m_currentThread;
}

QString Controller::currentBoard()
{
    return m_settings.getCurrentBoard();
}

void Controller::setCurrentBoard(const QString &currentBoard)
{

}

QString Controller::baseDirectory() const
{
    return "todo";
}

void Controller::setBaseDirectory(const QString &baseDirectory)
{

}

QString Controller::boardUrl()
{
    QString boardUrl = m_settings.getBoardUrl();
    return boardUrl;
}

QString Controller::imageUrl()
{
    QString boardUrl = m_settings.getImageUrl();
    return boardUrl;
}

void Controller::threadDownloaded(bool success)
{
    if(success)
    {
        m_currentThread = m_wc.getThreadJson();
        //qDebug() << m_postParser.getImageUrlsFromThread(m_currentThread);
        emit threadDownloaded();
    }
}

void Controller::frontPageDownloaded(bool success)
{
    if(success)
    {
        m_currentFrontPage = m_wc.getFrontPageJson();
        qDebug() << m_postParser.getImageUrlsFromFrontPage(m_currentFrontPage);
        ThreadDownloader* td = new ThreadDownloader(this);
        connect(td,
                &ThreadDownloader::finished,
                td,
                &QObject::deleteLater);
        td->start();
        emit frontPageDownloaded();
    }
}
