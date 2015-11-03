#include "threaddownloader.h"

ThreadDownloader::ThreadDownloader(QObject *parent) : QThread(parent)
{

}

void ThreadDownloader::run()
{
    for(int i = 0; i < 10; i++)
    {
        sleep(1);
        qDebug() << "sleeping " << (i+1);
    }
}



