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
#include "webserviceclient.h" //TODO: remove

class FileDownloader : public QObject
{
 Q_OBJECT
public:
  FileDownloader(QObject *parent = 0);
  Q_INVOKABLE void download(QUrl url);

 void downloadFiles(QStringList fileNames);

 void setCurrentBoardDirectory(const QString &currentBoardDirectory);

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
  int m_outStandingRequests;
  int m_receivedRequests;
};

#endif // FILEDOWNLOADER_H
