
#ifndef _CLIENT_H
#define _CLIENT_H

#include "Common.h"

class Client
{
private:
    /* data */
    // int sock_fd;
    // int pid;
    // int epfd;
    // int pipe_fd[2];
    // bool isClientwork;
    // Message msg;
    // char send_buf[BUF_SIZE];
    // char recv_buf[BUF_SIZE];
    struct sockaddr_in server_addr;

public:
    Client(/* args */);
    void connect();
    void start();
    void close();
    ~Client();
};


#endif 