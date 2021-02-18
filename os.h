#ifndef OS_H
#define OS_H

#if defined(_WIN32)
    #define WINDOWS_OS 1
#elif defined(_WIN64)
    #define WINDOWS_OS 1
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define WINDOWS_OS 1
#elif defined(__linux__)
    #define LINUX_OS 1
#endif

#endif // OS_H
