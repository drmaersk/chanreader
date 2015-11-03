#ifndef THREADDOWNLOADER_H
#define THREADDOWNLOADER_H
#include <QObject>

class ThreadDownloader : public QObject
{
    Q_OBJECT
public:
    ThreadDownloader(QObject *parent = 0, QString thread = "", QStringList fileNames = QStringList ());

signals:
    Q_SIGNAL void threadDownloaded();

//public slots:
};

#endif // THREADDOWNLOADER_H
