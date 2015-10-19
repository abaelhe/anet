#include "net.h"

namespace net {

atomic_t ChannelPool::_globalChannelId = {1};
atomic_t ChannelPool::_globalTotalCount = {0};

ChannelPool::ChannelPool() {
_freeListHead = NULL;
_freeListTail = NULL;
_useListHead = NULL;
_useListTail = NULL;
_maxUseCount = 0;
}

ChannelPool::~ChannelPool() {
std::list<Channel*>::iterator it = _clusterList.begin();

for (;it != _clusterList.end(); it++) {
delete[] *it;
}
}

Channel *ChannelPool::allocChannel() {
Channel *channel = NULL;

_mutex.lock();
if (_freeListHead == NULL) { // 如果是空，新分配一些放到freeList中
assert(CHANNEL_CLUSTER_SIZE>2);
Channel *channelCluster = new Channel[CHANNEL_CLUSTER_SIZE];
SYS_LOG(DEBUG, "分配的Channel总数:%d (%d)", atomic_add_return(CHANNEL_CLUSTER_SIZE, &_globalTotalCount), sizeof(Channel));
_clusterList.push_back(channelCluster);
_freeListHead = _freeListTail = &channelCluster[1];
for (int i = 2; i < CHANNEL_CLUSTER_SIZE; i++) {
_freeListTail->_next = &channelCluster[i];
channelCluster[i]._prev = _freeListTail;
_freeListTail = _freeListTail->_next;
}
_freeListHead->_prev = NULL;
_freeListTail->_next = NULL;
channel = &channelCluster[0];   // 把第一个元素拿过来直接用, 不放到freelist中
} else {
// 从链头取出
channel = _freeListHead;
_freeListHead = _freeListHead->_next;
if (_freeListHead != NULL) {
_freeListHead->_prev = NULL;
} else {
_freeListTail = NULL;
}
}

// 把channel放到_useList中
channel->_prev = _useListTail;
channel->_next = NULL;
channel->_expireTime = NET_MAX_TIME+1;
if (_useListTail == NULL) {
_useListHead = channel;
} else {
_useListTail->_next = channel;
}
_useListTail = channel;

// generate channel id
uint32_t id = atomic_add_return(1, &ChannelPool::_globalChannelId);
id = (id & 0x0FFFFFFF);
if (id == 0)
{
id = 1;
atomic_set(&ChannelPool::_globalChannelId, 1);
}
channel->_id = id;
channel->_handler = NULL;
channel->_args = NULL;

// 把channel放到hashmap中
_useMap[id] = channel;
if (_maxUseCount < (int)_useMap.size()) {
_maxUseCount = _useMap.size();
}
_mutex.unlock();

return channel;
}

bool ChannelPool::freeChannel(Channel *channel) {
__gnu_cxx::hash_map<uint32_t, Channel*>::iterator it;

_mutex.lock();
it = _useMap.find(channel->_id);
if (it == _useMap.end()) {
_mutex.unlock();
return false;
}

// 删除掉
_useMap.erase(it);

// 从_userList删除
if (channel == _useListHead) { // head
_useListHead = channel->_next;
}
if (channel == _useListTail) { // tail
_useListTail = channel->_prev;
}
if (channel->_prev != NULL)
channel->_prev->_next = channel->_next;
if (channel->_next != NULL)
channel->_next->_prev = channel->_prev;

// 加入到_freeList
channel->_prev = _freeListTail;
channel->_next = NULL;
if (_freeListTail == NULL) {
_freeListHead = channel;
} else {
_freeListTail->_next = channel;
}
_freeListTail = channel;
channel->_id = 0;
channel->_handler = NULL;
channel->_args = NULL;

_mutex.unlock();

return true;
}

bool ChannelPool::appendChannel(Channel *channel) {
_mutex.lock();

// 加入到_freeList
channel->_prev = _freeListTail;
channel->_next = NULL;
if (_freeListTail == NULL) {
_freeListHead = channel;
} else {
_freeListTail->_next = channel;
}
_freeListTail = channel;
channel->_id = 0;
channel->_handler = NULL;
channel->_args = NULL;
_mutex.unlock();

return true;
}

Channel *ChannelPool::offerChannel(uint32_t id) {
Channel *channel = NULL;

__gnu_cxx::hash_map<uint32_t, Channel*>::iterator it;
_mutex.lock();
it = _useMap.find(id);
if (it != _useMap.end()) {
channel = it->second;
_useMap.erase(it);

// 从_userList删除
if (channel == _useListHead) { // head
_useListHead = channel->_next;
}
if (channel == _useListTail) { // tail
_useListTail = channel->_prev;
}
if (channel->_prev != NULL)
channel->_prev->_next = channel->_next;
if (channel->_next != NULL)
channel->_next->_prev = channel->_prev;
channel->_prev = NULL;
channel->_next = NULL;
}
_mutex.unlock();

return channel;
}

Channel* ChannelPool::getTimeoutList(int64_t now) {
Channel *list = NULL;

_mutex.lock();
if (_useListHead == NULL) { //是空
_mutex.unlock();
return list;
}

Channel *channel = _useListHead;
while (channel != NULL) {
if (channel->_expireTime >= now) break;
_useMap.erase(channel->_id);
channel = channel->_next;
}

// 有超时的list
if (channel != _useListHead) {
list = _useListHead;
if (channel == NULL) {  // 全部超时
_useListHead = _useListTail = NULL;
} else {
if (channel->_prev != NULL) {
channel->_prev->_next = NULL;
}
channel->_prev = NULL;
_useListHead = channel;
}
}

_mutex.unlock();

return list;
}

bool ChannelPool::appendFreeList(Channel *addList) {
// 是空
if (addList == NULL) {
return true;
}

_mutex.lock();

// 找tail
Channel *tail = addList;
while (tail->_next != NULL) {
tail->_id = 0;
tail->_handler = NULL;
tail->_args = NULL;
tail = tail->_next;
}
tail->_id = 0;
tail->_handler = NULL;
tail->_args = NULL;

// 加入到_freeList
addList->_prev = _freeListTail;
if (_freeListTail == NULL) {
_freeListHead = addList;
} else {
_freeListTail->_next = addList;
}
_freeListTail = tail;

_mutex.unlock();
return true;
}

void ChannelPool::setExpireTime(Channel *channel, int64_t now)
{
_mutex.lock();
if (channel != NULL) {
channel->_expireTime = now;
}
_mutex.unlock();
}

}

