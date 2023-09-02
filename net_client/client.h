#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "iostream"
#include <asio.hpp>
#include <thread>
using namespace std;
#include "client_session.h"
#include "../net/msg.h"
#include "../net/user.h"
#include "../tool/redis_operation.h"


class Client{
public:
    Client(asio::io_context& ioc,const char* serverAddress,unsigned short port);
    ~Client();
    void start_client();
private:
    asio::io_context& ioc_;
    shared_ptr<CSession> session_;
    User* user_;
    bool login();
    bool sign();
    bool login_verify_identity();
    bool sign_verify_identity();
    //void send(char* toUser,string msg);
    void sendMsg(int sendMode);
    void showUserMSG();
    void showGroupMSG();
    void handle_sendMsg(Json* json);
};

#endif