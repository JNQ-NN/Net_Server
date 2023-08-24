#include "server.h"

/*
* @brief 封装客户端socket,负责async accept
*/
Server::Server(asio::io_context& ioc,unsigned short port):ioc_(ioc),
acceptor_(ioc_,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port))
{
    cout<<"Server Start"<<endl;
    cout<<"local host: "<<acceptor_.local_endpoint().address().to_string()<<endl;
    cout<<"local port: "<<acceptor_.local_endpoint().port()<<endl;
}

void Server::start_accept(){
    try{
        std::shared_ptr<SSession> session = make_shared<SSession>(ioc_);
        asio::ip::tcp::socket tempSocket(ioc_);
        acceptor_.async_accept(*(session->getSocket()),std::bind(&Server::handle_accept,this,std::placeholders::_1,session));
    }catch(std::exception& e){
        cerr<<e.what()<<"\n";
    }
}

/*
* @处理accpet的异步回调函数
*/
void Server::handle_accept(const asio::error_code& error,std::shared_ptr<SSession> session){
    if(!error){
        cout<<"######################"<<endl;
        cout<<"Client Connection ... "<<endl;
        cout<<"Client Address:"<<session->getSocket()->remote_endpoint().address()<<endl;
        session->start_receive();
        // char buff[20]="        10HelloANGO";
        // session->send(buff,20);
        start_accept(); //以此保持accpet状态
    }else{
        cerr<<error.message()<<endl;
    }
}