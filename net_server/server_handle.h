#ifndef __SERVER_HANDLE__
#define __SERVER_HANDLE__

#include <iostream>
#include <queue>
using namespace std;

#include "../tool/include/threadPool.h"
#include "../tool/json.h"
#include "../tool/mysql_operation.h"
#include "../tool/redis_operation.h"
#include "server_session.h"
using namespace RedisMSG;

class SSession;
/*
* @brief 用于服务器处理事件，采用单例模式，以此维护线程池
*/
class SHandle:public std::enable_shared_from_this<SHandle>{
public:
    SHandle(){}
    ~SHandle(){ delete threadPool_; }
    static void handle_receive(shared_ptr<SSession> session,char* msgRecv);  //此处加个协程，进行事件分发
    static void handle_mysqlQueryExist(shared_ptr<SSession> session,const char* queryCmd);
    static void handle_redisQueryExist(shared_ptr<SSession> session,shared_ptr<Json> json);

    static void handle_redis_sendUserMsg(shared_ptr<SSession> session,shared_ptr<Json> json);
    static void handle_redis_showUserMsg(shared_ptr<SSession> session,shared_ptr<Json> json);
    static void handle_redis_sendGroupMsg(shared_ptr<SSession> session,shared_ptr<Json> json);
    static void handle_redis_showGroupMsg(shared_ptr<SSession> session,shared_ptr<Json> json);

    static void handle_login();
    static void handle_sign();
private:
    static queue<char*>* msg_queue_; //消息队列
    static ThreadPool* threadPool_;
};

#endif