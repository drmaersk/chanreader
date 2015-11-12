#include "filedownloader.h"
#include <QtDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>
#include <QDateTime>
#include "webserviceclient.h"

FileDownloader::FileDownloader(QObject *parent) :
    QObject(parent),
    m_baseUrl(""),
    m_fileName(""),
    m_saveDirectory(""),
    m_fileUrl("")
{

}


void FileDownloader::download()
{
    m_WebCtrl = new QNetworkAccessManager();
    QNetworkRequest request(m_fileUrl);


    connect(m_WebCtrl,
            SIGNAL (finished(QNetworkReply*)),
            this,
            SLOT (fileDownloaded(QNetworkReply*)));

    request.setOriginatingObject(this);
    m_WebCtrl->get(request);
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

    if(pReply->request().originatingObject() != this)
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

