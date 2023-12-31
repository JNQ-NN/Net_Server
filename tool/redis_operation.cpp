#include "redis_operation.h"

static auto redis = Redis("tcp://127.0.0.1:6379");; //Reids保持连接状态

/*
* @brief 检查Redis是否连接，若未连接，考虑redis-server未开启
* TODO:没啥用,得在Main之前,使用脚本检测,若检测未连接,应调用$redis-server
*/
void RedisMSG::checkRedisConnection(){
    while(1){
        try {
        std::string response = redis.ping();
            // 判断响应是否为 "PONG"
            if (response == "PONG") {
                std::cout << "Redis Connection is active." << std::endl;
                break;
            } else {
                std::cout << "Redis Connection is not active." << std::endl;
                TOOL::cmd("redis-server");
                this_thread::sleep_for(chrono::seconds(1));
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

void RedisMSG::sendUserMessage(const char* fromUser,const char* toUser,const char* msg){
    string msgMode = "User:";
    redis.lpush(msgMode+fromUser,msg);
    redis.lpush(msgMode+toUser,msg);
}

void RedisMSG::getUserMessage(const char* fromUser,vector<string>&msgs){
    string msgMode = "User:";
    string msgKey = msgMode + fromUser;
    // auto len = redis.llen(msgKey);
    redis.lrange(msgKey, 0, -1, std::back_inserter(msgs));
}

void RedisMSG::sendGroupMessage(const char* fromUser,const char* toGroup,const char* msg){
    string msgMode = "Group:";
    redis.lpush(msgMode+toGroup,msg);
}

void RedisMSG::getGroupMessage(const char* toGroup,vector<string>&msgs){
    string msgMode = "Group:";
    string msgKey = msgMode + toGroup;
    // auto len = redis.llen(msgKey);
    redis.lrange(msgKey, 0, -1, std::back_inserter(msgs));
    for(auto& v:msgs){
        cout<<v<<endl;
    }
}

void RedisMSG::appendList(const char* listName,string listContent){
    redis.lpush(listName,listContent);
}

void RedisMSG::appendSet(const char* listName,string listContent){
    redis.sadd(listName,listContent);
}

bool RedisMSG::queryExistSetElement(const char* setName,const char* setContent){
    return redis.sismember(setName,setContent);
}