#ifndef LOCK_H
#define LOCK_H

#include <QLockFile>

class Lock : public QLockFile
{

public:
    explicit Lock(const QString& fileName);

};

#endif // LOCK_H
