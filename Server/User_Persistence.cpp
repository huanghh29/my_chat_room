#include "User_Persistence.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MySQL.h"
#include "../Common.h"

extern MyDB db;

bool User_Persistence_IsUserName(string name){
    MYSQL_RES *res;
    MYSQL_ROW row;
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "select * from users where name = '%s'", name.c_str());
    res = db.exeSelectSQL(sql);
    row = mysql_num_rows(res);
    mysql_free_result(res);
    if(row>0){
        return true;
    }
    return false;
}

bool User_Persistence_MatchNameAndPassword(string name, string password){
    MYSQL_RES *res;
    MYSQL_ROW row;
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "select * from users where name='%s' and password='%s'", name.c_str(), password.c_str());
    res = db.exeSelectSQL(sql);
    row = mysql_num_rows(res);
    mysql_free_result(res);
    if(row>0)
        return true;
    return false;
}

bool User_Persistence_AddUser(string name, string password){
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "insert into users values (null, '%s', md5('%s'), null, null)", name, password);
    int row = db.exeOtherSQL(sql);
    if(row>0){
        return true;
    }
    return false;
}

bool User_Persistence_DeleteUser(string name){
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "delete from users where name = '%s'", name);
    int row = db.exeOtherSQL(sql);
    if(row>0){
        return true;
    }
    return false;
}

