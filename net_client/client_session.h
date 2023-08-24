#ifndef __CLIENT_CSession_H__
#define __CLIENT_CSession_H__

#include "iostream"
#include <asio.hpp>
using namespace std;
#include "../net/msg.h"
#include "../tool/tool.h"


class CSession:public std::enable_shared_from_this<CSession>{
    typedef asio::ip::tcp::socket* socket_t;
public:
    CSession(asio::io_context& ioc,asio::ip::tcp::endpoint ep);
    ~CSession();
    void start_receive();
    void send(char* msg,size_t msgMaxLen);
    void handle_receiveMsgHead(const asio::error_code& error);
    void handle_receiveMsgNode(const asio::error_code& error);
private:
    socket_t socket_;
    char* msgHeadRecv_;
    shared_ptr<MsgNode> msgNodeRecv_;
};

#endif