#ifndef TRAY_H
#define TRAY_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

class MainWindow;

class Tray : protected QSystemTrayIcon
{
    Q_OBJECT

    MainWindow* mw;

    QMenu* menu;

    QAction* quit;
    QAction* settings;
    QAction* snipe;
    QAction* open_save_dir;

public:
    explicit Tray(MainWindow *parent = nullptr);
    ~Tray();

    void show_msg(QString arg);

public slots:

    void show_context_menu(QSystemTrayIcon::ActivationReason);
    void open_directory();

};

#endif // TRAY_H
