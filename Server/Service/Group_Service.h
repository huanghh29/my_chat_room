#ifndef _GROUP_SERVICE_H
#define _GROUP_SERVICE_H
#include "../Common.h"

bool Group_Service_CreateGroup(int client_fd, Message msg_in);

bool Group_Service_InviteMember(int client_fd, Message msg_in);

bool Group_Service_JoinGroup(int client_fd, Message msg_in);

bool Group_Service_GetList(int client_fd, Message msg_in);

bool Group_Service_ShowMember(int client_fd, Message msg_in);


#endif