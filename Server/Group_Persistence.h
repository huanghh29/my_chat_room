#ifndef _GROUP_PERSISTENCE_H
#define _GROUP_PERSISTENCE_H

#include<string>
#include<vector>
using namespace std;

bool Group_Persistence_IsGroup(string gname);

bool Group_Persistence_Add(string gname,string uname);

bool Group_Persistence_Delete(string gname);

bool Group_Persistence_AddMember(string gname, string uname);

bool Group_Persistence_DeleteMember(string gname, string uname);

vector<string> Group_Persistence_GetGroupList(string uname);

vector<string> Group_Persistence_GetGroupMember(string gname);


#endif