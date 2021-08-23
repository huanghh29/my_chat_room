#ifndef _USER_PERSISTENCE_H
#define _USER_PERSISTENCE_H

#include <string>
bool User_Persistence_IsUserName(string name);
bool User_Persistence_AddUser(string name, string password);
bool User_Persistence_MatchNameAndPassword(string name);
bool User_Persistence_DeleteUser(string name);

#endif