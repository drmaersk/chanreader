#ifndef THREADDOWNLOADER_H
#define THREADDOWNLOADER_H
#include <QObject>
#include <QThread>
#include <QDebug>
#include "filedownloader.h"

class FileDownloaderThread : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
public:
    FileDownloaderThread(QObject *parent = 0,
                     QString fileName = "",
                     QString pathToSave = "",
                     QString baseUrl = "");
signals:
//    Q_SIGNAL void threadJsonDownloaded();
    Q_SIGNAL void downloadFile(QString fileName, QString pathToSave, QString baseUrl);
    Q_SIGNAL void testSignal(QString test);
private:
    QString m_fileName;
    QString m_pathToSave;
    QString m_baseUrl;
    FileDownloader m_fileDownloader;
private slots:
    void fileSaved();
};

#endif // THREADDOWNLOADER_H
