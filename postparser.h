#ifndef POSTPARSER_H
#define POSTPARSER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QtDebug>
#include <QJsonDocument>

class PostParser
{
public:
    PostParser();
    QStringList getImageUrlsFromPostList(QJsonArray postList);
    QStringList getImageUrlsFromThread(QJsonValue thread);
    QString getThreadNoFromImage(const QString &imageName) const;

private:
    QStringList parsePosts(const QJsonArray posts);
    QHash<QString, QString> m_imageToThreadMap;
};

#endif // POSTPARSER_H
