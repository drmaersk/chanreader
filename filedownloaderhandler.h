#ifndef FILEDOWNLOADERHANDLER_H
#define FILEDOWNLOADERHANDLER_H

#include "filedownloader.h"
#include <QObject>
#include <QMutex>
#include <QThread>
#include <QQueue>

class FileDownloaderHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileDownloaderHandler(QObject *parent = 0);

signals:
    Q_SIGNAL void startDownload(QString, QString, QString);
    Q_SIGNAL void fileSaved(QString, QString);
public slots:
    void downloadWhenReady(QString, QString, QString);
    void downloadComplete(QString fileName, QString path);
private:
    uint32_t m_outstandingDownloads;
    QMutex m_mutex;
    void startNewDownload();
    struct FileInfoStruct {
        QString currentBaseUrl;
        QString fileName;
        QString savePath;
    };
    QQueue<FileInfoStruct> m_fileDownloaderQueue;
};

#endif // FILEDOWNLOADERHANDLER_H
