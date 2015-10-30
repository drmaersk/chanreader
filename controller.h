#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonArray>
#include "postparser.h"
#include "databasehandler.h"
#include "webserviceclient.h" //TODO: remove
#include <QThread>

class Controller : public QObject
{
 Q_OBJECT
public:
  Controller(QObject *parent = 0);
  Q_INVOKABLE void downloadFrontPage();
  Q_INVOKABLE void downloadThread(QString threadId);
  Q_INVOKABLE QJsonArray getFrontPage();
  Q_INVOKABLE QJsonValue getThread();
  Q_PROPERTY(QString currentBoardDirectory READ currentBoardDirectory WRITE setCurrentBoardDirectory)
  Q_PROPERTY(QString baseDirectory READ baseDirectory WRITE setBaseDirectory)

 QString currentBoardDirectory() const;
 void setCurrentBoardDirectory(const QString &currentBoardDirectory);

 QString baseDirectory() const;
 void setBaseDirectory(const QString &baseDirectory);

signals:
 Q_SIGNAL void frontPageDownloaded();
 Q_SIGNAL void threadDownloaded();

private slots:
 void threadDownloaded(bool success);
 void frontPageDownloaded(bool success);

 private:
  QString m_currentBoardDirectory;
  QString m_baseDirectory;
  PostParser m_postParser;
  DataBaseHandler m_dataBaseHandler;
  WebServiceClient m_wc;
  QJsonArray m_currentFrontPage;
  QJsonValue m_currentThread;
};



#endif // CONTROLLER_H
