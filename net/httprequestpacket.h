#ifndef NET_HTTP_REQUEST_PACKET_H
#define NET_HTTP_REQUEST_PACKET_H

namespace net {

struct eqstr {
bool operator()(const char* s1, const char* s2) const {
return strcmp(s1, s2) == 0;
}
};
typedef __gnu_cxx::hash_map<const char*, const char*, __gnu_cxx::hash<const char*>, eqstr> PSTR_MAP;
typedef PSTR_MAP::iterator PSTR_MAP_ITER;

class HttpRequestPacket : public Packet {
public:
HttpRequestPacket();

~HttpRequestPacket();

void countDataLen();
bool encode(DataBuffer *output);

bool decode(DataBuffer *input, PacketHeader *header);

const char *findHeader(const char *name);

Connection *getConnection();

void setConnection(Connection *connection);
public:
char *strHeader;       // 保存头内容的buffer
char *strQuery;        // 查询串
bool bKeepAlive;      // 是否支持keepalive
int method;            // get - 1
private:
PSTR_MAP _headerMap;    // 其他头信息的map

net::Connection *_connection; // 存connection
};

}

#endif
