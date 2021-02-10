#include "tray.h"

Tray::Tray(QObject *parent) : QSystemTrayIcon(parent)
  , menu(new QMenu)
{
    setIcon(QIcon("E:\\Qt\\Projects\\BetterScreenshot\\BS.png"));
    setVisible(true);

    settings = new QAction("Settings");
    quit = new QAction("Quit");
    menu->addAction(settings);
    menu->addAction(quit);

    setContextMenu(menu);

    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(show_context_menu(QSystemTrayIcon::ActivationReason)));
    connect(quit, SIGNAL(triggered()), parent, SLOT(quit()));
    connect(settings, SIGNAL(triggered()), parent, SLOT(show()));
}

Tray::~Tray()
{
   delete settings;
   delete quit;
   delete menu;
}

void Tray::show_context_menu(ActivationReason)
{
   menu->show();
}
