#include "webserviceclient.h"

WebServiceClient::WebServiceClient(QObject *parent) :
    QObject(parent),
    m_WebCtrl()
{

}

QJsonArray WebServiceClient::getFrontPage(QString board)
{
    //xhr.open("GET", "http://a.4cdn.org/tv/1.json");
    connect(&m_WebCtrl,
            SIGNAL (finished(QNetworkReply*)),
            this,
            SLOT (frontPageDownloaded(QNetworkReply*)));

    QNetworkRequest req = QNetworkRequest(QUrl("http://a.4cdn.org/tv/1.json"));
    m_WebCtrl.get(req);
    QJsonArray array;
    return array;
}

void WebServiceClient::frontPageDownloaded(QNetworkReply* pReply)
{
    qDebug() << "frontPageDownloaded";
    if(pReply->size() == 0) //Get multiple QNetWorkReply per request
    {
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(pReply->readAll());

    if(doc.isObject())
    {
        qDebug() << doc.object();
    }
    else if(doc.isArray())
    {
        qDebug() << doc.array();
    }
    else{
        qDebug() << "ERROR Parsing JSON reply";
    }

}
