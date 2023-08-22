#ifndef __SERVER_SESSION_H__
#define __SERVER_SESSION_H__
#include "iostream"
#include <asio.hpp>
using namespace std;

typedef asio::ip::tcp::socket* socket_t;
class Session:public std::enable_shared_from_this<Session>{
public:
    Session(asio::io_context& ioc);
    ~Session();
    socket_t getSocket();
private:
    socket_t socket_;
};

#endif