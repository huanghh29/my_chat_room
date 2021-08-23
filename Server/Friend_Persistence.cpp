#include "Friend_Persistence_GetList.h"

vector<string> Friend_Persistence_GetList(string name){
    vector<string> friends;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "select fname from friends where (name = '%s' or fname = '%s') and status=1", name);
    res = db.exeSelectSQL(sql);
    int num_rows = mysql_num_rows(res);
    for (int i = 0; i < num_rows;i++){
        row = mysql_fetch_row(res);
        friends.push_back(row[0]);
    }
    mysql_free_result(res);
    return friends;
}

bool Friend_Persistence_Add(string name, string fname){
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "insert into friends values('%s','%s',0, null, null)", name, fname);
    int affected_row = db.exeOtherSQL(sql);
    if(affected_row>0){
        return true;
    }
    return false;
}

bool Friend_Persistence_UpdateStatus(string name, string fname, int status){
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "update friends set status = '%d' where name = '%s' and fname = '%s'", status, name, fname);
    int affected_row = db.exeOtherSQL(sql);
    if(affected_row>0){
        return true;
    }
    return false;
}

bool Friend_Persistence_Delete(string name, string fname){
    char sql[100];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "delete from friends where name = '%s' and fname = '%s'", name, fname);
    int affected_row = db.exeOtherSQL(sql);
    if(affected_row>0){
        return true;
    }
    return false;
}