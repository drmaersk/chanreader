#include "databasehandler.h"

DataBaseHandler::DataBaseHandler()
{
    qDebug() << "DbConstructor";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString currentDir = "C:/tmp";//QDir::currentPath();
    m_db.setDatabaseName(currentDir + QDir::separator() +"4chanDb.sqlite");
    if (!m_db.open())
    {
        qDebug() << m_db.lastError().text();
    }
    else
    {
        QSqlQuery query(m_db);
        query.exec("CREATE TABLE IF NOT EXISTS boardtothreads (board STRING, thread STRING, UNIQUE(thread))");
        query.exec("CREATE TABLE IF NOT EXISTS threads (no STRING, date DATETIME, UNIQUE(no))");
        query.exec("CREATE TABLE IF NOT EXISTS post (no STRING, com STRING)");
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

