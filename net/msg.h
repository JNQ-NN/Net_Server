#include <iostream>
using namespace std;

struct Msg{
    int mod;                //     
    char usrName[10];       //发送源用户名称
    union{
        char toName[10];    //发送目的用户名称
        char groupName[10]; //发送目的分组名称
        char ipAddress[16]; //发送目的用户ip
    };
    char msg[0xFF];
};