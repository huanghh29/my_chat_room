#include "Chat_Persistence.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"./Chat_Persist.h"
#include<mysql/mysql.h>

using namespace std;
using namespace Json;
extern MyDB db;
bool Chat_Persistence_AddGroupMsg(string gname, string send_name, string recv_name, string message, int is_push){
    char sql[100 + strlen(message)];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "insert into group_messages values(null, '%s', '%s', '%s', '%s', '%d')", gname, send_name, recv_name, message, is_push);
    int rows = db.exeOtherSQL(sql);
    return rows > 0 ? true : false;
}

bool Chat_Persistence_AddPrivateMsg(string from_name, string to_name, string message, int is_push){
    char sql[100 + strlen(message)];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "insert into private_messages values(null, %s', '%s', '%s', '%d')", from_name, to_name, message, is_push);
    int rows = db.exeOtherSQL(sql);
    return rows > 0 ? true : false;
}

vector<MessageRecord> Chat_Persistence_GetPrivateMsg(string name, string fname){
    vector<MessageRecord> msgList;
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "select * from private_messages where (from_name='%s' and to_name='%s') or (from_name='%s' and to_name='%s')", name, fname, fname, name);
    MYSQL_RES *res = db.exeSelectSQL(sql);
    int row = mysql_num_rows(res);
    for (int i = 0; i < row;i++){
        MYSQL_ROW row = mysql_fetch_row(res);
        MessageRecord record(row[])
    }
}

vector<MessageRecord>  Chat_Persistence_GetGroupMsg(string gname);

vector<MessageRecord> Chat_Persistence_GetOfflineGroupMsg(string name);

vector<MessageRecord> Chat_Persistence_GetOfflinePrivateMsg(string name);