#ifndef THREADDOWNLOADER_H
#define THREADDOWNLOADER_H
#include <QObject>
#include <QThread>
#include <QDebug>

class ThreadDownloader : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
public:
    ThreadDownloader(QObject *parent = 0);
signals:
    Q_SIGNAL void threadDownloaded();

//public slots:
};

#endif // THREADDOWNLOADER_H
