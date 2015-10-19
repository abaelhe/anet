#ifndef NET_CHANNEL_H_
#define NET_CHANNEL_H_

namespace net {

class Channel {
friend class ChannelPool;

public:
Channel();

void setId(uint32_t id);

uint32_t getId();

void setArgs(void *args);

void *getArgs();

void setHandler(IPacketHandler *handler);

IPacketHandler *getHandler();

void setExpireTime(int64_t expireTime);

int64_t getExpireTime() {
return _expireTime;
}

Channel *getNext() {
return _next;
}

private:
uint32_t _id;      // channel id
void *_args;    // 回传参数
IPacketHandler *_handler;
int64_t _expireTime; // 到期时间

private:
Channel *_prev;     // 用在链表
Channel *_next;
};
}

#endif /*CONNECTION_H_*/