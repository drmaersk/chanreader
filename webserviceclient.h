#ifndef WEBSERVICECLIENT_H
#define WEBSERVICECLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

class WebServiceClient : public QObject
{
    Q_OBJECT
public:
    WebServiceClient(QObject *parent = 0);
    QJsonArray getFrontPage(QString board);


private slots:
    void frontPageDownloaded(QNetworkReply* pReply);
private:
    QNetworkAccessManager m_WebCtrl;
};

#endif // WEBSERVICECLIENT_H
