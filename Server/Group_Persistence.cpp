#include "Group_Persistence.h"
#include<stdio.h>
#include<string.h>
#include "MyDB.h"

extern MyDB db;

bool Group_Persistence_IsGroup(string gname){
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "select * from groups where gname = '%s'", gname);
    MYSQL_RES *res = db.exeSelectSQL(sql);
    int num_rows = mysql_num_rows(res);
    mysql_free_result(res);
    return num_rows > 0 ? true : false;
}

bool Group_Persistence_Add(string gname, string uname){
    char sql[256];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "insert into groups values(null, '%s', '%s', null, null)", gname, uname);
    int affected_row = db.exeOtherSQL(sql);
    return affected_row > 0 ? true : false;
}

bool Group_Persistence_Delete(string gname){}

bool Group_Persistence_AddMember(string gname, string uname){
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "insert into group_members values(null, '%s', '%s', null, null)", gname, uname);
    int affected_row = db.exeOtherSQL(sql);
    return affected_row > 0 ? true : false;
}

bool Group_Persistence_DeleteMember(string gname, string uname);

vector<string> Group_Persistence_GetGroupList(string uname){
    vector<string> groupList;
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "select group_name from group_members where member_name = '%s'", uname);
    MYSQL_RES *res = db.exeSelectSQL(sql);
    MYSQL_ROW row;
    int num_rows = mysql_num_rows(res);
    for (int i = 0; i < num_rows;i++){
        row = mysql_fetch_row(res);
        groupList.push_back(row[0]);
    }
    mysql_free_result(res);
    return groupList;
}

vector<string> Group_Persistence_GetGroupMember(string gname){
    vector<string> memberList;
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "select member_name from group_members where group_name = '%s'", gname);
    MYSQL_RES *res = db.exeSelectSQL(sql);
    MYSQL_ROW row;
    int num_rows = mysql_num_rows(res);
    for (int i = 0; i < num_rows;i++){
        row = mysql_fetch_row(res);
        memberList.push_back(row[0]);
    }
    mysql_free_result(res);
    return memberList;
}