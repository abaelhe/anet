#ifndef NET_CHANNEL_POOL_H_
#define NET_CHANNEL_POOL_H_

#define CHANNEL_CLUSTER_SIZE 25
namespace net {

class ChannelPool {

public:
ChannelPool();

~ChannelPool();

Channel *allocChannel();

bool freeChannel(Channel *channel);
bool appendChannel(Channel *channel);

Channel* offerChannel(uint32_t id);

Channel* getTimeoutList(int64_t now);

bool appendFreeList(Channel *addList);

int getUseListCount() {
return static_cast<int32_t>(_useMap.size());
}

void setExpireTime(Channel *channel, int64_t now);

private:
__gnu_cxx::hash_map<uint32_t, Channel*> _useMap; // 使用的map
std::list<Channel*> _clusterList;                // cluster list
sys::CThreadMutex _mutex;

Channel *_freeListHead;             // 空的链表
Channel *_freeListTail;
Channel *_useListHead;              // 被使用的链表
Channel *_useListTail;
int _maxUseCount;                   // 被用链表的长度

static atomic_t _globalChannelId;   // 生成统一的id
static atomic_t _globalTotalCount;
};

}

#endif /*CHANNEL_POOL_H_*/