#ifndef NET_IPACKET_FACTORY_H_
#define NET_IPACKET_FACTORY_H_

namespace net {

class IPacketFactory {
public:
virtual ~IPacketFactory() {};
virtual Packet *createPacket(int pcode) = 0;
};
}

#endif /*IPACKET_FACTORY_H_*/