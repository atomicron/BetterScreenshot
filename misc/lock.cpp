#include "lock.h"
#include "msgbox.h"

#include "misc/os.h"

#if LINUX_OS
#include <iostream>
#endif

Lock::Lock(const QString &fileName)
    : QLockFile(fileName)
{
    if (!tryLock()) {
        MsgBox("An instance of this program is already running");
#if LINUX_OS
        std::cerr << "The program could not obtain a lock file, one already exists.\n";
#endif
        exit(66);
    }
}
