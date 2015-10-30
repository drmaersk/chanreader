#include "filedownloader.h"
#include <QtDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include "QtConcurrent/qtconcurrentrun.h"
#include <QDir>
#include <QDateTime>

FileDownloader::FileDownloader(QObject *parent) :
    QObject(parent),
    m_currentBoardDirectory("tv/"), //TODO: default == b
    m_baseDirectory("C:/tmp/"), //TODO: default??
    m_postParser(),
    m_outStandingRequests(0),
    m_receivedRequests(0),
    m_dataBaseHandler(),
    m_wc(parent)
{
    qDebug() << "Constructor";
    m_wc.getFrontPage("");//todo remove
}

QJsonArray FileDownloader::postList() const {
    return m_postList;
}



void FileDownloader::setPostList(QJsonArray n_postlist)
{
    qDebug() << "setPostList############ ";
    m_postList = n_postlist;
    QStringList images = m_postParser.getImageUrlsFromPostList(n_postlist);
    m_outStandingRequests = images.size();
    m_receivedRequests = 0;
    foreach(const QString &image, images) {
        QUrl url = "http://i.4cdn.org/tv/" +image;
        //qDebug() << url;
        download(url);
        //QFuture<void> thread = QtConcurrent::run(this, &FileDownloader::download, url);
        //thread.waitForFinished();
    }
}

QJsonValue FileDownloader::thread() const {
    return m_thread;
}

void FileDownloader::setThread(QJsonValue n_thread)
{
    qDebug() << "setThread############";
    m_thread = n_thread;
    QStringList images = m_postParser.getImageUrlsFromThread(n_thread);
    m_outStandingRequests = images.size();
    m_receivedRequests = 0;
    foreach(const QString &image, images) {
        QUrl url = "http://i.4cdn.org/tv/" +image;
        //qDebug() << url;
        download(url);
    }
}


void FileDownloader::download(QUrl imageUrl)
{
    connect(
                &m_WebCtrl, SIGNAL (finished(QNetworkReply*)),
                this, SLOT (fileDownloaded(QNetworkReply*))
                );

    QNetworkRequest request(imageUrl);
    request.setOriginatingObject(this);
    m_WebCtrl.get(request);
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    if(pReply->size() == 0) //Get multiple QNetWorkReply per request
    {
        return;
    }

    QString fileName = pReply->url().toString().split("http://i.4cdn.org/tv/")[1];
    m_DownloadedData = pReply->readAll();
    //emit a signal
    //BaseDir + boardDir + date + threadDir + filename
    //TODO: currentDirectory should be provided from controller
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString threadNo = m_postParser.getThreadNoFromImage(fileName);
    QString currentDirectory = m_baseDirectory + m_currentBoardDirectory + currentDate + QDir::separator() + threadNo + QDir::separator();

    //m_dataBaseHandler.insertThreadInDatabase("tv",currentDate,threadNo); //TODO: fix probrem now TODO: signal to controller, controller tells db
    if(!QDir(currentDirectory).exists())
    {
        QDir().mkpath(currentDirectory);
    }

    QFile file(currentDirectory +fileName);

    if(!file.exists())
    {
        file.open(QIODevice::WriteOnly);
        file.write(m_DownloadedData);
        file.close();
    }

    ++m_receivedRequests;
    int percent = ((double)m_receivedRequests) / ((double)m_outStandingRequests) * 100.0;
    //qDebug() << "Outstanding requests == " << m_outStandingRequests << " Progress: " << percent << "%";
    if(m_outStandingRequests == m_receivedRequests)
    {
        qDebug() << "Got them all";
        emit filesDownloaded();
    }
    pReply->deleteLater();
}

QString FileDownloader::baseDirectory() const
{
    return m_baseDirectory;
}

void FileDownloader::setBaseDirectory(const QString &baseDirectory)
{
    m_baseDirectory = baseDirectory;
}

QString FileDownloader::currentBoardDirectory() const
{
    return m_currentBoardDirectory;
}

void FileDownloader::setCurrentBoardDirectory(const QString &currentBoard)
{
    m_currentBoardDirectory = currentBoard;
}


