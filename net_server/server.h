#ifndef __SERVER_H__
#define __SERVER_H__
#include <iostream>
#include <asio.hpp>
using namespace std;
#include "server_session.h"

class Server{
public:
    Server(asio::io_context& ioc,int port);
    void start_accept();
    void handle_accept(const asio::error_code& error,std::shared_ptr<Session> session);

private:
    asio::io_context& ioc_;
    //asio::io_service& ios_; //io_context io_service 两者皆可
    asio::ip::tcp::acceptor acceptor_;
};

#endif