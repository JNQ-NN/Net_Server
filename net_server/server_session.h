#ifndef __SERVER_SESSION_H__
#define __SERVER_SESSION_H__
#include <iostream>
#include <asio.hpp>
#include <queue>
using namespace std;
#include "server_handle.h"
#include "../tool/tool.h"
#include "../net/msg.h"

class SSession:public std::enable_shared_from_this<SSession>{
    typedef asio::ip::tcp::socket* socket_t;
public:
    SSession(asio::io_context& ioc);
    ~SSession();
    socket_t getSocket();
    void start_receive();
    void handle_receive(const asio::error_code& error);
    void handle_receiveMsgHead(const asio::error_code& error);
    void handle_receiveMsgNode(const asio::error_code& error);
    void handle_send(const asio::error_code& error);
    void send(char* msg,size_t msgMaxLen);
    
private:
    socket_t socket_;
    char* msgHeadRecv_;  //存储msgNode数据长度，用于支持可变长数据的接收
    shared_ptr<MsgNode> msgNodeRecv_;  
    queue<shared_ptr<MsgNode>> msgNodeSendQueue_; //消息发送队列
    mutex mxSendQueue_; //保护发送队列的线程安全
};

#endif