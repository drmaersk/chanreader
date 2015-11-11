#include "filedownloaderhandler.h"
#include "filedownloader.h"

FileDownloaderHandler::FileDownloaderHandler(QObject *parent) : QObject(parent), m_outstandingDownloads(0), m_fileDownloaderVector()
{


    //Should start maximum number of ~ 4 threads for image dling,
    //get
}
void FileDownloaderHandler::downloadWhenReady(QString currentBaseUrl, QString fileName, QString savePath)
{
    m_mutex.lock();

    FileInfoStruct fd = {currentBaseUrl, fileName, savePath};
    m_fileDownloaderVector.push_back(fd);
    m_mutex.unlock();
    startNewDownload();
}

void FileDownloaderHandler::startNewDownload()
{
    m_mutex.lock();
    if(m_outstandingDownloads < 5 && m_fileDownloaderVector.size() > 0)
    {
        QThread* thread = new QThread(this);
        FileDownloader* fd = new FileDownloader();
        //FileDownloader* fd = reinterpret_cast<FileDownloader*>(m_fileDownloaderVector.front()); //TODO: Create pure virtual base for FileDownloader if neccessary

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

        fd->moveToThread(thread);
        m_fileDownloaderVector.pop_front();
        thread->start();
        FileInfoStruct fis = m_fileDownloaderVector.front();
        emit startDownload(fis.currentBaseUrl, fis.fileName, fis.savePath);
        m_outstandingDownloads++;
    }
    m_mutex.unlock();
}

void FileDownloaderHandler::downloadComplete(QString a, QString b)
{
    m_mutex.lock();
    --m_outstandingDownloads;
    emit fileSaved(a,b); //To Database
    m_mutex.unlock();
    startNewDownload();
}

