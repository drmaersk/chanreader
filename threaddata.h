#ifndef THREADDATA
#define THREADDATA
#include <QString>
#include <QMetaType>

struct PostData {
QString no;
QString name;
QString com;
QString resto;
};

class ThreadData
{
    public:
    QString no;
    QVector<PostData> posts;
};

Q_DECLARE_METATYPE(ThreadData);

#endif // THREADDATA

