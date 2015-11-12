#include "filedownloaderhandler.h"
#include "filedownloader.h"

FileDownloaderHandler::FileDownloaderHandler(QObject *parent) : QObject(parent), m_outstandingDownloads(0),  m_mutex(), m_fileDownloaderQueue()
{


    //Should start maximum number of ~ 4 threads for image dling,
    //get
}
void FileDownloaderHandler::downloadWhenReady(QString currentBaseUrl, QString fileName, QString savePath)
{
    m_mutex.lock();
    FileInfoStruct fis = {QString(currentBaseUrl), QString(fileName), QString(savePath)};
    //qDebug() << currentBaseUrl + fileName;
    m_fileDownloaderQueue.enqueue(fis);
    startNewDownload();
    m_mutex.unlock();
}

void FileDownloaderHandler::startNewDownload()
{
    if(m_outstandingDownloads < 1 && !m_fileDownloaderQueue.isEmpty())
    {
        QThread* thread = new QThread();
        FileDownloader* fd = new FileDownloader();

        fd->moveToThread(thread);
        thread->start();

        connect(this,
                SIGNAL(startDownload(QString,QString,QString)),
                fd,
                SLOT(downloadFile(QString,QString,QString)));

        connect(fd,
                SIGNAL(fileSaved(QString, QString)),
                this,
                SLOT(downloadComplete(QString, QString)));

        connect(fd,
                SIGNAL(fileSaved(QString, QString)),
                thread,
                SLOT(quit()));

        connect(thread,
                &QThread::finished,
                thread,
                &QThread::deleteLater);

        FileInfoStruct fis = m_fileDownloaderQueue.dequeue();
//        QString currentBaseUrl = fis.currentBaseUrl;
//        QString fileName = fis.fileName;
//        QString savePath = fis.savePath;
        qDebug() << fis.fileName;

        emit startDownload(fis.currentBaseUrl, fis.fileName, fis.savePath);
        m_outstandingDownloads++;
    }
}

void FileDownloaderHandler::downloadComplete(QString fileName, QString path)
{
    m_mutex.lock();
    --m_outstandingDownloads;
    qDebug() << "fileSaved: " << fileName;
    emit fileSaved(fileName,path); //To Database
    startNewDownload();
    m_mutex.unlock();
}

