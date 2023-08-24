#ifndef __MSG_H__
#define __MSG_H__
#include <iostream>
#include <string.h>
using namespace std;
#include "../tool/json.h"

#define MSGHEAD_LEN 10 //消息头长度 理论最大传输长度9999999999

// class MsgNode;

// struct Msg{
//     size_t msgHeadLen_;  //消息头 保存消息体的长度
//     char* msgHead;
//     size_t msgNodeLent_; //消息体 保存消息
//     MsgNode msg;
// };


class MsgNode{
public:
    MsgNode();
    MsgNode(size_t msgMaxLen);
    MsgNode(const char* msg,unsigned int msgMaxLen);
    MsgNode(Json* jt);

    char* getMsg();
    void resize(size_t newMaxSize);
    void msgClear();
    size_t getMsgMaxLen();
    size_t getMsgCurLen();

private:
    char* msg_;
    size_t msgMaxLen_;
    size_t msgCurLen_;
};

#endif