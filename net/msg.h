#ifndef __MSG_H__
#define __MSG_H__
#include <iostream>
#include <string.h>
using namespace std;
#include "../tool/json.h"

struct Msg{
    size_t msgHeadLen_;
};


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