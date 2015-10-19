#ifndef NET_TCPCONNECTION_H_
#define NET_TCPCONNECTION_H_

namespace net {

class TCPConnection : public Connection {

public:
TCPConnection(Socket *socket, IPacketStreamer *streamer, IServerAdapter *serverAdapter);

~TCPConnection();

bool writeData();

bool readData();

void setWriteFinishClose(bool v) {
_writeFinishClose = v;
}

void clearOutputBuffer() {
_output.clear();
}

void clearInputBuffer() {
_input.clear();
}

void setDisconnState();

private:
DataBuffer _output;      // 输出的buffer
DataBuffer _input;       // 读入的buffer
PacketHeader _packetHeader; // 读入的packet header
bool _gotHeader;            // packet header已经取过
bool _writeFinishClose;     // 写完断开
};

}

#endif /*TCPCONNECTION_H_*/