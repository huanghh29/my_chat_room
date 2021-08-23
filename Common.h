#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define LISTEN_SIZE 12
#define EPOLL_SIZE 5000
#define BUF_SIZE 1024
#define NAME_SIZE 10
#define CONTENT_SIZE 100
// 新用户登录后的欢迎信息
#define SERVER_WELCOME "Welcome you join to the chat room! Your chat ID is: Client #%d"
// 其他用户收到消息的前缀
#define SERVER_MESSAGE "ClientID %d say >> %s"
#define SERVER_PRIVATE_MESSAGE "Client %d say to you privately >> %s"
#define SERVER_PRIVATE_ERROR_MESSAGE "Client %d is not in the chat room yet~"
// 退出系统
#define EXIT "EXIT"
// 提醒你是聊天室中唯一的客户
#define CAUTION "There is only one int the char room!"

enum MessageType
{
    Login,
    Signin,
    AddFriend,
    FriendList,
    CreateGroup,
    GroupList,
    GroupAddMember,
    GroupShowMember,
    QuitGroup,
    ProcessApplication,
    PrivateMessage,
    GroupMessage,
    Logout,
    File,
    ShowPrivateMessage,
    ShowGroupMessage,
    Notify,
    FriendApplyReply,
    BadRequest,
    NewApply
};

enum StatusCode
{
    UserNotExist,
    WrongPassword,
    LoginSuccess,
    SigninSuccess,
    UserAlreadyExist,
    Online,
    Offline,
    FriendApplyAccept,
    FriendApplyReject,
    ApplySuccess,
    ApplyFail
};

struct Message
{
    MessageType type;
    // string from_name;
    StatusCode code;
    char name[NAME_SIZE];
    char content[CONTENT_SIZE];
};

struct MessageRecord{
    string group_name;
    string send_name;
    string send_time;
    string content;
};


void addfd(int epollfd, int fd, bool enable_et);


#endif