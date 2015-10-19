#ifndef NET_STATS_H_
#define NET_STATS_H_

namespace net {

class StatCounter {
public:
StatCounter();
~StatCounter();
void log();
void clear();

public:
uint64_t _packetReadCnt;  // # packets read
uint64_t _packetWriteCnt; // # packets written
uint64_t _dataReadCnt;    // # bytes read
uint64_t _dataWriteCnt;   // # bytes written

public:
static StatCounter _gStatCounter; // È«¾Ö

};

#define NET_GLOBAL_STAT net::StatCounter::_gStatCounter
#define NET_COUNT_PACKET_READ(i) {NET_GLOBAL_STAT._packetReadCnt += (i);}
#define NET_COUNT_PACKET_WRITE(i) {NET_GLOBAL_STAT._packetWriteCnt += (i);}
#define NET_COUNT_DATA_READ(i) {NET_GLOBAL_STAT._dataReadCnt += (i);}
#define NET_COUNT_DATA_WRITE(i) {NET_GLOBAL_STAT._dataWriteCnt += (i);}

}

#endif
