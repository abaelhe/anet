#include "net.h"

namespace net {

UDPConnection::UDPConnection(Socket *socket, IPacketStreamer *streamer,
IServerAdapter *serverAdapter) : Connection(socket, streamer, serverAdapter) {}

UDPConnection::~UDPConnection() {}

bool UDPConnection::writeData() {
return true;
}

bool UDPConnection::readData() {
return true;
}

}