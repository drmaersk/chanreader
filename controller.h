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
#include "webserviceclient.h"
#include <QThread>
#include "settingshandler.h"

class Controller : public QObject
{
 Q_OBJECT
public:
  Controller(QObject *parent = 0);
  Q_INVOKABLE void downloadFrontPageJson();
  Q_INVOKABLE void downloadThreadJson(QString threadId);
  Q_INVOKABLE QJsonArray getFrontPageJson();
  Q_INVOKABLE QJsonArray getThreadJson();
  Q_INVOKABLE QString boardUrl();
  Q_INVOKABLE QString imageUrl();
  Q_PROPERTY(QString currentBoard READ currentBoard WRITE setCurrentBoard)
  Q_PROPERTY(QString baseDirectory READ baseDirectory WRITE setBaseDirectory)

 QString currentBoard();
 void setCurrentBoard(const QString &currentBoardDirectory);

 QString baseDirectory() const;
 void setBaseDirectory(const QString &baseDirectory);

public slots:
 void cleanupBeforeExit();

signals:
 Q_SIGNAL void frontPageJsonReady();
 Q_SIGNAL void threadJsonReady();
 Q_SIGNAL void insertThreadsInDatabase(QJsonArray threads);
 Q_SIGNAL void insertPostsInDatabase(QJsonArray posts);

private slots:
 void threadJsonReady(bool success);
 void frontPageJsonReady(bool success);

 private:
  PostParser m_postParser;
  DataBaseHandler m_dataBaseHandler;
  WebServiceClient m_wc;
  QJsonArray m_currentFrontPage;
  QJsonArray m_currentThread;
  SettingsHandler m_settings;
  void downloadImages(QStringList fileUrls);
  QThread* m_dbThread;
};



#endif // CONTROLLER_H
