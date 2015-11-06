#include "databasehandlerthread.h"
#include <QDebug>

DatabaseHandlerThread::DatabaseHandlerThread(QObject *parent) :
    QThread(parent),
    m_gotsignal(false),
    m_mutex(),
    m_test()
{

}


void DatabaseHandlerThread::run()
{
    forever{
        m_mutex.lock();
        if(m_gotsignal)
        {
            qDebug() << "received a signal size == " << m_test.size();
//            foreach(QString t, m_test){
//                qDebug() << t;
//            }

            QThread::msleep(500);
            m_gotsignal = false;
        }
        m_mutex.unlock();

//        QThread::msleep(200);
//        exec();
        //        qDebug() << "loop";
    }
}

void DatabaseHandlerThread::testSlot(QString test)
{
    m_mutex.lock();
    m_gotsignal = true;
    m_test.push_back(test);
    m_mutex.unlock();

}
