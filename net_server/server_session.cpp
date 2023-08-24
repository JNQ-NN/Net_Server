#include "server_session.h"

Session::Session(asio::io_context& ioc){
    socket_ = new asio::ip::tcp::socket(ioc);
    msgNodeRecv_ = make_shared<MsgNode>(MSGNODE_LEN);
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

void Session::start_receive(){
    try{
        msgNodeRecv_->msgClear();
        socket_->async_receive(asio::buffer(msgNodeRecv_->getMsg(),msgNodeRecv_->getMsgMaxLen()),
            std::bind(&Session::handle_receive,shared_from_this(),std::placeholders::_1));
        
    }catch(std::exception& e){
        cerr<<e.what()<<"\n";
    }
}

void Session::handle_receive(const asio::error_code& error){
    if(error) cerr<<error.message()<<"\n";
    try{
        cout<<"msg:"<<msgNodeRecv_->getMsg()<<endl;
        msgNodeRecv_->msgClear();
        // 以此实现持续接收消息
        socket_->async_receive(asio::buffer(msgNodeRecv_->getMsg(),msgNodeRecv_->getMsgMaxLen()),
            std::bind(&Session::handle_receive,shared_from_this(),std::placeholders::_1));
    }catch(std::exception& e){
        cerr<<e.what()<<"\n";
    }
}