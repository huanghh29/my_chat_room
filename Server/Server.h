
#ifndef _CONNECT_H
#define _CONNECT_H
#include <map>
#include <string>
#include <list>
#include "Common.h"

void *thread(int arg);

class Server{
public:
    Server();
    void init();
    void start();
    void close();
    void ClientDisconnect(int client_fd);
    ~Server(){}
private:
    struct sockaddr_in server_addr;
    int sock_fd;
    list<int> client_fds;
};

#endif