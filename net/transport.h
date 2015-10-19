#ifndef NET_TRANSPORT_H_
#define NET_TRANSPORT_H_

#include <sys/ptrace.h>

namespace net {

class Transport : public sys::Runnable {

public:
Transport();

~Transport();

bool start();

bool stop();

bool wait();

void run(sys::CThread *thread, void *arg);

IOComponent *listen(const char *spec, IPacketStreamer *streamer, IServerAdapter *serverAdapter);

Connection *connect(const char *spec, IPacketStreamer *streamer, bool autoReconn = false);

bool disconnect(Connection *conn);

void addComponent(IOComponent *ioc, bool readOn, bool writeOn);

void removeComponent(IOComponent *ioc);

bool* getStop();

private:
int parseAddr(char *src, char **args, int cnt);

void eventLoop(SocketEvent *socketEvent);

void timeoutLoop();

void destroy();

private:

EPollSocketEvent _socketEvent;      // 读写socket事件
sys::CThread _readWriteThread;    // 读写处理线程
sys::CThread _timeoutThread;      // 超时检查线程
bool _stop;                         // 是否被停止

IOComponent *_delListHead, *_delListTail;  // 等待删除的IOComponent集合
IOComponent *_iocListHead, *_iocListTail;   // IOComponent集合
bool _iocListChanged;                       // IOComponent集合被改过
int _iocListCount;
sys::CThreadMutex _iocsMutex;
};
}

#endif /*TRANSPORT_H_*/