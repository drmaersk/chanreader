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
    QStringList getImageUrlsFromFrontPage(QJsonArray threads);
    QStringList getImageUrlsFromThread(const QJsonArray posts);
    QString getThreadNoFromImage(const QString &imageName) const;

    QStringList getThreadNumbersFromFrontPageJson(QJsonArray threads);

    QJsonArray getPostsFromThreadNumber(QString threadNo, QJsonArray threads);
private:
    QStringList getImageUrlsFromPosts(const QJsonArray posts);
    QHash<QString, QString> m_imageToThreadMap;
};

#endif // POSTPARSER_H
