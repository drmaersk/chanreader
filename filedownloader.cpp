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
    m_outStandingRequests(0),
    m_receivedRequests(0)
{
    qDebug() << "Constructor";
    connect(&m_WebCtrl,
            SIGNAL (finished(QNetworkReply*)),
            this,
            SLOT (fileDownloaded(QNetworkReply*)));
}


void FileDownloader::downloadFiles(QStringList fileNames)
{
    m_outStandingRequests = fileNames.size();
    m_receivedRequests = 0;
    foreach(const QString &fileName, fileNames) {
        QUrl url = "http://i.4cdn.org/tv/" +fileName;
        download(url);
    }
}

void FileDownloader::download(QUrl imageUrl)
{
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
    QString threadNo;//TODO:
    QString currentDirectory = m_baseDirectory + m_currentBoardDirectory + currentDate + QDir::separator() + threadNo + QDir::separator();

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

void FileDownloader::setBaseDirectory(const QString &baseDirectory)
{
    m_baseDirectory = baseDirectory;
}

void FileDownloader::setCurrentBoardDirectory(const QString &currentBoard)
{
    m_currentBoardDirectory = currentBoard;
}


