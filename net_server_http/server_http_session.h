#ifndef __SERVER_HTTP_SESSION__
#define __SERVER_HTTP_SESSION__
#include <iostream>
#include <asio.hpp>
using namespace std;

class SHSession:public enable_shared_from_this<SHSession>{
    typedef asio::ip::tcp::socket* socket_t;
public: 
    SHSession(asio::io_context& ioc);
    ~SHSession();
    socket_t getSocket();
    void start_receive();
    void handle_receive(const asio::error_code& error,size_t length);
    void handle_send(const asio::error_code& error,size_t length);

private:
    socket_t socket_;
    string msgRecv_;
    string msgSend_;
};

#endif