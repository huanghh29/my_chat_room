#include "Client.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;
int sock_fd;

void* thread(void* arg){
    if(arg==NULL){
        arg = NULL;
    }
    int ret, recv_len;
    char recv_buf[BUF_SIZE];
    Message msg;
    while(1){
        if(my_mutex)
            continue;
        recv_len = 0;
        while(recv_len<BUF_SIZE){
            ret = recv(sock_fd, recv_buf + recv_len, BUF_SIZE-recv_len, 0);
            if(ret==0){
                cerr << "连接断开" << endl;
                exit(0);
            }
            recv_len += ret;
        }
        memset(&msg, 0, sizeof(msg));
        switch(msg.type){
            
        }
    }
    return NULL;
}

Client(/* args */){
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    // sock_id = 0;
}

void Client::connect(){
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd<0){
        cerr<<"socket error"<<endl;
        exit(0);
    }
    if(connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in))<0){
        cerr << "connect error" << endl;
    }
}

void start(){
    connect();
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread, NULL);
}

void close(){
    close(sock_fd);
}

~Client(){

}