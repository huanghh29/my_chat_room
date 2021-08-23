#include "MyDB.h"
#include <iostream>
using namespace std;

MyDB::MyDB(){
    mysql = mysql_init(NULL);
    if(mysql==NULL){
        cout << "数据库初始化错误:" << mysql_error(mysql);
        exit(1);
    }
}

MyDB::~MyDB(){
    if(mysql!=NULL){
        mysql_close(mysql);
    }
}

bool MyDB::initDB(string host, string user, string password, string db_name){
    mysql = mysql_real_connect(mysql, host.c_str(), user.c_str(), password.c_str(), db_name.c_str(), 0, NULL, 0);
    if(mysql==NULL){
        cout << "数据库连接错误:" << mysql_error(mysql);
        exit(1);
    }
    return true;
}

bool MyDB::exeSQL(string sql, int& affected_rows, MYSQL_RES* res){
    if(mysql_query(mysql,sql.c_str())){
        cout << "Query Error: " << mysql_error(mysql);
        return false;
    }
    else{
        res = mysql_store_result(mysql);
        affected_rows = 0;
        if(!res){
            if(mysql_field_count(mysql)==0){
                affected_rows = mysql_affected_rows(mysql);
            }
            else{
                cout << "Get result error: " << mysql_error(mysql);
                return false;
            }
        }

    }
    return true;
}

MYSQL_RES* MyDB::exeSelectSQL(string sql){
    if(mysql_query(mysql, sql.c_str())){
        cout << "Query Error:" << mysql_error(mysql) << endl;
        return NULL;
    }
    return mysql_store_result(mysql);
}

int MyDB::exeOtherSQL(string sql){
    if(mysql_query(mysql, sql.c_str())){
        cout << "Query Error:" << mysql_error(mysql) << endl;
        return 0;
    }
    return mysql_affected_rows(mysql);
}

