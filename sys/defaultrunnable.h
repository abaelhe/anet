
#ifndef SYS_DEFAULT_RUNNABLE_H_
#define SYS_DEFAULT_RUNNABLE_H_

namespace sys {

class CDefaultRunnable : public Runnable {

public:
CDefaultRunnable(int threadCount = 1);

virtual ~CDefaultRunnable();

void setThreadCount(int threadCount);

int start();

void stop();

void wait();

protected:
CThread *_thread;
int _threadCount;
bool _stop;
};

}

#endif /*RUNNABLE_H_*/