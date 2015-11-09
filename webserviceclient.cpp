#include "webserviceclient.h"

WebServiceClient::WebServiceClient(QObject *parent) :
    QObject(parent),
    m_WebCtrl(),
    m_currentPage(),
    m_currentThread()
{
    connect(&m_WebCtrl,
            SIGNAL (finished(QNetworkReply*)),
            this,
            SLOT (downloadFinished(QNetworkReply*)));
}

void WebServiceClient::downloadFrontPageJson(QString boardUrl)
{
    QNetworkRequest req = QNetworkRequest(QUrl(boardUrl+"1.json"));
    m_WebCtrl.get(req);
}

void WebServiceClient::downloadThreadJson(QString boardUrl, QString threadNo)
{
    QNetworkRequest req = QNetworkRequest(QUrl(boardUrl+"thread/"+threadNo+".json"));
    m_WebCtrl.get(req);
}

QJsonArray WebServiceClient::getFrontPageJson()
{
    return m_currentPage;
}

QJsonArray WebServiceClient::getThreadJson()
{
    return m_currentThread;
}

void WebServiceClient::downloadFinished(QNetworkReply* pReply)
{
    qDebug() << "Network reply received";
    if(pReply->size() == 0) //Get multiple QNetWorkReply per request
    {
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(pReply->readAll());

    if(doc.isArray())
    {
        qDebug() << "ERROR: Received array";

    }
    else if(doc.isObject())
    {
        QJsonObject obj = doc.object();
        if(!obj["threads"].isNull())
        {
            m_currentPage = obj["threads"].toArray();
            emit(frontPageJsonDownloaded(true));
        }
        else if(!obj["posts"].isNull())
        {
            m_currentThread = obj["posts"].toArray();
            emit(threadJsonDownloaded(true));
        }
    }
    else
    {
        qDebug() << "ERROR Parsing JSON reply";
    }

}


