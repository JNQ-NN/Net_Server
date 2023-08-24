#ifndef __SERVER_SESSION_H__
#define __SERVER_SESSION_H__
#include "iostream"
#include <asio.hpp>
#include <queue>
using namespace std;
#include "../net/msg.h"

#define MSGNODE_LEN 100

typedef asio::ip::tcp::socket* socket_t;
class Session:public std::enable_shared_from_this<Session>{
public:
    Session(asio::io_context& ioc);
    socket_t getSocket();
    void start_receive();
    void handle_receive(const asio::error_code& error);
    void handle_send(const asio::error_code& error);
    void send(char* msg,size_t msgMaxLen);
    ~Session();
    
private:
    socket_t socket_;
    shared_ptr<MsgNode> msgNodeRecv_;
    queue<shared_ptr<MsgNode>> msgNodeSendQueue_;
    mutex mxSendQueue_; //用于保护发送队列的线程安全
};

#endif