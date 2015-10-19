#ifndef NET_IPACKETSTREAMER_H_
#define NET_IPACKETSTREAMER_H_

namespace net {

class IPacketStreamer {

public:
IPacketStreamer() {
_factory = NULL;
_existPacketHeader = true;
}

IPacketStreamer(IPacketFactory *factory) {
_factory = factory;
_existPacketHeader = true;
}

virtual ~IPacketStreamer() {}

virtual bool getPacketInfo(DataBuffer *input, PacketHeader *header, bool *broken) = 0;

virtual Packet *decode(DataBuffer *input, PacketHeader *header) = 0;

virtual bool encode(Packet *packet, DataBuffer *output) = 0;

bool existPacketHeader() {
return _existPacketHeader;
}

protected:
IPacketFactory *_factory;   // 产生packet
bool _existPacketHeader;    // 是否有packet header, 如http有自己协议就不需要输出头信息
};
}

#endif /*RUNNABLE_H_*/