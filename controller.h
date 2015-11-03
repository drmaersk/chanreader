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
#include "settingshandler.h"
#include "threaddownloader.h"

class Controller : public QObject
{
 Q_OBJECT
public:
  Controller(QObject *parent = 0);
  Q_INVOKABLE void downloadFrontPage();
  Q_INVOKABLE void downloadThread(QString threadId);
  Q_INVOKABLE QJsonArray getFrontPage();
  Q_INVOKABLE QJsonArray getThread();
  Q_INVOKABLE QString boardUrl();
  Q_INVOKABLE QString imageUrl();
  Q_PROPERTY(QString currentBoard READ currentBoard WRITE setCurrentBoard)
  Q_PROPERTY(QString baseDirectory READ baseDirectory WRITE setBaseDirectory)

 QString currentBoard();
 void setCurrentBoard(const QString &currentBoardDirectory);

 QString baseDirectory() const;
 void setBaseDirectory(const QString &baseDirectory);

signals:
 Q_SIGNAL void frontPageDownloaded();
 Q_SIGNAL void threadDownloaded();

private slots:
 void threadDownloaded(bool success);
 void frontPageDownloaded(bool success);

 private:
  PostParser m_postParser;
  DataBaseHandler m_dataBaseHandler;
  WebServiceClient m_wc;
  QJsonArray m_currentFrontPage;
  QJsonArray m_currentThread;
  SettingsHandler m_settings;
};



#endif // CONTROLLER_H
