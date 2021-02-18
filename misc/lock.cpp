#include "lock.h"
#include "msgbox.h"
#include <iostream>

Lock::Lock(const QString &fileName)
    : QLockFile(fileName)
{
    if (!tryLock()) {
        MsgBox("An instance of this program is already running");
        std::cerr << "The program could not obtain a lock file, one already exists.\n";
        exit(66);
    }
}
