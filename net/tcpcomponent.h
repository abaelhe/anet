#ifndef NET_TCPCOMPONENT_H_
#define NET_TCPCOMPONENT_H_

namespace net {

class TCPComponent : public IOComponent {
public:
TCPComponent(Transport *owner, Socket *socket,
IPacketStreamer *streamer, IServerAdapter *serverAdapter);

~TCPComponent();

bool init(bool isServer = false);

void close();

bool handleWriteEvent();

bool handleReadEvent();

TCPConnection *getConnection() {
return _connection;
}

void checkTimeout(int64_t now);

bool socketConnect();

private:
// TCPÁ¬½Ó
TCPConnection *_connection;
int64_t _startConnectTime;
};
}

#endif /*TCPCOMPONENT_H_*/