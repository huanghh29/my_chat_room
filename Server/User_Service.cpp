#include "User_Service.h"
#include "User_Persistence.h"
#include "Friend_Persistence_GetList.h"
#include <iostream>
#include <string>
#include <map>
using namespace Json;

extern map<int, string> ClientToUser;
extern map<string, int> UserToClient;

bool User_Service_Notify_Online(string name, bool online){
    char send_buf[BUF_SIZE];
    memset(send_buf, 0, sizeof(send_buf));
    Value root;
    Value arrayObj;
    Value item;
    Message msg;
    memset(&msg, 0, sizeof(msg));
    vector<string> friends = Friend_Persistence_GetList(name);
    msg.type = Notify;
    msg.code = online?Online:Offline;
    success = true;
    strcpy(msg.name, name);
    for (int i = 0; i < friends.size();i++){
        auto it = UserToClient.find(friends[i]);
        if(it!=UserToClient.end()){
            int client_fd = (*it).second;
            memcpy(send_buf, &msg, sizeof(msg));
            if(send(client_fd, send_buf, BUF_SIZE, 0)<0){
                success = false;
            }
        }
    }
    return success;
}

bool User_Service_Login(int client_fd, Message from_msg){
    string name = from_msg.name;
    string password = from_msg.content;
    char send_buf[BUF_SIZE];
    Message msg;
    bool success = false;
    memset(send_buf, 0, BUF_SIZE);
    memset(&msg, 0, sizeof(msg));
    auto it = UserToClient.find(name);
    if(it!=UserToClient.end()){
        int old_client_fd = (*it).second;
        msg.type = ForceOffline;
        memcpy(send_buf, &msg, sizeof(msg));
        if(send(old_client_fd, send_buf, sizeof(send_buf), 0)<0){
            cout << "send error" << endl;
        }
        ClientToUser[old_client_fd] = "";
        UserToClient.erase(it);
    }
    msg.type = Login;
    bool is_user_name = User_Persistence_IsUserName(name);
    if(is_user_name){
        bool is_match = User_Persistence_MatchNameAndPassword(name, password);
        if(is_match){
            msg.code = LoginSuccess;
            success = true;
        }
        else{
            msg.code = WrongPassword;
            success = false;
        }
    }
    else{
        msg.code = UserNotExist;
        success = false;
    }
    memcpy(send_buf, &msg, sizeof(msg));
    if(send(client_fd, send_buf, BUF_SIZE, 0)<0){
        cout << "send error" << endl;
        success = false;
    }
    if(success){
        ClientToUser[client_fd] = name;
        UserToClient[name] = client_fd;
        User_Service_Notify_Online(name, true);
    }
    return success;
}

bool User_Service_Signin(int client_fd, Message from_msg){
    char name = from_msg.name;
    string password = from_msg.content;
    Message msg;
    memset(&msg, 0, sizeof(msg));
    char send_buf[BUF_SIZE];
    memset(send_buf, 0, BUF_SIZE);
    int flag = User_Persistence_AddUser(name, password);
    bool success = flag>0?true:false;
    msg.type = Signin;
    if(success){
        Message.code = SigninSuccess;
    }
    else{
        Message.code = UserAlreadyExist;
    }
    memcpy(send_buf, &msg, sizeof(msg));
    if(send(client_fd, send_buf, BUF_SIZE, 0)<0){
        cout << "send error" << endl;
    }
    return success;
}

bool User_Service_Logout(int client_fd, Message from_msg){
    char name = from_msg.name;
    Message msg;
    memset(&msg, 0, sizeof(msg));
    char send_buf[BUF_SIZE];
    memset(send_buf, 0, BUF_SIZE);
    msg.type = Logout;
    //int flag = User_Persistence_Logout(name);
    //bool success = flag > 0 ? true : false;
    //msg.code = success ? LogoutSuccess : LogoutFail;
    memcpy(send_buf, &msg, sizeof(msg));
    if(send(client_fd, send_buf, BUF_SIZE, 0)<0){
        cout << "send error" << endl;
        return false;
    }
    ClientToUser[client_fd] = "";
    UsertoClient.erase(name);
    User_Service_Notify_Online(name, false);
    return true;
}


void User_Service_ClientDisConnect(int client_fd){
    string name = ClientToUser[client_fd];
    ClientToUser.erase(client_fd);
    if(name!=""){
        UserToClient.erase(name);
        User_Service_Notify_Online(name, false);
    }
}