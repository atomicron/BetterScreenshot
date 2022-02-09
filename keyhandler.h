#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include <QObject>

// Windows
#if WINDOWS_OS
#include <windows.h>
#include "Winuser.h"
#endif

class MainWindow;

class KeyHandler : public QObject
{
    Q_OBJECT
    MainWindow *mw;

#if WINDOWS_OS
    HHOOK key_hook;
#endif

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
