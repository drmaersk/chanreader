#include "databasehandler.h"

DataBaseHandler::DataBaseHandler()
{
    qDebug() << "DbConstructor";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    m_db.setDatabaseName(settingsDir + QDir::separator() +"chanReaderDb.sqlite");
    if (!m_db.open())
    {
        qDebug() << m_db.lastError().text();
    }
    else
    {
        QSqlQuery query(m_db);
        if(!query.exec("CREATE TABLE IF NOT EXISTS boardtothreads (board STRING, thread STRING, UNIQUE(thread))"))
        {
            qDebug() << query.lastError().text();
        }
        if(!query.exec("CREATE TABLE IF NOT EXISTS threads (no STRING, date DATETIME, UNIQUE(no))"))
        {
            qDebug() << query.lastError().text();
        }
        if(!query.exec("CREATE TABLE IF NOT EXISTS post (no STRING, com STRING)"))
        {
            qDebug() << query.lastError().text();
        }
    }
}

void DataBaseHandler::insertThreadInDatabase(QString board, QString date, QString thread)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO boardtothreads (board, thread)"
                  "VALUES (?, ?)");
    query.addBindValue(board);
    query.addBindValue(thread);
    query.exec();

    query.prepare("INSERT INTO threads (no, date)"
                  "VALUES (?, ?)");
    query.addBindValue(thread);
    query.addBindValue(date);
    query.exec();



            //query.exec("CREATE TABLE IF NOT EXISTS post (no STRING, com STRING)");
}

