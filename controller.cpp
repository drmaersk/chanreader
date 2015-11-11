#include "controller.h"
#include "filedownloader.h"

Controller::Controller(QObject *parent) :
    QObject(parent),
    m_postParser(),
    m_dataBaseHandler(),
    m_wc(parent),
    m_currentFrontPage(),
    m_currentThread(),
    m_fileDownloaderHandler()
{
    m_settings = SettingsHandler::getSettingsHandler();

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

    m_fileDlThread = new QThread(this);
    m_fileDownloaderHandler.moveToThread(m_fileDlThread);
    m_fileDlThread->start();

    connect(this,
            SIGNAL (putOnQueue(QString, QString, QString)),
            &m_fileDownloaderHandler,
            SLOT (downloadWhenReady(QString, QString, QString)));

    connect(&m_fileDownloaderHandler,
            SIGNAL(fileSaved(QString, QString)),
            &m_dataBaseHandler,
            SLOT(insertImageInDatabase(QString, QString)));
}

void Controller::downloadFrontPageJson()
{
    qDebug() << "downloadFp";
    m_wc.downloadFrontPageJson(m_settings->getCurrentBoard());
    qDebug() << "downloadFPdone";
}

void Controller::downloadThreadJson(QString threadId)
{
    qDebug() << "downloadThread";
    m_wc.downloadThreadJson(m_settings->getCurrentBoard(), threadId);
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
    return m_settings->getCurrentBoard();
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
//    QString boardUrl = m_settings->getBoardUrl();
//    return boardUrl;
//}

//QString Controller::imageUrl()
//{
//    QString boardUrl = m_settings->getImageUrl();
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

        QVector<QJsonArray> currentFrontPage = m_wc.getFrontPageJson(); //TODO: send to database
        m_currentFrontPage = currentFrontPage[0]; //TODO: Handle multiple pages
        foreach(QJsonArray page, currentFrontPage){
            QStringList imgUrls = m_postParser.getImageUrlsFromFrontPage(page); //TODO: get image name not urls
            downloadImages(imgUrls);
            emit insertThreadsInDatabase(page);
        }
        emit frontPageJsonReady();

    }
}

void Controller::downloadImages(QStringList fileUrls)
{
    const QString currentBaseUrl = WebServiceClient::URL_PREFIX_IMAGE_HTTP + m_settings->getCurrentBoard() + "/";
    const QString imageDirectory = m_settings->getImageDirectory();
    const QString currentBoard = m_settings->getCurrentBoard();
    foreach(QString fileName, fileUrls)
    {
        QString threadNo = m_postParser.getThreadNoFromImage(fileName);
        QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
        QString savePath =
                imageDirectory + QDir::separator() +
                currentBoard   + QDir::separator() +
                currentDate    + QDir::separator() +
                threadNo       + QDir::separator();

        //TODO: copy one step up
//        connect(fd,
//                SIGNAL(fileSaved(QString, QString)),
//                &m_dataBaseHandler,
//                SLOT(insertImageInDatabase(QString, QString)));

        emit putOnQueue(currentBaseUrl, fileName, savePath);
    }
}

void Controller::cleanupBeforeExit()
{
    qDebug() << "cleanupBeforeExit()";
    m_dbThread->quit();
    m_dbThread->wait(5000);
    m_dbThread->deleteLater();

    m_fileDlThread->quit();
    m_fileDlThread->wait(5000);
    m_fileDlThread->deleteLater();
    qDebug() << "cleanupBeforeExit done()";
}
