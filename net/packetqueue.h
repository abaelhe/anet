#ifndef NET_PACKET_QUEUE_H_
#define NET_PACKET_QUEUE_H_

namespace net {

class PacketQueue {
friend class PacketQueueThread;
public:
PacketQueue();

~PacketQueue();

Packet *pop();

void clear();

void push(Packet *packet);

int size();

bool empty();

void moveTo(PacketQueue *destQueue);

Packet *getTimeoutList(int64_t now);

Packet *getPacketList();

Packet *head()
{
return _head;
}
Packet* tail()
{
return _tail;
}
protected:
Packet *_head;  // 链头
Packet *_tail;  // 链尾
int _size;      // 元素数量
};

}

#endif
