#include "net.h"

namespace net {
TCPAcceptor::TCPAcceptor(Transport *owner, Socket *socket,
IPacketStreamer *streamer, IServerAdapter *serverAdapter) : IOComponent(owner, socket) {
_streamer = streamer;
_serverAdapter = serverAdapter;
}

bool TCPAcceptor::init(bool isServer) {
_socket->setSoBlocking(false);
return ((ServerSocket*)_socket)->listen();
}

bool TCPAcceptor::handleReadEvent() {
Socket *socket;
while ((socket = ((ServerSocket*)_socket)->accept()) != NULL) {
//SYS_LOG(INFO, "有新连接进来, fd: %d", socket->getSocketHandle());
// TCPComponent, 在服务器端
TCPComponent *component = new TCPComponent(_owner, socket, _streamer, _serverAdapter);

if (!component->init(true)) {
delete component;
return true;
}

// 加入到iocomponents中，及注册可读到socketevent中
_owner->addComponent(component, true, false);
}

return true;
}

void TCPAcceptor::checkTimeout(int64_t now) {}
}