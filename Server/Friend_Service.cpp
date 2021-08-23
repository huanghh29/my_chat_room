#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include "../Common.h"
#include "User_Persistence.h"
#include "Friend_Persistence.h"
using namespace std;
using namespace Json;

extern map<int, string> ClientToUser;
extern map<string, int> UserToClient;

bool Friend_Service_Add(int client_fd, Message from_msg){
    string this_name = ClientToUser[client_fd];
    string that_name = from_msg.name;
    Message msg;
    memset(&msg, 0, sizeof(msg));
    bool is_user_name = User_Persistence_IsUserName(that_name);
    msg.type = AddFriend;
    
    bool success = false;
    if(!is_user_name){
        msg.code = UserNotExist;
        success = false;
    }
    else if(Friend_Persistence_Add(this_name, that_name)){
        msg.code = ApplySuccess;
        success = true;
    }
    else{
        msg.code = ApplyFail;
        success = false;
    }

    //给申请者发送消息
    memcpy(send_buf, &msg, sizeof(msg));
    if(send(client_fd, send_buf, BUF_SIZE, 0)<0){
        cout << "send error" << endl;
    }

    //给被申请者发送消息
    if(msg.code==ApplySuccess){
        auto it = UserToClient.find(that_name);
        if(it!=UserToClient.end()){
            int that_client_fd = (*it).second;
            msg.type = NewApply;
            msg.name = this_name;
            memcpy(send_buf, &msg, sizeof(msg));
            if(send(client_fd, send_buf, BUF_SIZE, 0)<0){
                cout << "send error" << endl;
            }
        }
    }

    return success;
}

bool Friend_Service_GetList(int client_fd, Message in){
    string name = in.name;
    vector<string> friends = Friend_Persistence_GetList(name);
    char send_buf[BUF_SIZE];
    memset(send_buf, 0, BUF_SIZE);
    Message msg;
    memset(&msg, 0, sizeof(msg));
    msg.type = FriendList;
    //vector<string> friends = Friend_Persistence_GetList(name);
    Value root;
    Value item;
    Value arrayObj;
    for (int i = 0; i < friends.size();i++){
        item["friend"] = friends[i];
        arrayObj.append(item);
    }
    root["friendList"] = arrayObj;
    string content = root.toStyledString();
    strcpy(msg.content, content.c_str());
    memcpy(send_buf, &msg, sizeof(msg));
    if(send(client_fd, send_buf, BUF_SIZE, 0)<0){
        cout << "send error" << endl;
        return false;
    }
    return true;
}

bool Friend_Service_Apply(int client_fd, Message in){
    char send_buf[BUF_SIZE];
    memset(send_buf, 0, BUF_SIZE);
    Message out;
    memset(&out, 0, sizeof(out));
    string this_name = ClientToUser[client_fd];
    string that_name = in.name;
    int that_client_fd;
    auto it = UserToClient.find(that_name);
    if(it==UserToClient.end()){
        that_client_fd = -1;
    }
    else{
        that_client_fd = (*it).second;
    }
    out.type = FriendApplyReply;
    out.code = in.code;
    out.name = this_name;
    //memcpy(send_buf, &out, sizeof(out));
    if(in.code==FriendApplyAccept){
        if(Friend_Persistence_UpdateStatus(that_name, this_name, 1)){
            if(that_client_fd>0){
                memcpy(send_buf, &out, sizeof(out));
                if(send(that_client_fd, send_buf, BUF_SIZE, 0)<0){
                    cout << "send error" << endl;
                }
            }
            return true;
        }
        else{
            out.code = BadRequest;
            memcpy(send_buf, &out, sizeof(out));
            if(send(client_fd, send_buf, BUF_SIZE, 0)<0){
                cout << "send error" << endl;
            }
            return false;
        }
    }
    else{
        if(Friend_Persistence_Delete(that_name, this_name)){
            if(that_client_fd>0){
                memcpy(send_buf, &out, sizeof(out));
                if(send(that_client_fd, send_buf, BUF_SIZE, 0)<0){
                    cout << "send error" << endl;
                }
            }
                
            return true;
        }
        else{
            out.code = BadRequest;
            memcpy(send_buf, &out, sizeof(out));
            if(send(client_fd, send_buf, BUF_SIZE, 0)<0){
                cout << "send error" << endl;
            }
            return false;
        }
    }
    return false;
}