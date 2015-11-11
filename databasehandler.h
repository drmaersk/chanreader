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
#include <QJsonArray>
#include "postparser.h"

class DataBaseHandler : public QObject
{
    Q_OBJECT
public:
    DataBaseHandler(QObject* parent = 0);
    QJsonArray getThread(QString threadNo);
    void updateImage(QString board, QString date, QString tim);
public slots:
    void insertThreadsInDatabase(QJsonArray threads);
    void insertPostsInDatabase(QJsonArray posts);
    void insertImageInDatabase(QString fileName, QString path);
private:
    void insertThreadInDatabase(QString board, QString date, QString thread);
    QSqlDatabase m_db;
    PostParser m_postParser;
    QMutex m_mutex;
    bool m_debugOutput;
};

#endif // DATABASE_H
