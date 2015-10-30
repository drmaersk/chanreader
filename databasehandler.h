#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDir>
#include <QtDebug>

class DataBaseHandler
{
public:
    DataBaseHandler();

    void insertThreadInDatabase(QString board, QString date, QString thread);
//signals:

//public slots:
private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
