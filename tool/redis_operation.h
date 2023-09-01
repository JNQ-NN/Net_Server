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

namespace RedisMSG{
    void checkRedisConnection();
    void sendUserMessage(const char* fromUser,const char* toUser,const char* msg);
    void getUserMessage(const char* fromUser,vector<string>& msgs);
    void sendGroupMessage(const char* fromUser,const char* toGroup,const char* msg);
    void getGroupMessage(const char* toGroup,vector<string>&msgs);
};

#endif