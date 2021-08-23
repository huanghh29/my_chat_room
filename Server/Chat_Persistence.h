#ifndef _CHAT_PERSISTENCE_H
#define _CHAT_PERSISTENCE_H

#include <string>
#include "../Common.h"
using namespace std;

bool Chat_Persistence_AddGroupMsg(string gname, string send_name, string recv_name, string message, int is_push);

bool Chat_Persistence_AddPrivateMsg(string from_name, string to_name, string message, int is_push);

vector<MessageRecord> Chat_Persistence_GetPrivateMsg(string name, string fname);

vector<MessageRecord>  Chat_Persistence_GetGroupMsg(string gname);

vector<MessageRecord> Chat_Persistence_GetOfflineGroupMsg(string name);

vector<MessageRecord> Chat_Persistence_GetOfflinePrivateMsg(string name);

#endif