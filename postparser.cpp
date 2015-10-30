#include "postparser.h"



//postList[0].toObject()["posts"].toArray()[0].toObject()["com"].toString();
PostParser::PostParser() : m_imageToThreadMap()
{

}

QStringList PostParser::getImageUrlsFromPostList(const QJsonArray postList)
{
    QStringList imgFileNames;
    m_imageToThreadMap.clear();
    foreach (const QJsonValue& thread, postList) {
        QJsonArray posts = thread.toObject()["posts"].toArray();
        imgFileNames += parsePosts(posts);
    }

    return imgFileNames;
}

QStringList PostParser::getImageUrlsFromThread(const QJsonValue thread){
    QJsonArray posts = thread.toArray();
    m_imageToThreadMap.clear();

    return parsePosts(posts);
}

QStringList PostParser::parsePosts(const QJsonArray posts)
{
   QStringList imgFileNames;
   foreach (const QJsonValue& post, posts) {
        QJsonObject postObj = post.toObject();
        if(!postObj["tim"].isNull()){
            QString imgName = QString::number(postObj["tim"].toVariant().toLongLong(), 10);
            QString imgFileName = imgName + postObj["ext"].toString();
            imgFileNames << imgFileName;
            if(postObj["resto"] == 0)
            {
               QString threadNo = QString::number(postObj["no"].toInt());
               m_imageToThreadMap.insert(imgFileName, threadNo);
            }
            else
            {
                QString threadNo = QString::number(postObj["resto"].toInt());
                m_imageToThreadMap.insert(imgFileName, threadNo);
            }
        }
    }
    return imgFileNames;
}

QString PostParser::getThreadNoFromImage(const QString &imageName) const
{
    return m_imageToThreadMap.find(imageName).value();
}
