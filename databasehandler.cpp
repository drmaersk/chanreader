#include "databasehandler.h"
#include <QDateTime>
#include <QThread> //TODO: remove after testing
#include <QJsonValue>
#include <QRegularExpression>
#include "webserviceclient.h"
#include "settingshandler.h"

DataBaseHandler::DataBaseHandler(QObject* parent) : QObject(parent), m_postParser(), m_mutex(), m_debugOutput(false)
{
    qDebug() << "DbConstructor";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    if(!QDir(settingsDir).exists())
    {
        QDir().mkpath(settingsDir);
    }

    m_db.setDatabaseName(settingsDir + QDir::separator() +"chanReaderDb.sqlite");

    if (!m_db.open() && m_debugOutput)
    {
        qDebug() << m_db.lastError().text();
    }
    else
    {
        QSqlQuery query(m_db);
        if(!query.exec("CREATE TABLE IF NOT EXISTS threads (no STRING, board STRING, date DATETIME, PRIMARY KEY(no, board))") && m_debugOutput)
        {
            qDebug() << query.lastError().text();
        }
        if(!query.exec("CREATE TABLE IF NOT EXISTS post (no STRING, com STRING, name STRING, ext STRING, tim STRING, trip STRING, w STRING, h STRING, threadNo STRING REFERENCES threads(no), board STRING REFERENCES threads(board), PRIMARY KEY(no, threadNo, board))") && m_debugOutput)
        {
            qDebug() << query.lastError().text();
        }
    }
}

void DataBaseHandler::insertThreadsInDatabase(QJsonArray threads)
{
    QStringList threadNumbers = m_postParser.getThreadNumbersFromFrontPageJson(threads);
    foreach(QString threadNumber, threadNumbers)
    {
        //qDebug() << threadNumber;
        QJsonArray posts = m_postParser.getPostsFromThreadNumber(threadNumber, threads);
        insertThreadInDatabase("tv", QDateTime::currentDateTime().toString("yyyy-MM-dd"), threadNumber); //TODO: get board programmatically
        insertPostsInDatabase(posts);
    }
}

void DataBaseHandler::insertThreadInDatabase(QString board, QString date, QString thread)
{
    m_mutex.lock();
    QSqlQuery query(m_db);

    query.prepare("INSERT INTO threads (no, board, date)"
                  "VALUES (?, ?, ?)");
    query.addBindValue(thread);
    query.addBindValue(board);
    query.addBindValue(date);
    if(!query.exec() && m_debugOutput)
    {
        qDebug() << query.lastError().text();
    }
    m_mutex.unlock();
}

void DataBaseHandler::insertPostsInDatabase(QJsonArray posts)
{
    m_mutex.lock();
    const QString currentTimPrefix = WebServiceClient::URL_PREFIX_IMAGE_HTTP + SettingsHandler::getSettingsHandler()->getCurrentBoard() + "/";
    QSqlQuery query(m_db);
    foreach (const QJsonValue& post, posts) {
        QJsonObject postObj = post.toObject();

        QString threadNo;

        if(postObj["resto"] == 0)
        {
            threadNo = QString::number(postObj["no"].toInt());

        }
        else
        {
            threadNo = QString::number(postObj["resto"].toInt());
        }

        QString no  = QString::number(postObj["no"].toInt());
        QString com = postObj["com"].toString();
        QString name = postObj["name"].toString();
        QString ext = postObj["ext"].toString();
        QString tim = QString::number(postObj["tim"].toVariant().toLongLong(), 10);
        if(!tim.isEmpty())
        {
            tim = currentTimPrefix + tim;
        }
        QString trip = postObj["trip"].toString();
        QString w = QString::number(postObj["w"].toInt());
        QString h = QString::number(postObj["h"].toInt());

        //TODO: add more values, required: time for sorting the SELECT

        query.prepare("INSERT INTO post (no, com, name, ext, tim, trip, w, h, threadNo, board)"
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(no);
        query.addBindValue(com);
        query.addBindValue(name);
        query.addBindValue(ext);
        query.addBindValue(tim);
        query.addBindValue(trip);
        query.addBindValue(w);
        query.addBindValue(h);
        query.addBindValue(threadNo);
        query.addBindValue("tv"); //TODO: get programatically
        if(!query.exec() && m_debugOutput)
        {
            qDebug() << query.lastError().text();
        }
    }
    m_mutex.unlock();
}

void DataBaseHandler::insertImageInDatabase(QString fileName, QString path)
{
    m_mutex.lock();
    static int i = 1;
    QStringList splitPath = path.split(QDir::separator());
    QStringList splitName = fileName.split(".");

    QString tim = splitName[0]; //TODO: full path to img
    QString ext = "."+splitName[1];
    QString board = splitPath[2];
    QString thread = splitPath[4];
    if(i == 1)
    {
        qDebug() << board << thread << tim << ext;
    }
    i++;
    m_mutex.unlock();
}

void DataBaseHandler::updateImage(QString board, QString date, QString thread)
{
    m_mutex.lock();
    QSqlQuery query(m_db);

    query.prepare("INSERT INTO threads (no, board, date)"
                  "VALUES (?, ?, ?)");
    query.addBindValue(thread);
    query.addBindValue(board);
    query.addBindValue(date);
    if(!query.exec() && m_debugOutput)
    {
        qDebug() << query.lastError().text();
    }
    m_mutex.unlock();
}

QJsonArray DataBaseHandler::getThread(QString threadNo)
{
    m_mutex.lock();
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM post WHERE threadNo=?");
    query.addBindValue(threadNo);
    QJsonArray posts;

    if(!query.exec() && m_debugOutput)
    {
        qDebug() << query.lastError().text();
    }
    while (query.next()) {
        QString no = query.value(0).toString();
        QString com = query.value(1).toString();
        QString name = query.value(2).toString();
        QString ext = query.value(3).toString();
        QString tim = query.value(4).toString();
        QString trip = query.value(5).toString();
        QString w = query.value(6).toString();
        QString h = query.value(7).toString();

        QJsonObject post;

        post["no"] = no;
        post["com"] = com;
        post["name"] = name;
        post["ext"] = ext;
        post["tim"] = tim;
        post["trip"] = trip;
        post["w"] = w;
        post["h"] = h;
        posts.append(post);
    }
    m_mutex.unlock();
    return posts;
}

