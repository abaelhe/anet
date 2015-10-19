#ifndef NET_SERVERSOCKET_H_
#define NET_SERVERSOCKET_H_

namespace net {

class ServerSocket : public Socket {

public:
ServerSocket();
Socket *accept();

bool listen();

private:
int _backLog; // backlog
};

}

#endif /*SERVERSOCKET_H_*/