#include "filedownloaderthread.h"

FileDownloaderThread::FileDownloaderThread(QObject *parent,
                                   QString fileName,
                                   QString pathToSave,
                                   QString baseUrl) :
    QThread(parent),
    m_fileName(fileName),
    m_pathToSave(pathToSave),
    m_baseUrl(baseUrl),
    m_fileDownloader(parent)
{
    connect(this,
            SIGNAL (downloadFile(QString, QString, QString)),
            &m_fileDownloader,
            SLOT (downloadFile(QString, QString, QString)));

    connect(&m_fileDownloader,
            SIGNAL (fileSaved()),
            this,
            SLOT (fileSaved()));

}

void FileDownloaderThread::run()
{
//    qDebug() << "started: " << m_fileName;
    emit downloadFile(m_fileName, m_pathToSave, m_baseUrl);
    exec();
}

void FileDownloaderThread::fileSaved()
{
//    qDebug() << "stopped: " << m_fileName;
//    emit(testSignal(m_fileName));
    exit();
}



