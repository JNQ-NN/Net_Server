#include "redis_operation.h"

static auto redis = Redis("tcp://127.0.0.1:6379");; //Reids保持连接状态

void RedisMSG::sendMessage(const char* fromUser,const char* toUser,const char* msg){
    string msgMode = "User:";
    redis.lpush(msgMode+fromUser,msg);
    redis.lpush(msgMode+toUser,msg);
}