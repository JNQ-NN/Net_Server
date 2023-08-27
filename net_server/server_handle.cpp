#include "server_handle.h"

queue<char*>* SHandle::msg_queue_ = new queue<char*>();
ThreadPool* SHandle::threadPool_ = new ThreadPool();

/*
* @brief 解析接收到的数据，根据mode再次选择对应handle
*/
void SHandle::handle_receive(shared_ptr<SSession> session,char* msgRecv){
    shared_ptr<Json> json = make_shared<Json>(msgRecv);
    switch (json->getInt("mode"))
    {
    case 1: //查询是否存在
        handle_queryExist(session,json->getCharPtr("queryCmd"));
        break;
    
    default:
        break;
    }
}

/*
* @brief 查询，是否存在
*/
void SHandle::handle_queryExist(shared_ptr<SSession> session,const char* queryCmd){
    Mysql* ms = new Mysql();
    ms->mysqlConnection();
    MYSQL_RES* queryRes = nullptr;
    queryRes = ms->mysqlQuery(queryCmd);
    bool isExist = mysql_num_rows(queryRes)>0?true:false;

    Json* json = new Json();
    json->appendInt("mode",1);
    json->appendBool("queryRes",isExist);
    string msg = MSG::packing(json);
    session->send(const_cast<char*>(msg.c_str()),msg.length());
}