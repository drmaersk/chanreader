#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>



class FileDownloader : public QObject
{
 Q_OBJECT
public:
  FileDownloader(QObject *parent = 0, const QString baseUrl = "", const QString fileName = "", const QString directory = "");

 void download();

 void downloadFile(QString fileName);

signals:
 Q_SIGNAL void fileSaved();

private slots:
 void fileDownloaded(QNetworkReply* pReply);

 private:
  QNetworkAccessManager m_WebCtrl;
  QByteArray m_DownloadedData;
  QString m_baseUrl;
  QString m_fileName;
  QString m_currentDirectory;
  QUrl m_fileUrl;
};

#endif // FILEDOWNLOADER_H
