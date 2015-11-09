#include "postparser.h"


PostParser::PostParser() : m_imageToThreadMap()
{

}

QStringList PostParser::getImageUrlsFromFrontPage(const QJsonArray threads)
{
    QStringList imgFileNames;
    m_imageToThreadMap.clear();
    foreach (const QJsonValue& thread, threads) {
        QJsonArray posts = thread.toObject()["posts"].toArray();
        imgFileNames += getImageUrlsFromPosts(posts);
    }

    return imgFileNames;
}

QStringList PostParser::getImageUrlsFromThread(const QJsonArray posts){
    m_imageToThreadMap.clear();
    return getImageUrlsFromPosts(posts);
}

QStringList PostParser::getImageUrlsFromPosts(const QJsonArray posts)
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

QVector<ThreadData> PostParser::getThreadDataFromFrontPage(QJsonArray threads)
{
    QVector<ThreadData> threadsVector;
    foreach (const QJsonValue& thread, threads) {
        QJsonArray posts = thread.toObject()["posts"].toArray();
        ThreadData currentThread;

        foreach (const QJsonValue& post, posts) {
            QJsonObject postObj = post.toObject();
            PostData postData;

            if(postObj["resto"] == 0)
            {
                QString threadNo = QString::number(postObj["no"].toInt());
                currentThread.no = threadNo;
            }
            postData.name = postObj["name"].toString();
            postData.com = postObj["com"].toString();
            postData.no  = QString::number(postObj["no"].toInt());

            currentThread.posts.push_back(postData);

        }

        threadsVector.push_back(currentThread);
    }
    return threadsVector;
}

QStringList PostParser::getThreadNumbersFromFrontPageJson(QJsonArray threads)
{
    QStringList threadNumbers;
    foreach (const QJsonValue& thread, threads) {
        QJsonArray posts = thread.toObject()["posts"].toArray();
        QJsonObject postObj = posts[0].toObject();
        if(postObj["resto"] == 0)
        {
            QString threadNo = QString::number(postObj["no"].toInt());
            threadNumbers << threadNo;
        }
    }
    return threadNumbers;
}

QJsonArray PostParser::getPostsFromThreadNumber(QString threadNo, QJsonArray threads)
{
    QJsonArray posts;
    foreach (const QJsonValue& thread, threads) {
        posts = thread.toObject()["posts"].toArray();
        QJsonObject postObj = posts[0].toObject();
        if(postObj["resto"] == 0)
        {
            QString currThreadNo = QString::number(postObj["no"].toInt());
            if(currThreadNo == threadNo)
            {
                return posts;
            }
        }
    }
    qDebug() << "PostParser::getPostsFromThreadNumber ERROR: Did not find thread";
    return posts;
}
