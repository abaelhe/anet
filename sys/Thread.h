
#ifndef SYSEX_THREAD_H
#define SYSEX_THREAD_H
#include "Shared.h"
#include "Handle.h"
#include "Mutex.h"
#include "Cond.h"
#include "Time.h"

namespace util
{
class Thread : virtual public util::Shared
{
public:

Thread();
virtual ~Thread();

virtual void run() = 0;

int  start(size_t stackSize= 0);

bool isAlive() const;

void _done();

int join();

int detach();

pthread_t id() const;

static void yield();
static void ssleep(const util::Time& timeout);

protected:
bool  _running;   //线程运行标志
bool _started;    //线程是否处于开始状态
bool _detachable; //是否全使线程处于分离状态
pthread_t _thread;//线程ID
util::Mutex _mutex;     //线程运行标志锁
private:
Thread(const Thread&);
Thread& operator=(const Thread&);
};
typedef util::Handle<Thread> ThreadPtr;
}//end namespace util

#endif
