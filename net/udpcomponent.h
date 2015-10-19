#ifndef NET_UDPCOMPONENT_H_
#define NET_UDPCOMPONENT_H_

namespace net {

class UDPComponent : public IOComponent {

public:
UDPComponent(Transport *owner, Socket *socket, IPacketStreamer *streamer, IServerAdapter *serverAdapter);

~UDPComponent();

bool init(bool isServer = false);

void close();

bool handleWriteEvent();

bool handleReadEvent();

private:
__gnu_cxx::hash_map<int, UDPConnection*> _connections;  // UDP连接集合
IPacketStreamer *_streamer;                             // streamer
IServerAdapter *_serverAdapter;                         // serveradapter
};
}

#endif /*UDPCOMPONENT_H_*/