#include "redis_operation.h"

static auto redis = Redis("tcp://127.0.0.1:6379");; //Reids保持连接状态

/*
* 检查Redis是否连接，若未连接，考虑redis-server未开启
*/
void checkRedisConnection(){
    try {

    // 发送 PING 命令
    std::string response = redis.ping();

    // 判断响应是否为 "PONG"
    if (response == "PONG") {
        std::cout << "Connection is active." << std::endl;
    } else {
        std::cout << "Connection is not active." << std::endl;
    }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void RedisMSG::sendMessage(const char* fromUser,const char* toUser,const char* msg){
    string msgMode = "User:";
    redis.lpush(msgMode+fromUser,msg);
    redis.lpush(msgMode+toUser,msg);
}

string RedisMSG::getUserMessage(const char* fromUser){
    string msgMode = "User:";
    string msgKey = msgMode + fromUser;
    cout<<"msgKey:"<<msgKey<<endl;
    auto len = redis.llen(msgKey);
    cout<<"len"<<len<<endl;
    std::vector<std::string> msgs;
    redis.lrange(msgKey, 0, -1, std::back_inserter(msgs));
    for(auto& m:msgs){
        cout<<m<<endl;
    }
    string temp = "";
    return temp;
}