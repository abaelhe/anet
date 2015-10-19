#include "net.h"

namespace net {
UDPComponent::UDPComponent(Transport *owner, Socket *socket, IPacketStreamer *streamer,
IServerAdapter *serverAdapter) : IOComponent(owner, socket) {
_streamer = streamer;
_serverAdapter = serverAdapter;
}

UDPComponent::~UDPComponent() {}

bool UDPComponent::init(bool isServer) {
if (!isServer) { // 不要connect, 是accept产生的

if (!_socket->connect()) {
return false;
}
}
_isServer = isServer;
return true;
}

void UDPComponent::close() {}

bool UDPComponent::handleWriteEvent() {
return true;
}

bool UDPComponent::handleReadEvent() {
return true;
}


}