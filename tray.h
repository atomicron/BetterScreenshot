#ifndef TRAY_H
#define TRAY_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

class MainWindow;

class Tray : public QSystemTrayIcon
{
    Q_OBJECT

    MainWindow* mw;

    QMenu* menu;
    QAction* full_screenshot;
    QAction* snipe;
    QAction* open_save_dir;
    QAction* settings;
    QAction* quit;
    void add_clickies();
    void connect_clickies();

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
