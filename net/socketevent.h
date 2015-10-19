#ifndef NET_SOCKETEVENT_H_
#define NET_SOCKETEVENT_H_

namespace net {

#define MAX_SOCKET_EVENTS 256

class IOEvent {

public:
bool _readOccurred;  // 读发生
bool _writeOccurred;  // 写发生
bool _errorOccurred;  // 错误发生
IOComponent *_ioc;  // 回传参数
};

class SocketEvent {

public:
SocketEvent();
virtual ~SocketEvent();
virtual bool addEvent(Socket *socket, bool enableRead, bool enableWrite) = 0;

virtual bool setEvent(Socket *socket, bool enableRead, bool enableWrite) = 0;

virtual bool removeEvent(Socket *socket) = 0;

virtual int getEvents(int timeout, IOEvent *events, int cnt) = 0;
};
}

#endif /*SOCKETEVENT_H_*/