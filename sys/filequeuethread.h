
#ifndef SYS_FILE_QUEUE_THREAD_H
#define SYS_FILE_QUEUE_THREAD_H

//using namespace std;

namespace sys {
class CFileQueueThread : public CDefaultRunnable {
public:
CFileQueueThread(CFileQueue *queue, int threadCount, IQueueHandler *handler, void *args);
~CFileQueueThread(void);
int writeData(void *data, int len);
void stop();
void run(CThread *thread, void *args);

private:
CThreadCond _mutex;
IQueueHandler *_handler;
void *_args;
CFileQueue *_queue;
};
}

#endif

//////////////////END