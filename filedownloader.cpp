#include "filedownloader.h"
#include <QtDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>
#include <QDateTime>
#include "webserviceclient.h"

FileDownloader::FileDownloader(QObject *parent,
                               const QString baseUrl,
                               const QString fileName,
                               const QString pathToSave) :
    QObject(parent),
    m_baseUrl(baseUrl),
    m_fileName(fileName),
    m_saveDirectory(pathToSave)
{
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
    m_WebCtrl.get(request);
}

void FileDownloader::downloadFile(QString baseUrl, QString fileName, QString pathToSave)
{
    m_baseUrl = baseUrl;
    QString url = baseUrl+fileName;
    m_fileUrl.setUrl(url);
    m_fileName = fileName;
    m_saveDirectory = pathToSave;
    download();
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    if(pReply->size() == 0) //Get multiple QNetWorkReply per request
    {
        return;
    }

    m_DownloadedData = pReply->readAll();

    if(!QDir(m_saveDirectory).exists())
    {
        QDir().mkpath(m_saveDirectory);
    }

    QFile file(m_saveDirectory + m_fileName);

    if(!file.exists())
    {
        file.open(QIODevice::WriteOnly);
        file.write(m_DownloadedData);
        file.close();
    }

    emit fileSaved(m_fileName, m_saveDirectory);
    pReply->deleteLater();
}

