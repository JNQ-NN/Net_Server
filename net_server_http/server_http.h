#ifndef __SERVER_HTTP_H__
#define __SERVER_HTTP_H__
#include <iostream>
#include "asio.hpp"
using namespace std;
#include "server_http_session.h"
#include "../tool/log.h"

/*
* @brief 提供HTTP服务
*/
class ServerHTTP{
public:
    ServerHTTP(asio::io_context& ioc,unsigned short port);
    void start_accept();
    void handle_accept(const asio::error_code& error,std::shared_ptr<SHSession> session);
private:
    asio::io_context& ioc_;
    asio::ip::tcp::acceptor acceptor_;
};

#endif