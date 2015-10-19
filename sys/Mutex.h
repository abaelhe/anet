
#ifndef SYS_MUTEX_H
#define SYS_MUTEX_H

#include <pthread.h>
#include "Lock.h"
#include "ThreadException.h"

namespace util
{
class Mutex
{
public:

typedef LockT<Mutex> Lock;
typedef TryLockT<Mutex> TryLock;

Mutex();
~Mutex();

void lock() const;

bool tryLock() const;

void unlock() const;

bool willUnlock() const;

private:

Mutex(const Mutex&);
Mutex& operator=(const Mutex&);

struct LockState
{
pthread_mutex_t* mutex;
};

void unlock(LockState&) const;
void lock(LockState&) const;
mutable pthread_mutex_t _mutex;

friend class Cond;
};
}//end namespace
#endif