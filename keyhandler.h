#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include <QObject>

// Windows
#include <windows.h>
#include "Winuser.h"

class MainWindow;

class KeyHandler : public QObject
{
    Q_OBJECT
    MainWindow *mw;

    HHOOK key_hook;

    KeyHandler(KeyHandler&) {}
    KeyHandler& operator=(KeyHandler) {}

public:
    explicit KeyHandler(MainWindow* parent = nullptr);
    static KeyHandler& Instance(MainWindow* parent = nullptr);

    bool enable_hook();
    bool disable_hook();

    void mw_do_print_screen();

};

#endif // KEYHANDLER_H
