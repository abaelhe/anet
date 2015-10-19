
#ifndef SYS_RUNNABLE_H_
#define SYS_RUNNABLE_H_

namespace sys {

class Runnable {

public:
virtual ~Runnable() {
}
virtual void run(CThread *thread, void *arg) = 0;
};

}

#endif /*RUNNABLE_H_*/