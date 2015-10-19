#ifndef NET_HTTP_PACKET_STREAMER_H
#define NET_HTTP_PACKET_STREAMER_H

namespace net {


class HttpPacketStreamer : public DefaultPacketStreamer {
public:
HttpPacketStreamer();
HttpPacketStreamer(IPacketFactory *factory);
bool getPacketInfo(DataBuffer *input, PacketHeader *header, bool *broken);
void setHttpPacketCode(int code) {
_httpPacketCode = code;
}
private:
int _httpPacketCode;
};

class DefaultHttpPacketFactory : public IPacketFactory {
public:
Packet *createPacket(int pcode) {
if (pcode == 1) {
return new HttpRequestPacket();
} else {
return new HttpResponsePacket();
}
}
};

}

#endif
