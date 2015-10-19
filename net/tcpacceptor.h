#ifndef NET_TCPACCEPTOR_H_
#define NET_TCPACCEPTOR_H_

namespace net {

class TCPAcceptor : public IOComponent {

public:
TCPAcceptor(Transport *owner, Socket *socket,
IPacketStreamer *streamer, IServerAdapter *serverAdapter);

bool init(bool isServer = false);

bool handleReadEvent();

bool handleWriteEvent() {
return true;
}

void checkTimeout(int64_t now);

private:
IPacketStreamer *_streamer;      // 数据包解析器
IServerAdapter  *_serverAdapter; // 服务器适配器
};
}

#endif /*TCPACCEPTOR_H_*/