#include "server_handle.h"

queue<char*>* SHandle::msg_queue_ = new queue<char*>();
ThreadPool* SHandle::threadPool_ = new ThreadPool();

/*
* @brief 解析接收到的数据，根据mode再次选择对应handle
*/
void SHandle::handle_receive(shared_ptr<SSession> session,char* msgRecv){
    shared_ptr<Json> json = make_shared<Json>(msgRecv);
    cout<<"receive！"<<endl;
    switch (json->getInt("mode"))
    {
    case MSGMODE_MYSQL_QUERY_EXIST:    //Mysql查询是否存在
        threadPool_->commit(handle_mysqlQueryExist,session,json->getCharPtr("queryCmd"));
        break;
    case MSGMODE_REDIS_QUERY_EXIST:    //Redis查询是否存在
        threadPool_->commit(handle_redisQueryExist,session,json);
        break;
    case MSGMODE_MYSQL_USER_APPEND:    //MYSQL添加用户
        threadPool_->commit(handle_mysql_appendUser,session,json);
        break;
    case MSGMODE_REDIS_USER_SENDMSG:   //发送用户消息
        threadPool_->commit(handle_redis_sendUserMsg,session,json);
        break;
    case MSGMODE_REDIS_USER_SHOWMSG:   //显示用户沟通的消息
        threadPool_->commit(handle_redis_showUserMsg,session,json);
        break;
    case MSGMODE_REDIS_GROUP_SENDMSG:  //发送群组消息
        threadPool_->commit(handle_redis_sendGroupMsg,session,json);
        break;
    case MSGMODE_REDIS_GROUP_SHOWMSG:  //发送群组消息
        threadPool_->commit(handle_redis_showGroupMsg,session,json);
        break;
    default:
        break;
    }
}

/*
* @brief 查询，是否存在
*/
void SHandle::handle_mysqlQueryExist(shared_ptr<SSession> session,const char* queryCmd){
    Mysql* ms = new Mysql();
    ms->mysqlConnection();
    MYSQL_RES* queryRes = nullptr;
    queryRes = ms->mysqlQuery(queryCmd);
    bool isExist = mysql_num_rows(queryRes)>0?true:false;
    Json* json = new Json();
    json->appendInt("mode",MSGMODE_MYSQL_QUERY_EXIST);
    json->appendBool("queryRes",isExist);
    string msg = MSG::packing(json);
    session->send(const_cast<char*>(msg.c_str()),msg.length());
    mysql_free_result(queryRes);
    delete json;
}

void SHandle::handle_redisQueryExist(shared_ptr<SSession> session,shared_ptr<Json> json){
    bool isExist = false;
    switch(json->getInt("REDIS_TYPE")){
        case REDIS_SET:
            isExist = RedisMSG::queryExistSetElement(json->getCharPtr("key"),json->getCharPtr("value"));
            break;
        default:
            break;
    }
    
    Json* queryJson = new Json();
    queryJson->appendInt("mode",MSGMODE_REDIS_QUERY_EXIST);
    queryJson->appendBool("queryRes",isExist);
    string msg = MSG::packing(queryJson);
    session->send(const_cast<char*>(msg.c_str()),msg.length());
    delete queryJson;
}

void SHandle::handle_mysql_appendUser(shared_ptr<SSession> session,shared_ptr<Json> json){
    Mysql* ms = new Mysql();
    ms->mysqlConnection();
    MYSQL_RES* appendRes = nullptr;
    appendRes = ms->mysqlAppend(json->getCharPtr("appendCmd"));
    Json* appendJson = new Json();
    appendJson->appendInt("mode",MSGMODE_MYSQL_QUERY_EXIST);
    appendJson->appendBool("appendRes",!appendRes);
    string msg = MSG::packing(appendJson);
    session->send(const_cast<char*>(msg.c_str()),msg.length());
    mysql_free_result(appendRes);
    delete appendJson;
    RedisMSG::appendSet("User",json->getCharPtr("name"));
    
}

void SHandle::handle_redis_sendUserMsg(shared_ptr<SSession> session,shared_ptr<Json> json){
    RedisMSG::sendUserMessage(json->getCharPtr("fromUser"),json->getCharPtr("toUser"),json->serialization());
}

void SHandle::handle_redis_showUserMsg(shared_ptr<SSession> session,shared_ptr<Json> json){
    vector<string> msgs;
    RedisMSG::getUserMessage(json->getCharPtr("fromUser"),msgs);
    Json* msgJson = new Json();
    msgJson->appendInt("mode",MSGMODE_REDIS_USER_SHOWMSG);
    msgJson->appendArr("msgs",msgs);
    string msg = MSG::packing(msgJson);
    session->send(const_cast<char*>(msg.c_str()),msg.length());
    delete msgJson;
}

void SHandle::handle_redis_sendGroupMsg(shared_ptr<SSession> session,shared_ptr<Json> json){
    RedisMSG::sendGroupMessage(json->getCharPtr("fromUser"),json->getCharPtr("toGroup"),json->serialization());
}

void SHandle::handle_redis_showGroupMsg(shared_ptr<SSession> session,shared_ptr<Json> json){
    vector<string> msgs;
    RedisMSG::getGroupMessage(json->getCharPtr("toGroup"),msgs);
    Json* msgJson = new Json();
    msgJson->appendInt("mode",MSGMODE_REDIS_GROUP_SHOWMSG);
    msgJson->appendArr("msgs",msgs);
    string msg = MSG::packing(msgJson);
    session->send(const_cast<char*>(msg.c_str()),msg.length());
    delete msgJson;
}
