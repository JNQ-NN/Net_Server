#ifndef __REDIS_OPERATION__
#define __REDIS_OPERATION__

#include <iostream>
#include <vector>
#include <thread>
#include <map>
#include <sw/redis++/redis++.h>
using namespace std;
using namespace sw::redis;
#include "mysql_operation.h"
#include "json.h"
#include "tool.h"

/* #define REDIS_TYPE */
    #define REDIS_STRING 1
    #define REDIS_SET    2
    #define REDIS_LIST   3
    #define REDIS_HASH   4
    #define REDIS_ZSET   5

namespace RedisMSG{
    void checkRedisConnection();
    void sendUserMessage(const char* fromUser,const char* toUser,const char* msg);
    void getUserMessage(const char* fromUser,vector<string>& msgs);
    void sendGroupMessage(const char* fromUser,const char* toGroup,const char* msg);
    void getGroupMessage(const char* toGroup,vector<string>&msgs);

    void appendList(const char* listName,string listContent);
    void appendSet(const char* setName,string setContent);
    bool queryExistSetElement(const char* setName,const char* setContent);
};

#endif