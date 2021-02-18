#include "tray.h"
#include "mainwindow.h"

#include <QDir>
#include <QDesktopServices>

Tray::Tray(MainWindow *parent)
    : QSystemTrayIcon(parent)
    , mw(parent)
    , menu(new QMenu)
{
    setIcon(QIcon(":/resources/icon/BS.png"));
    setVisible(true);
    setToolTip("Click with left mouse button to snipe");
    setContextMenu(menu);

    add_clickies();
    connect_clickies();
}

Tray::~Tray()
{
    delete settings;
    delete quit;
    delete menu;
    delete open_save_dir;
}

void Tray::add_clickies()
{
    full_screenshot = new QAction("Full screenshot");
    snipe = new QAction("Snipe");
    open_save_dir = new QAction("Open save directory");
    settings = new QAction("Settings");
    quit = new QAction("Quit");

    menu->addAction(full_screenshot);
    menu->addAction(snipe);
    menu->addAction(open_save_dir);
    menu->addAction(settings);
    menu->addAction(quit);
}

void Tray::connect_clickies()
{
    connect(this, SIGNAL(messageClicked()), this, SLOT(open_directory()));
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(show_context_menu(QSystemTrayIcon::ActivationReason)));
    connect(full_screenshot, SIGNAL(triggered()), mw, SLOT(do_screenshot()));
    connect(snipe, SIGNAL(triggered()), mw, SLOT(do_snipe()));
    connect(open_save_dir, SIGNAL(triggered()), this, SLOT(open_directory()));
    connect(settings, SIGNAL(triggered()), mw, SLOT(showNormal()));
    connect(quit, SIGNAL(triggered()), mw, SLOT(custom_quit()));
}

void Tray::show_msg(QString arg)
{
    if (!is_enable_pop_up) return;
    QString title = "BetterScreenshot";
    showMessage(title, arg);
}

void Tray::set_enable_pop_up(bool b)
{
    is_enable_pop_up = b;
}

void Tray::show_context_menu(ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Context)
        menu->show();
    else if(reason == QSystemTrayIcon::Trigger)
        mw->do_snipe();
}

void Tray::open_directory()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(mw->get_save_path()));
}
