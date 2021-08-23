#ifndef _USER_SERVICE_H
#define _USER_SERVICE_H
#include "../Common.h"

bool User_Service_Login(int client_fd, Message msg);

bool User_Service_Signin(int client_fd, Message msg);

bool User_Service_Logout(int client_fd, Message msg);

bool User_Service_Notify_Online(string name, bool online);

void User_Service_ClientDisConnect(int client_fd);

#endif