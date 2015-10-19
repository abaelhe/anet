#ifndef NET_DEFAULT_PACKET_STREAMER_H_
#define NET_DEFAULT_PACKET_STREAMER_H_

namespace net {

class DefaultPacketStreamer : public IPacketStreamer {

public:
DefaultPacketStreamer();

DefaultPacketStreamer(IPacketFactory *factory);

~DefaultPacketStreamer();

void setPacketFactory(IPacketFactory *factory);

bool getPacketInfo(DataBuffer *input, PacketHeader *header, bool *broken);

Packet *decode(DataBuffer *input, PacketHeader *header);

bool encode(Packet *packet, DataBuffer *output);

static void setPacketFlag(int flag);

public:
static int _nPacketFlag;
};

}

#endif /*DEFAULT_PACKET_STREAMER_H_*/