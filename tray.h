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
    QAction* full_screenshot;

    bool is_enable_pop_up;

public:
    explicit Tray(MainWindow *parent = nullptr);
    ~Tray();

    void show_msg(QString arg);
    void set_enable_pop_up(bool);

public slots:

    void show_context_menu(QSystemTrayIcon::ActivationReason reason);
    void open_directory();

};

#endif // TRAY_H
