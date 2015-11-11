#include "webserviceclient.h"

const QString WebServiceClient::URL_PREFIX_WEB_SERVICE_HTTP = "http://a.4cdn.org/";
const QString WebServiceClient::URL_PREFIX_WEB_SERVICE_HTTPS = "https://a.4cdn.org/";
const QString WebServiceClient::URL_PREFIX_IMAGE_HTTP = "http://i.4cdn.org/";
const QString WebServiceClient::URL_PREFIX_IMAGE_HTTPS = "https://i.4cdn.org/";


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
    QNetworkRequest req = QNetworkRequest(QUrl(URL_PREFIX_WEB_SERVICE_HTTP+board+"/1.json"));
    qDebug() << URL_PREFIX_WEB_SERVICE_HTTP<<board<<"/1.json";
    m_WebCtrl.get(req);
}

void WebServiceClient::downloadThreadJson(QString board, QString threadNo)
{
    QNetworkRequest req = QNetworkRequest(QUrl(URL_PREFIX_WEB_SERVICE_HTTP+board+"/thread/"+threadNo+".json"));
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
    qDebug() << "Network reply saved";
}


