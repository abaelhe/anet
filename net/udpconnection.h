#ifndef NET_UDPCONNECTION_H_
#define NET_UDPCONNECTION_H_

namespace net {

class UDPConnection : public Connection {
UDPConnection(Socket *socket, IPacketStreamer *streamer, IServerAdapter *serverAdapter);

~UDPConnection();

bool writeData();

bool readData();

};

}

#endif /*UDPCONNECTION_H_*/