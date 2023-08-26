#ifndef __SERVER_H__
#define __SERVER_H__
#include <iostream>
#include <asio.hpp>
using namespace std;
#include "server_session.h"
#include "server_handle.h"

/*
* @brief 双工异步通信
*/
class Server{
public:
    Server(asio::io_context& ioc,unsigned short port);
    void start_accept();
    void handle_accept(const asio::error_code& error,std::shared_ptr<SSession> SSession);

private:
    asio::io_context& ioc_; //io_context io_service 两者皆可
    asio::ip::tcp::acceptor acceptor_;
};

#endif