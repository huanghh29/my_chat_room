#include <string>
#include <iostream>
#include <cunistd>
#include <cfcntl>
#include <fstream>
#include <mysql/mysql.h>
using namespace std;

MyDB db;
Server server;
map<int, string> ClientToUser;
map<string, int> UserToClient;
// int port;

int main(){
    ifstream infile;
    infile.open("config.txt",ios::in);
    if(!infile){
        cout << "配置文件打开失败" << endl;
        exit(1);
    }
    int port;
    string host, user, password, database;
    infile >> port >> host >> user >> password >> database;
    infile.close();
    db.initDB(host, user, password, database);
    // server.set_port(port);
    server.start();
    return 0;
}