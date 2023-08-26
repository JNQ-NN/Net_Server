#include "client_session.h"

CSession::CSession(asio::io_context& ioc,asio::ip::tcp::endpoint ep){
    socket_ = new asio::ip::tcp::socket(ioc);
    socket_->connect(ep);
    cout<<"Client Connection"<<endl;
    msgHeadRecv_ = new char[MSGHEAD_LEN];
    msgNodeRecv_ = make_shared<MsgNode>();
}

CSession::~CSession(){
    cout<<"Client Close ..."<<endl;
    socket_->close();  //完全关闭,不遵循四次挥手
    delete[] msgHeadRecv_;  
    if(socket_ != nullptr){
        delete socket_;
        socket_ = nullptr;
    }
}

void CSession::start_receive(){
    try{
        memset(msgHeadRecv_,' ',MSGHEAD_LEN);
        socket_->async_receive(asio::buffer(msgHeadRecv_,MSGHEAD_LEN),
            std::bind(&CSession::handle_receiveMsgHead,shared_from_this(),std::placeholders::_1));
    }catch(std::exception& e){
        cerr<<e.what()<<"\n";
    }
}

/*
* 同步发送
*/
void CSession::send(char* msg,size_t msgMaxLen){
    // char msgHead[MSGHEAD_LEN];
    // char* msgSend;
    // sprintf(msgHead,MSG_)
    socket_->send(asio::buffer(msg,msgMaxLen));
}

/*
* 同步接收
*/
void CSession::receive(){
    /*接收消息头*/
    try{
        memset(msgHeadRecv_,' ',MSGHEAD_LEN);
        socket_->receive(asio::buffer(msgHeadRecv_,MSGHEAD_LEN));
    }catch(std::exception& e){
        cerr<<e.what()<<"\n";
    }
    /*接收消息体*/  
    try{
        msgNodeRecv_->resize(TOOL_Str::strToNum(msgHeadRecv_));
        socket_->receive(asio::buffer(msgNodeRecv_->getMsg(),msgNodeRecv_->getMsgMaxLen()));
        cout<<"NNN"<<endl;
        cout<<msgNodeRecv_->getMsg()<<endl;
    }catch(std::exception& e){
        cerr<<e.what()<<"\n";
    } 
    
}

void CSession::handle_receiveMsgHead(const asio::error_code& error){
    if(error){
        if(error.value() == 2) return; //对端关闭,调用CSession的析构函数,释放掉建立的连接              
        cerr<<"receive error: "<<error.message()<<"\n";  //其他error
        return;
    }
    try{
        cout<<"msgLen:"<<TOOL_Str::strToNum(msgHeadRecv_)<<endl;
        msgNodeRecv_->resize(TOOL_Str::strToNum(msgHeadRecv_));
        socket_->async_receive(asio::buffer(msgNodeRecv_->getMsg(),msgNodeRecv_->getMsgMaxLen()),
            std::bind(&CSession::handle_receiveMsgNode,shared_from_this(),std::placeholders::_1));
        
    }catch(std::exception& e){
        cerr<<e.what()<<"\n";
    }
}

void CSession::handle_receiveMsgNode(const asio::error_code& error){
    if(error){
        if(error.value() == 2) return; //对端关闭,调用CSession的析构函数,释放掉建立的连接              
        cerr<<"receive error: "<<error.message()<<"\n";  //其他error
        return;
    }
    try{
        cout<<"msg:"<<msgNodeRecv_->getMsg()<<endl;
        memset(msgHeadRecv_,' ',MSGHEAD_LEN);
        socket_->async_receive(asio::buffer(msgHeadRecv_,MSGHEAD_LEN),
            std::bind(&CSession::handle_receiveMsgHead,shared_from_this(),std::placeholders::_1));
    }catch(std::exception& e){
        cerr<<e.what()<<"\n";
    }
}

shared_ptr<MsgNode> CSession::getMsgNode(){
    return msgNodeRecv_;
}
