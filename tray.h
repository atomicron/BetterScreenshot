#ifndef TRAY_H
#define TRAY_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

class Tray : protected QSystemTrayIcon
{
    Q_OBJECT
    QMenu* menu;
    QAction* quit;
    QAction* settings;

public:
    explicit Tray(QObject *parent = nullptr);
    ~Tray();

    void show_msg(QString arg);

public slots:

    void show_context_menu(QSystemTrayIcon::ActivationReason);

};

#endif // TRAY_H
