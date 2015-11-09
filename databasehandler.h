#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDir>
#include <QtDebug>
#include <QStandardPaths>
#include <QMutex>
#include "threaddata.h"

class DataBaseHandler : public QObject
{
    Q_OBJECT
public:
    DataBaseHandler(QObject* parent = 0);

    void insertThreadInDatabase(QString board, QString date, QString thread);
    void insertPostsInDatabase(QStringList posts);
//signals:

public slots:
    void insertThreadsInDatabase(QVector<ThreadData> threads);
private:
    QSqlDatabase m_db;
    QMutex m_mutex;
};

#endif // DATABASE_H
