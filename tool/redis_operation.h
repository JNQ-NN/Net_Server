#ifndef __REDIS_OPERATION__
#define __REDIS_OPERATION__

#include <iostream>
#include <vector>
#include <map>
#include <sw/redis++/redis++.h>
using namespace std;
using namespace sw::redis;
#include "mysql_operation.h"

namespace RedisMSG{
    // void redisTest(){
    //     redis.set("key","value");
    //     auto value = redis.get("key");
    //     cout<<*value<<endl;
    // }

    void sendMessage(const char* fromUser,const char* toUser,const char* msg);
}

#endif