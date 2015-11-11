#include "webserviceclient.h"

const QString WebServiceClient::URL_PREFIX_WEB_SERVICE_HTTP = "http://a.4cdn.org/";
const QString WebServiceClient::URL_PREFIX_WEB_SERVICE_HTTPS = "https://a.4cdn.org/";
const QString WebServiceClient::URL_PREFIX_IMAGE_HTTP = "http://i.4cdn.org/";
const QString WebServiceClient::URL_PREFIX_IMAGE_HTTPS = "https://i.4cdn.org/";


WebServiceClient::WebServiceClient(QObject *parent) :
    QObject(parent),
    m_WebCtrl(),
    m_currentFrontPage(),
    m_currentFrontPageRequests(0),
    m_currentThread()
{
    connect(&m_WebCtrl,
            SIGNAL (finished(QNetworkReply*)),
            this,
            SLOT (downloadFinished(QNetworkReply*)));
}

void WebServiceClient::downloadFrontPageJson(QString board)
{
    m_currentFrontPageRequests = 1; //TODO: set programatically

    for(int i = 1; i <= 1; i++) //TODO: set programatically
    {
        QString currentPage = QString::number(i);
        QNetworkRequest req = QNetworkRequest(QUrl(URL_PREFIX_WEB_SERVICE_HTTP+board+"/"+currentPage+".json"));
        qDebug() << URL_PREFIX_WEB_SERVICE_HTTP+board+"/"+currentPage+".json";
        m_WebCtrl.get(req);
    }
}

void WebServiceClient::downloadThreadJson(QString board, QString threadNo)
{
    QNetworkRequest req = QNetworkRequest(QUrl(URL_PREFIX_WEB_SERVICE_HTTP+board+"/thread/"+threadNo+".json"));
    m_WebCtrl.get(req);
}

QVector<QJsonArray> WebServiceClient::getFrontPageJson() //TODO: take page number
{
    return m_currentFrontPage;
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
            m_currentFrontPage.push_back(obj["threads"].toArray());
            --m_currentFrontPageRequests;
            qDebug() << m_currentFrontPageRequests;
            if(m_currentFrontPageRequests == 0)
            {
                qDebug() << "All page requests done";
                emit(frontPageJsonDownloaded(true));
            }
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


