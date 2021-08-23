#include<string>
#include<iostream>
#include<cstring>
using namespace std;
enum MessageType
{
    Login,
    Signin,
    AddFriend,
    FriendList,
    CreateGroup,
    GroupList,
    GroupAddMember,
    GroupShowMember,
    QuitGroup,
    ProcessApplication,
    PrivateMessage,
    GroupMessage,
    Logout,
    File,
    ShowPrivateMessage,
    ShowGroupMessage,
    Notify
};

enum StatusCode
{
    UserNotExist,
    WrongPassword,
    LoginSuccess,
    SigninSuccess,
    UserAlreadyExist,
    Online,
    Offline
};

struct Message
{
    MessageType type;
    // string from_name;
    StatusCode code;
    char name[10];
    char content[100];
};
int main(){
    char name[20] = {'2','3','5','4','7','\0','2'};
    string s = name;
    cout << s << endl;
    sprintf(name, "'%s'", s);
    cout << strlen(name) << endl;
    // char x[100] = s.c_str();
    Message msg;
    msg.type = AddFriend;
    msg.code = LoginSuccess;
    strcpy(msg.content, "123fjsdajfbbte4");
    strcpy(msg.name, "543758");
    char send_buf[1024];

    memcpy(send_buf, &msg, sizeof(msg));
    memcpy(&msg, send_buf, sizeof(msg));
    cout <<"msg"<< sizeof(msg) << endl;
    cout << sizeof(StatusCode) << endl;
    cout << sizeof(MessageType) << endl;
    cout << sizeof(msg.name) << endl;
    cout << sizeof(msg.content) << endl;
    cout << msg.code << endl;
    cout << msg.type << endl;
    cout << msg.name << endl;
    cout << msg.content << endl;
    return 0;
}