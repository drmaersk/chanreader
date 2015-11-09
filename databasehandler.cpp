#include "databasehandler.h"
#include <QDateTime>
#include <QThread> //TODO: remove after testing

DataBaseHandler::DataBaseHandler(QObject* parent) : QObject(parent), m_mutex()
{
    qDebug() << "DbConstructor";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    if(!QDir(settingsDir).exists())
    {
        QDir().mkpath(settingsDir);
    }

    m_db.setDatabaseName(settingsDir + QDir::separator() +"chanReaderDb.sqlite");

    if (!m_db.open())
    {
        qDebug() << m_db.lastError().text();
    }
    else
    {
        QSqlQuery query(m_db);
        if(!query.exec("CREATE TABLE IF NOT EXISTS boardtothreads(board STRING, thread STRING, PRIMARY KEY(thread))"))
        {
            qDebug() << query.lastError().text();
        }
        if(!query.exec("CREATE TABLE IF NOT EXISTS threads (no STRING, date DATETIME, PRIMARY KEY(no))"))
        {
            qDebug() << query.lastError().text();
        }
        if(!query.exec("CREATE TABLE IF NOT EXISTS post (no STRING, com STRING, threadNo STRING, FOREIGN KEY(threadNo) REFERENCES threads(no))"))
        {
            qDebug() << query.lastError().text();
        }
    }
}

void DataBaseHandler::insertThreadInDatabase(QString board, QString date, QString thread)
{
    m_mutex.lock();
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO boardtothreads (board, thread)"
                  "VALUES (?, ?)");
    query.addBindValue(board);
    query.addBindValue(thread);
    if(!query.exec())
    {
        qDebug() << query.lastError().text();
    }

    query.prepare("INSERT INTO threads (no, date)"
                  "VALUES (?, ?)");
    query.addBindValue(thread);
    query.addBindValue(date);
    if(!query.exec())
    {
        qDebug() << query.lastError().text();
    }

    m_mutex.unlock();

    //query.exec("CREATE TABLE IF NOT EXISTS post (no STRING, com STRING)");
}

void DataBaseHandler::insertPostsInDatabase(QStringList posts)
{

}

void DataBaseHandler::insertThreadsInDatabase(QVector<ThreadData> threads)
{
    qDebug() << "DataBaseHandler: insert started";
    m_mutex.lock();
    foreach(ThreadData thread, threads){

        QSqlQuery query(m_db);
        query.prepare("INSERT INTO boardtothreads (board, thread)"
                      "VALUES (?, ?)");
        query.addBindValue("tv"); //TODO: Get via inparam
        query.addBindValue(thread.no);
        if(!query.exec())
        {
            //qDebug() << query.lastError().text(); TODO: keep or remove
        }

        query.prepare("INSERT INTO threads (no, date)"
                      "VALUES (?, ?)");
        query.addBindValue(thread.no);
        query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd")); //TODO: get via inparam
        if(!query.exec())
        {
//            qDebug() << query.lastError().text(); TODO: keep or remove
        }

        foreach(PostData post, thread.posts){
            query.prepare("INSERT INTO post (no, com, threadNo)"
                          "VALUES (?, ?, ?)");
            query.addBindValue(post.no);
            query.addBindValue(post.com);
            query.addBindValue(thread.no);
            if(!query.exec())
            {
                qDebug() << query.lastError().text();
            }
        }
    }
    m_mutex.unlock();
    qDebug() << "DataBaseHandler: insert done";
}

