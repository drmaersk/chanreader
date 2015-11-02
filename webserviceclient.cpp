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

void WebServiceClient::downloadFrontPageJson(QString board)
{
    //xhr.open("GET", "http://a.4cdn.org/tv/1.json");


    QNetworkRequest req = QNetworkRequest(QUrl("http://a.4cdn.org/tv/1.json"));
    m_WebCtrl.get(req);
}

void WebServiceClient::downloadThreadJson(QString threadNo)
{
    QNetworkRequest req = QNetworkRequest(QUrl("http://a.4cdn.org/tv/thread/"+threadNo+".json"));
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
        qDebug() << "Received array";
        qDebug() << doc.array();
    }
    else if(doc.isObject())
    {
        QJsonObject obj = doc.object();
        if(!obj["threads"].isNull())
        {
            qDebug() << "Received frontPage";
            //qDebug() << obj;
            m_currentPage = obj["threads"].toArray();
            emit(frontPageDownloaded(true));
        }
        else if(!obj["posts"].isNull())
        {
            qDebug() << "Received thread";
            //qDebug() << obj;
            m_currentThread = obj["posts"].toArray();
            emit(threadDownloaded(true));
        }
    }
    else
    {
        qDebug() << "ERROR Parsing JSON reply";
    }

}


