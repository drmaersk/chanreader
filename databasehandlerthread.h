#ifndef DATABASEHANDLERTHREAD_H
#define DATABASEHANDLERTHREAD_H
#include <QObject>
#include <QThread>
#include <QMutex>

class DatabaseHandlerThread : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
public:
    DatabaseHandlerThread(QObject *parent = 0);
public slots:
    void testSlot(QString test);
private:
    bool m_gotsignal;
    QMutex m_mutex;
    QStringList m_test;
};

#endif // DATABASEHANDLERTHREAD_H
