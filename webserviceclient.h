#ifndef WEBSERVICECLIENT_H
#define WEBSERVICECLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

class WebServiceClient : public QObject
{
    Q_OBJECT
public:
    WebServiceClient(QObject *parent = 0);
    void downloadThreadJson(QString boardUrl, QString threadNo);
    void downloadFrontPageJson(QString boardUrl);

    QJsonArray getFrontPageJson();
    QJsonArray getThreadJson();

signals:
 Q_SIGNAL void frontPageDownloaded(bool success);
 Q_SIGNAL void threadDownloaded(bool success);

private slots:
    void downloadFinished(QNetworkReply* pReply);
private:
    QNetworkAccessManager m_WebCtrl;
    QJsonArray m_currentPage;
    QJsonArray m_currentThread;
};

#endif // WEBSERVICECLIENT_H
