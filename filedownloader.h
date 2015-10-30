#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonArray>
#include "postparser.h"
#include "databasehandler.h"

class FileDownloader : public QObject
{
 Q_OBJECT
public:
  FileDownloader(QObject *parent = 0);
  Q_INVOKABLE void download(QUrl url);
  Q_PROPERTY(QJsonArray postList READ postList WRITE setPostList)
  Q_PROPERTY(QJsonValue thread READ thread WRITE setThread)
  Q_PROPERTY(QString currentBoardDirectory READ currentBoardDirectory WRITE setCurrentBoardDirectory)
  Q_PROPERTY(QString baseDirectory READ baseDirectory WRITE setBaseDirectory)
  //
 QJsonArray postList() const;
 void setPostList(QJsonArray n_postlist);

 QJsonValue thread () const;
 void setThread(QJsonValue n_thread);

 QString currentBoardDirectory() const;
 void setCurrentBoardDirectory(const QString &currentBoardDirectory);

 QString baseDirectory() const;
 void setBaseDirectory(const QString &baseDirectory);

signals:
 Q_SIGNAL void filesDownloaded();

private slots:
 void fileDownloaded(QNetworkReply* pReply);

 private:
  QNetworkAccessManager m_WebCtrl;
  QJsonArray m_imgsToDl;
  QByteArray m_DownloadedData;
  QJsonArray m_postList;
  QJsonValue m_thread;
  QString m_currentBoardDirectory;
  QString m_baseDirectory;
  PostParser m_postParser;
  int m_outStandingRequests;
  int m_receivedRequests;
  DataBaseHandler m_dataBaseHandler;
};

#endif // FILEDOWNLOADER_H
