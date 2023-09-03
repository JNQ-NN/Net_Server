#include "server_http_session.h"

SHSession::SHSession(asio::io_context& ioc){
    socket_ = new asio::ip::tcp::socket(ioc);
}

SHSession::~SHSession(){
    socket_->close();
    delete socket_;
}

SHSession::socket_t SHSession::getSocket(){
    return socket_;
}

void SHSession::start_receive(){
    msgRecv_.clear();
   
    asio::async_read_until(*socket_,asio::dynamic_buffer(msgRecv_),"\r\n\r\n",
        std::bind(&SHSession::handle_receive,shared_from_this(),std::placeholders::_1,std::placeholders::_2));
}

void SHSession::handle_receive(const asio::error_code& error,size_t length){
    if(error){

    }
    cout<<length<<endl;
    cout<<this->msgRecv_<<endl;
    char htmlConetent[]{ "HTTP/1.0 200 OK\r\n\r\n<html>Hello World!!!</html>\r\n" };
    socket_->async_send(asio::buffer(htmlConetent,sizeof(htmlConetent)),
        std::bind(&SHSession::handle_send,shared_from_this(),std::placeholders::_1,std::placeholders::_2));
}

void SHSession::handle_send(const asio::error_code& error,size_t length){
    // asio::async_read_until(*socket_,asio::dynamic_buffer(msgRecv_),"\r\n\r\n",
    //     std::bind(&SHSession::handle_receive,shared_from_this(),std::placeholders::_1,std::placeholders::_2));
}

