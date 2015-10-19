#ifndef NET_TCPACCEPTOR_H_
#define NET_TCPACCEPTOR_H_

namespace net {

class UDPAcceptor : public UDPComponent {

public:
UDPAcceptor(Transport *owner, char *spec, IPacketStreamer *streamer, IServerAdapter *serverAdapter);

bool handleReadEvent();

bool handleWriteEvent() {
return false;
}
};
}

#endif /*TCPACCEPTOR_H_*/