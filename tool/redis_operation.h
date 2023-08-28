#ifndef __REDIS_OPERATION__
#define __REDIS_OPERATION__

#include <iostream>
#include <vector>
#include <map>
#include <sw/redis++/redis++.h>
using namespace std;
using namespace sw::redis;
#include "mysql_operation.h"
#include "json.h"

namespace RedisMSG{
    void checkConnection();
    void sendMessage(const char* fromUser,const char* toUser,const char* msg);
    string getUserMessage(const char* fromUser);
};

#endif