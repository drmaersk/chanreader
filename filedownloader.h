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
  FileDownloader(QObject *parent = 0);

 void downloadFile(QString fileName);

signals:
 Q_SIGNAL void fileSaved(QString fileName, QString path);

public slots:
 void downloadFile(QString baseUrl, QString fileName, QString pathToSave);
 void download();

private slots:
 void fileDownloaded(QNetworkReply* pReply);

 private:
  QNetworkAccessManager* m_WebCtrl;
  QByteArray m_DownloadedData;
  QString m_baseUrl;
  QString m_fileName;
  QString m_saveDirectory;
  QUrl m_fileUrl;
};

#endif // FILEDOWNLOADER_H
