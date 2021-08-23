#include "Server.h"
#include "Common.h"

using namespace std;

void* thread(int arg){

    char msg[BUF_SIZE];
    int client_fd = arg;
    ClientToUser.insert(pair<int, string>(client_fd, ""));
    // MessageType msg_type;
    char recv_buf[BUF_SIZE];
    Message msg;
    // MessageType msg_t;
    memset(recv_buf, 0, BUF_SIZE);
    // char send_buf[BUF_SIZE];
    while(1){
        // bool flag = true;
        int recv_len = 0;
        while(recv_len<BUF_SIZE){
            int ret = recv(client_fd, buf+recv_len, BUF_SIZE-recv_len,0);
            if(ret==0){
                //向在线好友发送下线通知
                User_Service_ClientDisConnect(client_fd);
                server.ClientDisconnect(client_fd);
                cerr << client_fd << " 连接关闭" << endl;
                return NULL;
            }
            if(ret<0){
                server.ClientDisconnect(client_fd);
                cerr << client_fd << " 接收出错" << endl;
                pthread_exit(NULL);
            }
            recv_len += ret;
        }
        // if(flag==false)
        //     continue;
        memset(&msg, 0, sizeof(msg));
        memcpy(&msg, recv_buf, sizeof(msg));
        switch(msg.type){
            case Login:
                User_Service_Login(client_fd, msg);
                break;
            case Signin:
                User_Service_Signin(client_fd, msg);
                break;
            case Logout:
                User_Service_Logout(client_fd, msg);
                break;
            case AddFriend:
                Friend_Service_Add(client_fd, msg);
                break;
            case FriendList:
                Friend_Service_GetList(client_fd, msg);
                break;
            case ProcessApplication:
                Friend_Service_Apply(client_fd, msg);
                break;
            case CreateGroup:
                Group_Service_Create(client_fd, msg);
                break;
            case GroupList:
                Group_Service_GetList(client_fd, msg);
                break;
            case GroupAddMember:
                Group_Service_AddMember(client_fd, msg);
                break;
            case GroupShowMember:
                Group_Service_ShowMember(client_fd, msg);
                break;
            case QuitGroup:
                Group_Service_Quit(client_fd, msg);
                break;
            case PrivateMessage:
                Chat_Service_Private(client_fd, msg);
                break;
            case GroupMessage:
                Chat_Service_Group(client_fd, msg);
                break;
            case File:
                Chat_Service_File(client_fd, msg);
                break;
            case ShowPrivateMessage:
                Chat_Service_ShowPrivateMessage(client_fd, msg);
                break;
            case ShowGroupMessage:
                Chat_Service_ShowGroupMessage(client_fd, msg);
                break;
            case default:
                break;
        }

    }
    return NULL;
}

Server::Server(){
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sinport = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htol(INADDR_ANY);
    sock_fd = 0;
    epfd = 0;       //no use
}

Server::~Server(){

}

Server::init(){
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0){
        cerr << "socket error" << endl;
        exit(0);
    }
    int optval = 1;
    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&optval, sizeof(int))<0){
        cerr << "setsockopt error" << endl;
        exit(0);
    }
    if(bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        cerr << "bind error" << endl;
        exit(0);
    }
    if(listen(sock_fd, LISTEN_SIZE)<0){
        cerr << "listen error" << endl;
        exit(0);
    }
    epfd = epoll_create(EPOLL_SIZE);
    if(epfd<0){
        cerr << "epoll create error" << endl;
        exit(0);
    }
    // addfd(epfd, sock_fd, true);
}

void Server::Close(){
    close(sock_fd);
    close(epfd);
}

void Server::start(){
    static struct epoll_event events[EPOLL_SIZE];
    init();
    while(1){
        struct sockaddr_in client_addr;
        memset(&client_addr, 0, sizeof(client_addr));
        socklen_t client_addr_len = sizeof(struct sockaddr_in);
        int client_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if(client_fd<0){
            cerr << "accept error" << endl;
            exit(0);
        }
        clients.push_back(client_fd);
        pthread_t pthread_id;
        pthread_create(&pthread_id, NULL, thread, client_fd);
    }
}

void Server::ClientDisconnect(int client_fd){
    close(client_fd);
    clients.remove(client_fd);
}