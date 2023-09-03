#include "server_http.h"

ServerHTTP::ServerHTTP(asio::io_context& ioc,unsigned short port)
:ioc_(ioc),
acceptor_(ioc_,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port)){
    cout<<"Server HTTP Start"<<endl;
    cout<<"local host:"<<acceptor_.local_endpoint().address().to_string()<<endl;
    cout<<"local prot:"<<acceptor_.local_endpoint().port()<<endl;
    mainLog_INFO("Server HTTP Start");
}

void ServerHTTP::start_accept(){
    shared_ptr<SHSession> session = make_shared<SHSession>(ioc_);
    acceptor_.async_accept(*(session->getSocket()),std::bind(&ServerHTTP::handle_accept,this,std::placeholders::_1,session));
}


void ServerHTTP::handle_accept(const asio::error_code& error,std::shared_ptr<SHSession> session){
    if(!error){
        cout<<"######################"<<endl;
        cout<<"Client HTTP Connection ... "<<endl;
        cout<<"Client HTTP Address:"<<session->getSocket()->remote_endpoint().address()<<endl;
        session->start_receive();
        start_accept(); 
    }else{
        cerr<<error.message()<<endl;
    }
}