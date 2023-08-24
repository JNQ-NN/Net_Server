#ifndef __MSG_H__
#define __MSG_H__
#include <iostream>
#include <string.h>
using namespace std;
#include "../tool/json.h"

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


class MsgNode{
public:
    MsgNode(size_t msgMaxLen);
    MsgNode(const char* msg,unsigned int msgMaxLen);
    MsgNode(Json* jt);

    char* getMsg();
    void msgClear();
    size_t getMsgMaxLen();
    size_t getMsgCurLen(); 

private:
    char* msg_;
    size_t msgMaxLen_;
    size_t msgCurLen_;
};

#endif