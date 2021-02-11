#include "tray.h"
#include <QDir>
#include <QDebug>
#include <QDesktopServices>
#include "mainwindow.h"

Tray::Tray(MainWindow *parent)
    : QSystemTrayIcon(parent)
    , menu(new QMenu)
{
    mw = parent;

    setIcon(QIcon(":/resources/BS.png"));
    setVisible(true);


    settings = new QAction("Settings");
    quit = new QAction("Quit");
    snipe = new QAction("Snipe");
    open_save_dir = new QAction("Open save directory");
    menu->addAction(snipe);
    menu->addAction(open_save_dir);
    menu->addAction(settings);
    menu->addAction(quit);

    setContextMenu(menu);

    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(show_context_menu(QSystemTrayIcon::ActivationReason)));
    connect(quit, SIGNAL(triggered()), parent, SLOT(custom_quit()));
    connect(settings, SIGNAL(triggered()), parent, SLOT(show()));
    connect(this, SIGNAL(messageClicked()), this, SLOT(open_directory()));
    connect(snipe, SIGNAL(triggered()), mw, SLOT(do_snapshot()));
    connect(open_save_dir, SIGNAL(triggered()), this, SLOT(open_directory()));
}

Tray::~Tray()
{
    delete settings;
    delete quit;
    delete menu;
    delete open_save_dir;
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

void Tray::show_context_menu(ActivationReason)
{
    menu->show();
}

void Tray::open_directory()
{
    QDesktopServices::openUrl( QUrl::fromLocalFile(mw->get_save_path()));
}
