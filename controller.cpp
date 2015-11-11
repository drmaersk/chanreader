#include "controller.h"
#include "filedownloader.h"

Controller::Controller(QObject *parent) :
    QObject(parent),
    m_postParser(),
    m_dataBaseHandler(),
    m_wc(parent),
    m_currentFrontPage(),
    m_currentThread(),
    m_settings()
{
    connect(&m_wc,
            SIGNAL (threadJsonDownloaded(bool)),
            this,
            SLOT (threadJsonReady(bool)));
    connect(&m_wc,
            SIGNAL (frontPageJsonDownloaded(bool)),
            this,
            SLOT (frontPageJsonReady(bool)));

    m_dbThread = new QThread(this);
    m_dataBaseHandler.moveToThread(m_dbThread);
    m_dbThread->start();



    connect(this,
            SIGNAL (insertThreadsInDatabase(QJsonArray)),
            &m_dataBaseHandler,
            SLOT (insertThreadsInDatabase(QJsonArray)));

    connect(this,
            SIGNAL (insertPostsInDatabase(QJsonArray)),
            &m_dataBaseHandler,
            SLOT (insertPostsInDatabase(QJsonArray)));
}

void Controller::downloadFrontPageJson()
{
    qDebug() << "downloadFp";
    m_wc.downloadFrontPageJson(m_settings.getCurrentBoard());
    qDebug() << "downloadFPdone";
}

void Controller::downloadThreadJson(QString threadId)
{
    qDebug() << "downloadThread";
    m_wc.downloadThreadJson(m_settings.getCurrentBoard(), threadId);
}

QJsonArray Controller::getFrontPageJson()
{
    return m_currentFrontPage;
}

QJsonArray Controller::getThreadJson()
{
    return m_currentThread;
}

QString Controller::currentBoard()
{
    return m_settings.getCurrentBoard();
}

void Controller::setCurrentBoard(const QString &currentBoard)
{

}

QString Controller::baseDirectory() const
{
    return "todo";
}

void Controller::setBaseDirectory(const QString &baseDirectory)
{

}

//QString Controller::boardUrl()
//{
//    QString boardUrl = m_settings.getBoardUrl();
//    return boardUrl;
//}

//QString Controller::imageUrl()
//{
//    QString boardUrl = m_settings.getImageUrl();
//    return boardUrl;
//}

void Controller::threadJsonReady(bool success)
{
    if(success)
    {
        m_currentThread = m_wc.getThreadJson();
        QStringList imgUrls = m_postParser.getImageUrlsFromThread(m_currentThread);

        emit insertPostsInDatabase(m_currentThread);
        emit threadJsonReady();

        downloadImages(imgUrls);
    }
    else{
        //m_currentThread = m_dataBaseHandler.getThread("62574811"); TODO: Test later
        emit threadJsonReady();
    }
}

void Controller::frontPageJsonReady(bool success)
{
    if(success)
    {
        m_currentFrontPage = m_wc.getFrontPageJson();
        QStringList imgUrls = m_postParser.getImageUrlsFromFrontPage(m_currentFrontPage);

        emit insertThreadsInDatabase(m_currentFrontPage);
        emit frontPageJsonReady();

        downloadImages(imgUrls);
    }
}

void Controller::downloadImages(QStringList fileUrls)
{
    foreach(QString fileUrl, fileUrls)
    {
        QString threadNo = m_postParser.getThreadNoFromImage(fileUrl);
        QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
        QString savePath =
                m_settings.getImageDirectory() + QDir::separator() +
                m_settings.getCurrentBoard()  + QDir::separator() +
                currentDate + QDir::separator() +
                threadNo + QDir::separator();

        QThread* thread = new QThread(this);
        FileDownloader* fd = new FileDownloader();
        fd->moveToThread(thread);

        connect(fd,
                SIGNAL(fileSaved(QString, QString)),
                &m_dataBaseHandler,
                SLOT(insertImageInDatabase(QString, QString)));

        connect(fd,
                SIGNAL(fileSaved(QString, QString)),
                thread,
                SLOT(quit()));

        connect(thread,
                &QThread::finished,
                thread,
                &QThread::deleteLater);

        thread->start();

        fd->downloadFile(fileUrl,
                         savePath,
                         m_settings.getImageUrl());

    }

}

void Controller::cleanupBeforeExit()
{
    qDebug() << "cleanupBeforeExit()";
    m_dbThread->quit();
    m_dbThread->wait(5000);
    //m_dbThread->terminate();
    m_dbThread->deleteLater();
    qDebug() << "cleanupBeforeExit done()";
}
