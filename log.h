#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDebug>

#define LOG Log::getInstance()

class Log : public QObject
{
    Q_OBJECT

    Log()
    {
        qDebug()<<"Constr";
    }

    static Log *instance;

public:
    static Log* getInstance()
    {
        if (!instance) instance = new Log();
        return instance;
    }

    void operator<<(QString arg)
    {
        qDebug()<<arg;
    }

};

#endif // LOG_H
