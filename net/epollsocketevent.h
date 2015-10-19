#ifndef NET_EPOLLSOCKETEVENT_H_
#define NET_EPOLLSOCKETEVENT_H_

namespace net {

class EPollSocketEvent : public SocketEvent {

public:
EPollSocketEvent();

~EPollSocketEvent();

bool addEvent(Socket *socket, bool enableRead, bool enableWrite);

bool setEvent(Socket *socket, bool enableRead, bool enableWrite);

bool removeEvent(Socket *socket);

int getEvents(int timeout, IOEvent *events, int cnt);

private:
int _iepfd;    // epoll的fd
//    sys::CThreadMutex _mutex;  // 对fd操作加锁
};
}

#endif /*EPOLLSOCKETEVENT_H_*/