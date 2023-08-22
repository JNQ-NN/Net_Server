#include "server_session.h"

Session::Session(asio::io_context& ioc){
    socket_ = new asio::ip::tcp::socket(ioc);
}

Session::~Session(){
    socket_->close();
    if(socket_ != nullptr){
        delete socket_;
        socket_ = nullptr;
    }
}

asio::ip::tcp::socket* Session::getSocket(){
    return socket_;
}