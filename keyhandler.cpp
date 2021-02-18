// other headers
#include "keyhandler.h"
#include "mainwindow.h"

#include "misc/os.h"

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

KeyHandler::KeyHandler(MainWindow *parent) : mw(parent) {}

KeyHandler& KeyHandler::Instance(MainWindow *parent)
{
    static KeyHandler thisInstance(parent);
    return thisInstance;
}

#ifdef WINDOWS_OS
bool KeyHandler::enable_hook()
// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowshookexa
// return true of hook was successfully injected
{
    key_hook = SetWindowsHookEx(
                //      int       idHook,
                WH_KEYBOARD_LL,
                //      HOOKPROC  lpfn,
                LowLevelKeyboardProc,
                //      HINSTANCE hmod,
                (HINSTANCE)NULL,
                //      DWORD     dwThreadId
                0
                // GetCurrentThreadId()
                // Use 0 when using WH_KEYBOARD_LL and GetCurrentThreadID() when using WH_KEYBOARD
                );

    return key_hook;
}

bool KeyHandler::disable_hook()
// Return true if unhook was successful
{
    return UnhookWindowsHookEx(key_hook);
}
#endif

#ifdef LINUX_OS
bool KeyHandler::enable_hook()
{
}

bool KeyHandler::disable_hook()
{
}
#endif

void KeyHandler::mw_do_print_screen()
{
    mw->do_print_screen();
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
        return CallNextHookEx(NULL, nCode, wParam, lParam);

    if (wParam == VK_SNAPSHOT)
    {
        // do snapshot
    }

    // Pass the signal onto the chain
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
        return CallNextHookEx(NULL, nCode, wParam, lParam);

    // We get lParam as a LONGLONG but it's a pointer to KBDLLHOOKSTRUCT
    // https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-kbdllhookstruct?redirectedfrom=MSDN
    tagKBDLLHOOKSTRUCT *str = (tagKBDLLHOOKSTRUCT *)lParam;

    if (wParam == WM_KEYDOWN) // true only if key goes down
    {
        if (str->vkCode == VK_SNAPSHOT)
        {
            // do snapshot
            KeyHandler::Instance().mw_do_print_screen();
//            qDebug()<<"Screenshot";
            return 999; // return 1 here and stop the signal
            // returning 1 prevents other applications from receiving the signal!!
        }
    }
    if (wParam == WM_KEYUP)
    {
        if (str->vkCode == VK_SNAPSHOT)
        {
            return 666;
        }
    }

    // If you want to release the message down to the next applications to use
    return CallNextHookEx(NULL, nCode, wParam, lParam);
    // https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms644985(v=vs.85)
    // Return 1 if we don't want others to receive the print screen signal
}
