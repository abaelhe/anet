#ifndef NET_IOCOMPONENT_H_
#define NET_IOCOMPONENT_H_

namespace net {

#define NET_MAX_TIME (1ll<<62)

class IOComponent {
friend class Transport;

public:
enum {
NET_CONNECTING = 1,
NET_CONNECTED,
NET_CLOSED,
NET_UNCONNECTED
};

public:
IOComponent(Transport *owner, Socket *socket);
virtual ~IOComponent();

virtual bool init(bool isServer = false) = 0;

virtual void close() {}

virtual bool handleWriteEvent() = 0;

virtual bool handleReadEvent() = 0;

virtual void checkTimeout(int64_t now) = 0;

Socket *getSocket() {
return _socket;
}

void setSocketEvent(SocketEvent *socketEvent) {
_socketEvent = socketEvent;
}

void enableWrite(bool writeOn) {
if (_socketEvent) {
_socketEvent->setEvent(_socket, true, writeOn);
}
}

int addRef() {
return atomic_add_return(1, &_refcount);
}

void subRef() {
atomic_dec(&_refcount);
}

int getRef() {
return atomic_read(&_refcount);
}

bool isConnectState() {
return (_state == NET_CONNECTED || _state == NET_CONNECTING);
}

int getState() {
return _state;
}

void setAutoReconn(bool on) {
_autoReconn = on;
}

bool isAutoReconn() {
return (_autoReconn && !_isServer);
}

bool isUsed() {
return _inUsed;
}

void setUsed(bool b) {
_inUsed = b;
}

int64_t getLastUseTime() {
return _lastUseTime;
}

Transport *getOwner();

protected:
Transport *_owner;
Socket *_socket;    // 一个Socket的文件句柄
SocketEvent *_socketEvent;
int _state;         // 连接状态
atomic_t _refcount; // 引用计数
bool _autoReconn;   // 是否重连
bool _isServer;     // 是否为服务器端
bool _inUsed;       // 是否在用
int64_t _lastUseTime;   // 最近使用的系统时间

private:
IOComponent *_prev; // 用于链表
IOComponent *_next; // 用于链表
};
}

#endif /*IOCOMPONENT_H_*/