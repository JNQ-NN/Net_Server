#include "server_session.h"

Session::Session(asio::io_context& ioc){
    socket_ = new asio::ip::tcp::socket(ioc);
    msgNodeRecv_ = make_shared<MsgNode>(MSGNODE_LEN);
}

Session::~Session(){
    cout<<"Client Close ...!"<<endl;
    socket_->close();  //完全关闭,不遵循四次挥手
    if(socket_ != nullptr){
        delete socket_;
        socket_ = nullptr;
    }
}

asio::ip::tcp::socket* Session::getSocket(){
    return socket_;
}

/*
* @brief 异步循环接收信息
*/
void Session::start_receive(){
    try{
        msgNodeRecv_->msgClear();
        socket_->async_receive(asio::buffer(msgNodeRecv_->getMsg(),msgNodeRecv_->getMsgMaxLen()),
            std::bind(&Session::handle_receive,shared_from_this(),std::placeholders::_1));
        
    }catch(std::exception& e){
        cerr<<e.what()<<"\n";
    }
}

/*
* @异步发送数据
*/
void Session::send(char* msg,size_t msgMaxLen){
    auto msgNodeSend = make_shared<MsgNode>(msg,msgMaxLen);
    auto lock = unique_lock<mutex>(mxSendQueue_);
    msgNodeSendQueue_.push(msgNodeSend);
    if(msgNodeSendQueue_.size()==1){
        socket_->async_send(asio::buffer(msgNodeSendQueue_.front()->getMsg(),msgNodeSendQueue_.front()->getMsgMaxLen()),
            std::bind(&Session::handle_send,shared_from_this(),std::placeholders::_1));
    }
}

void Session::handle_receive(const asio::error_code& error){
    if(error){
        if(error.value() == 2) return; //对端关闭,调用Session的析构函数,释放掉建立的连接              
        cerr<<"receive error: "<<error.message()<<"\n";  //其他error
        return;
    }
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

void Session::handle_send(const asio::error_code& error){
    if(error)cerr<<error.message()<<"\n";
    try{
        auto lock = unique_lock<mutex>(mxSendQueue_);
        msgNodeSendQueue_.pop();
        if(!msgNodeSendQueue_.empty()){
            socket_->async_send(asio::buffer(msgNodeSendQueue_.front()->getMsg(),msgNodeSendQueue_.front()->getMsgMaxLen()),
                std::bind(&Session::handle_send,shared_from_this(),std::placeholders::_1));

        }
    }catch(std::exception& e){
        cerr<<e.what()<<"\n";
    }
}