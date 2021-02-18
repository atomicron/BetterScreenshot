#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QTextStream>

#include "msgbox.h"

#define log *Log::getInstance()

class Log
{
    static Log* instance;
    bool enabled;
    QFile *logfile;

    Log() {
        enabled = true;
        createLogfile();
    }

    ~Log() {
        logfile->close();
    }

    void createLogfile() {
        logfile = new QFile("better_screenshot.log");
        if (!logfile->open(QIODevice::WriteOnly | QIODevice::Append))
            MsgBox("Cannot open log file for writing");
    }

public:
    static Log* getInstance() {
        if (!instance)
            instance = new Log;
        return instance;
    }

    template<typename T>
    Log& operator<<(T data) {
        if (enabled) {
            QTextStream out(logfile);
            out << data;
        }
        return *this;
    }

    void truncate() { logfile->resize(0); }
    void setEnable(bool b) { enabled = b; }

};

#endif // LOG_H
