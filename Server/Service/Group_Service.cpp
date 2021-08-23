#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include "Group_Service.h"
#include "Group_Persistence.h"
#include "User_Persistence.h"
#include <string>
#include <iostream>
#include <map>

using namespace std;
using namespace Json;

extern map<string, int> UserToClient;
extern map<int, string> ClientToUser;


bool Group_Service_CreateGroup(int client_fd, Message msg_in){
    bool success = false;
    Message msg_out;
    memset(&msg_out, 0, sizeof(msg_out));
    msg_out.type = CreateGroup;
    char send_buf[BUF_SIZE];
    memset(send_buf, 0, sizeof(send_buf));
    string gname = msg_in.name;
    string uname = ClientToUser[client_fd];
    
    if(Group_Persistence_Add(gname, uname)){
        msg_out.code = Success;
        success = true;
    }
    else{
        msg_out.code = Fail;
        success = false;
    }
    memcpy(send_buf, &msg_out, sizeof(msg_out));
    if(send(client_fd, send_buf, sizeof(send_buf), 0)<0){
        cout << "send error" << endl;
    }
    return success;
}

bool Group_Service_InviteMember(int client_fd, Message msg_in){
    bool success = false;
    char send_buf[BUF_SIZE];
    memset(send_buf, 0, sizeof(send_buf));
    Message msg_out;
    memset(&msg_out, 0, sizeof(msg_out));
    msg_out.type = InviteMember;
    string gname = msg_in.gname;
    string uname = msg_in.uname;
    if(Group_Persistence_AddMember(gname, uname)){
        msg.code = Success;
        success = true;
    }
    else{
        msg.code = UserAlreadyInGroup;
    }
    memcpy(send_buf, &msg_out, sizeof(msg_out));
    if(send(client_fd, send_buf, sizeof(send_buf), 0)<0){
        cout << "send error" << endl;
    }
    if(success){
        Group_Service_JoinGroupNotify(gname, uname, ClientToUser[client_fd]);
    }

    return success;
}

bool Group_Service_JoinGroup(int client_fd, Message msg_in){
    bool success = false;
    char send_buf[BUF_SIZE];
    memset(send_buf, 0, sizeof(send_buf));
    Message msg_out;
    memset(&msg_out, 0, sizeof(msg_out));
    string gname = msg_in.gname;
    string uname = msg_in.uname;
    msg_out.type = JoinGroup;
    if(!Group_Persistence_IsGroup(gname)){
        msg_out.code = GroupNotExist;
    }
    else if(Group_Persistence_AddMember(gname,uname)){
        msg_out.code = Success;
        success = true;
    }
    else{
        msg_out.code = UserAlreadyInGroup;
    }
    memcpy(send_buf, &msg_out, sizeof(msg_out));
    if(send(client_fd, send_buf, sizeof(send_buf), 0)<0){
        cout << "send error" << endl;
    }
    if(success){
        Group_Service_JoinGroupNotify(gname, uname, uname);
    }

}

bool Group_Service_GetList(int client_fd, Message msg_in){
    bool success = false;
    char send_buf[BUF_SIZE];
    memset(send_buf, 0, sizeof(send_buf));
    Message msg_out;
    memset(&msg_out, 0, sizeof(msg_out));
    msg_out.type = GroupGetList;
    string uname = ClientToUser[client_fd];
    vector<string> groupList = Group_Persistence_GetGroupList(uname);
    Value root;
    Value item;
    Value arrayObj;
    for (int i = 0; i < groupList.size();i++){
        item["group"] = groupList[i];
        arrayObj.append(item);
    }
    root["groupList"] = arrayObj;
    string content = root.toStyledString();
    strcpy(msg_out.content, content.c_str());
    memcpy(send_buf, &msg_out, sizeof(msg_out));
    if(send(client_fd, send_buf, BUF_SIZE, 0)<0){
        cout << "send error" << endl;
        return false;
    }
    return true;
}

bool Group_Service_ShowMember(int client_fd, Message msg_in){
    char send_buf[BUF_SIZE];
    memset(send_buf, 0, sizeof(send_buf));
    Message msg_out;
    memset(&msg_out, 0, sizeof(msg_out));
    msg_out.type = GroupShowMember;
    string gname = msg_in.name;
    vector<string> memberList = Group_Persistence_GetGroupMember(gname);
    Value root;
    Value item;
    Value arrayObj;
    for (int i = 0; i < memberList.size();i++){
        item["member"] = memberList[i];
        arrayObj.append(item);
    }
    root["memberList"] = arrayObj;
    string content = root.toStyledString();
    strcpy(msg_out.content, content.c_str());
    memcpy(send_buf, &msg_out, sizeof(msg_out));
    if(send(client_fd, send_buf, BUF_SIZE, 0)<0){
        cout << "send error" << endl;
        return false;
    }
    return true;
}

bool Group_Service_JoinGroupNotify(string gname, string uname, string inviter){
    string success = true;
    char send_buf[BUF_SIZE];
    memset(send_buf, 0, sizeof(send_buf));
    Message msg_out;
    memset(&msg_out, 0, sizeof(msg_out));
    msg_out.type = JoinGroupNotify;
    msg_out.gname = gname;
    msg_out.uname = uname;
    msg_out.inviter = inviter;
    memcpy(send_buf, &msg_out, sizeof(msg_out));
    vector<string> members = Group_Persistence_GetGroupMember(gname);
    for (int i = 0; i < members.size();i++){
        auto it = UserToClient.find(members[i]);
        if(it!=UserToClient.end()){
            int client_fd = (*it).second;
            if(send(client_fd, send_buf, BUF_SIZE, 0)<0){
                cout << "send error" << endl;
                success = false;
            }
        }
    }
    return success;
}