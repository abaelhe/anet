#include "net.h"

namespace net {

StatCounter StatCounter::_gStatCounter;

StatCounter::StatCounter() {
clear();
}

StatCounter::~StatCounter() {
}

void StatCounter::log() {
SYS_LOG(INFO, "_packetReadCnt: %llu, _packetWriteCnt: %llu, _dataReadCnt: %llu, _dataWriteCnt: %llu",
_packetReadCnt, _packetWriteCnt, _dataReadCnt, _dataWriteCnt);
}

void StatCounter::clear() {
_packetReadCnt = 0;
_packetWriteCnt = 0;
_dataReadCnt = 0;
_dataWriteCnt = 0;
}

}