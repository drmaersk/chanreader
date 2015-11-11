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
    static const QString URL_PREFIX_WEB_SERVICE_HTTP;
    static const QString URL_PREFIX_WEB_SERVICE_HTTPS;
    static const QString URL_PREFIX_IMAGE_HTTP;
    static const QString URL_PREFIX_IMAGE_HTTPS;

    WebServiceClient(QObject *parent = 0);
    void downloadThreadJson(QString board, QString threadNo);
    void downloadFrontPageJson(QString board);

    QVector<QJsonArray> getFrontPageJson();
    QJsonArray getThreadJson();

signals:
 Q_SIGNAL void frontPageJsonDownloaded(bool success);
 Q_SIGNAL void threadJsonDownloaded(bool success);

private slots:
    void downloadFinished(QNetworkReply* pReply);
private:
    QNetworkAccessManager m_WebCtrl;
    QVector<QJsonArray> m_currentFrontPage;
    uint32_t m_currentFrontPageRequests;
    QJsonArray m_currentThread;
};

#endif // WEBSERVICECLIENT_H
