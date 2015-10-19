#ifndef NET_CONNECTION_H_
#define NET_CONNECTION_H_

#define READ_WRITE_SIZE 8192
#ifndef UNUSED
#define UNUSED(v) ((void)(v))
#endif

namespace net {

class Connection {

public:
Connection(Socket *socket, IPacketStreamer *streamer, IServerAdapter *serverAdapter);

virtual ~Connection();

void setServer(bool isServer) {
_isServer = isServer;
}

void setIOComponent(IOComponent *ioc) {
_iocomponent = ioc;
}

IOComponent *getIOComponent() {
return _iocomponent;
}
void setDefaultPacketHandler(IPacketHandler *ph) {
_defaultPacketHandler = ph;
}

bool postPacket(Packet *packet, IPacketHandler *packetHandler = NULL, void *args = NULL, bool noblocking = true);

bool handlePacket(DataBuffer *input, PacketHeader *header);

bool checkTimeout(int64_t now);

virtual bool writeData() = 0;

virtual bool readData() = 0;

virtual void setWriteFinishClose(bool v) {
UNUSED(v);
}

void setQueueTimeout(int queueTimeout) {
_queueTimeout = queueTimeout;
}

virtual void clearOutputBuffer() {
;
}

void setQueueLimit(int limit) {
_queueLimit = limit;
}

bool isConnectState();

uint64_t getServerId() {
if (_socket) {
return _socket->getId();
}
return 0;
}

uint64_t getPeerId() {
if (_socket) {
return _socket->getPeerId();
}
return 0;
}

int getLocalPort() {
if (_socket) {
return _socket->getLocalPort();
}
return -1;
}

protected:
void disconnect();

protected:
IPacketHandler *_defaultPacketHandler;  // connection的默认的packet handler
bool _isServer;                         // 是服务器端
IOComponent *_iocomponent;
Socket *_socket;                        // Socket句柄
IPacketStreamer *_streamer;             // Packet解析
IServerAdapter *_serverAdapter;         // 服务器适配器

PacketQueue _outputQueue;               // 发送队列
PacketQueue _inputQueue;                // 发送队列
PacketQueue _myQueue;                   // 在write中处理时暂时用
sys::CThreadCond _outputCond;         // 发送队列的条件变量
ChannelPool _channelPool;               // channel pool
int _queueTimeout;                      // 队列超时时间
int _queueTotalSize;                    // 队列总长度
int _queueLimit;                        // 队列最长长度, 如果超过这个值post进来就会被wait
};
}

#endif /*CONNECTION_H_*/