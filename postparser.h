#ifndef POSTPARSER_H
#define POSTPARSER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QtDebug>
#include <QJsonDocument>
#include "threaddata.h"

class PostParser
{
public:
    PostParser();
    QStringList getImageUrlsFromFrontPage(QJsonArray threads);
    QStringList getImageUrlsFromThread(const QJsonArray posts);
    QString getThreadNoFromImage(const QString &imageName) const;
    QVector<ThreadData> getThreadDataFromFrontPage(QJsonArray threads);

private:
    QStringList parsePosts(const QJsonArray posts);
    QHash<QString, QString> m_imageToThreadMap;
};

#endif // POSTPARSER_H
