#include "net.h"

namespace net {

HttpRequestPacket::HttpRequestPacket() {
strHeader = NULL;
strQuery = NULL;
bKeepAlive = false;
method = 0;
}

HttpRequestPacket::~HttpRequestPacket() {
if (strHeader) {
::free(strHeader);
}
}

bool HttpRequestPacket::encode(DataBuffer *output) {
return true;
}

bool HttpRequestPacket::decode(DataBuffer *input, PacketHeader *header) {
int len = header->_dataLen;
strHeader = (char*) malloc(len+1);
input->readBytes(strHeader, len);
strHeader[len] = '\0';
int line = 0;
int first = 1;

char *p, *name = NULL, *value;
p = value = strHeader;
while (*p) {
// 找每一行
if (*p == '\r' && *(p+1) == '\n') {
if (value == p && line > 0) { // header 结束了
break;
}
*p = '\0';
// 去前空格
while (*value == ' ') value ++;
if (line > 0) {
if (strcmp(name, "Connection") == 0 && strcasecmp(value, "Keep-Alive") == 0) {
bKeepAlive = true;
} else {
_headerMap[name] = value;
}
} else {
strQuery = value;
}
value = p + 2;
line ++;
first = 1;
} else if (line == 0 && *p == ' ') { // 首行
if (method) {
*p = '\0';
} else if (strncmp(value, "GET ", 4) == 0) {    // 是GET 方法
method = 1;
value = p + 1;
}
} else if (*p == ':' && first == 1) {
*p = '\0';
name = value;
value = p + 1;
first = 0;
}
p ++;
}

return true;
}

const char *HttpRequestPacket::findHeader(const char *name) {
PSTR_MAP_ITER it = _headerMap.find(name);
if (it != _headerMap.end()) {
return it->second;
}
return NULL;
}

// Connection
Connection *HttpRequestPacket::getConnection() {
return _connection;
}

// connection
void HttpRequestPacket::setConnection(Connection *connection) {
_connection = connection;
}

}

