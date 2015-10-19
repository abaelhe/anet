
#ifndef SYS_MUTEX_H_
#define SYS_MUTEX_H_

#include <assert.h>

namespace sys {


class CThreadMutex {

public:
CThreadMutex() {
//assert(pthread_mutex_init(&_mutex, NULL) == 0);
const int iRet = pthread_mutex_init(&_mutex, NULL);
(void) iRet;
assert( iRet == 0 );
}

~CThreadMutex() {
pthread_mutex_destroy(&_mutex);
}


void lock () {
pthread_mutex_lock(&_mutex);
}


int trylock () {
return pthread_mutex_trylock(&_mutex);
}

void unlock() {
pthread_mutex_unlock(&_mutex);
}

protected:

pthread_mutex_t _mutex;
};

class CThreadGuard
{
public:
CThreadGuard(CThreadMutex *mutex)
{
_mutex = NULL;
if (mutex) {
_mutex = mutex;
_mutex->lock();
}
}
~CThreadGuard()
{
if (_mutex) {
_mutex->unlock();
}
}
private:
CThreadMutex *_mutex;
};

}

#endif /*MUTEX_H_*/