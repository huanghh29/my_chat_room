#ifndef _FRIEND_PERSISTENCE_GETLIST_H
#define _FRIEND_PERSISTENCE_GETLIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MySQL.h"
#include "../Common.h"
using namespace std;

extern MyDB db;

vector<string> Friend_Persistence_GetList(string name);

bool Friend_Persistence_Add(string name, string fname);

bool Friend_Persistence_UpdateStatus(string name, string fname, int status);

bool Friend_Persistence_Delete(string name, string fname);

#endif