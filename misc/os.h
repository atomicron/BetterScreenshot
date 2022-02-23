// Used to help determine the OS
// Defines LINUX_OS or WINDOWS_OS

#ifndef OS_H
#define OS_H

#if defined(_WIN32)
    #define WINDOWS_OS 1
    #define LINUX_OS 0
#elif defined(_WIN64)
    #define WINDOWS_OS 1
    #define LINUX_OS 0
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define WINDOWS_OS 1
    #define LINUX_OS 0
#elif defined(__linux__)
    #define LINUX_OS 1
    #define WINDOWS_IS 0
#endif

#endif // OS_H
