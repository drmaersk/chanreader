#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDir>
#include <QtDebug>
#include <QStandardPaths>

class DataBaseHandler : public QObject
{
    Q_OBJECT
public:
    DataBaseHandler(QObject* parent = 0);

    void insertThreadInDatabase(QString board, QString date, QString thread);
//signals:

//public slots:
private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
