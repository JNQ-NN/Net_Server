#ifndef __MSG_H__
#define __MSG_H__
#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;
#include "../tool/json.h"

#define MSGHEAD_LEN  10 //消息头长度 10[MSGNODE_LEN]

/* Mysql */
#define MSGMODE_MYSQL_QUERY_EXIST   1   //查询条件下，是否存在
#define MSGMODE_MYSQL_QUERY_ALL     2   //查询条件下，所有信息并返回
#define MSGMODE_MYSQL_USER_APPEND   3   //添加用户
/* Redis */
#define MSGMODE_REDIS_QUERY_EXIST   11  //查询条件下，是否存在
#define MSGMODE_REDIS_USER_SENDMSG  12  //发送用户消息
#define MSGMODE_REDIS_USER_SHOWMSG  13  //查询和指定用户消息
#define MSGMODE_REDIS_GROUP_SENDMSG 14  //发送群组消息
#define MSGMODE_REDIS_GROUP_SHOWMSG 15  //查询和指定群组消息

/*
* @brief 消息体
*/
class MsgNode{
public:
    MsgNode();
    MsgNode(size_t msgMaxLen);
    MsgNode(const char* msg,unsigned int msgMaxLen);
    MsgNode(Json* jt);

    char* getMsg();
    Json getJson();
    void resize(size_t newMaxSize);
    void msgClear();
    size_t getMsgMaxLen();
    size_t getMsgCurLen();

private:
    char* msg_;
    size_t msgMaxLen_;
    size_t msgCurLen_;
};

/*
* @brief 消息 
*/
struct Msg{
    size_t msgHeadLen_;  //消息头 保存消息体的长度
    char* msgHead;
    size_t msgNodeLen_;  //消息体 保存消息
    MsgNode msg;
};

namespace MSG{
    string packing(char* msgBody);
    string packing(Json* json);
};

#endif