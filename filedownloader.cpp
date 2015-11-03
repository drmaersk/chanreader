#include "filedownloader.h"
#include <QtDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include "QtConcurrent/qtconcurrentrun.h"
#include <QDir>
#include <QDateTime>

FileDownloader::FileDownloader(QObject *parent,
                               const QString baseUrl,
                               const QString fileName,
                               const QString directory) :
    QObject(parent),
    m_baseUrl(baseUrl),
    m_fileName(fileName),
    m_currentDirectory(directory) //TODO: default??
{
    qDebug() << "Constructor";
    QString url = baseUrl+fileName;
    m_fileUrl.setUrl(url);
    connect(&m_WebCtrl,
            SIGNAL (finished(QNetworkReply*)),
            this,
            SLOT (fileDownloaded(QNetworkReply*)));
}


void FileDownloader::download()
{
    QNetworkRequest request(m_fileUrl);
    request.setOriginatingObject(this);
    m_WebCtrl.get(request);
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    if(pReply->size() == 0 || pReply->request().originatingObject() != this) //Get multiple QNetWorkReply per request
    {
        return;
    }

    m_DownloadedData = pReply->readAll();

    if(!QDir(m_currentDirectory).exists())
    {
        QDir().mkpath(m_currentDirectory);
    }

    QFile file(m_currentDirectory +m_fileName);

    if(!file.exists())
    {
        file.open(QIODevice::WriteOnly);
        file.write(m_DownloadedData);
        file.close();
    }

    emit fileSaved();
    pReply->deleteLater();
}

