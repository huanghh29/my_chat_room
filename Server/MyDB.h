#ifndef _MYDB_H
#define _MyDB_H
#include <string>
#include <mysql/mysql.h>
class MyDB{
public:
    MyDB();
    ~MyDB();
    bool initDB(string host, string user, string password, string db_name);
    bool exeSQL(string sql);
    MYSQL_RES *exeSelectSQL(string sql);
    int exeOtherSQL(string sql);

private:
    MYSQL *mysql;
    // MYSQL_RES *result;
    // MYSQL_ROW row;
};
#endif