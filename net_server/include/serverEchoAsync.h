#ifndef SERVER_ECHO_ASYNC_CLASS_H
#define SERVER_ECHO_ASYNC_CLASS_H
#include <iostream>
#include <asio.hpp>
using namespace std;


typedef std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
class ServerEcho{
public:
    ServerEcho(asio::io_context& ioContext,int port=6666):
    _ioContext(ioContext),
    _acceptor(_ioContext,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port))
    {
        cout<<"server start."<<endl; 
        cout<<"address:"<<_acceptor.local_endpoint().address()<<endl;
        cout<<"port:"<<_acceptor.local_endpoint().port()<<endl;
        this->start();  
    }
    void start(){
        socket_ptr clientSocket(new asio::ip::tcp::socket(_ioContext));
        _acceptor.async_accept(*clientSocket,std::bind(&ServerEcho::accept_handler,this,clientSocket));
    }
    void accept_handler(socket_ptr clientSocket){
        try
        {
            cout<<"client:"<<clientSocket->remote_endpoint().address()<<endl;
            char* buff = new char[0xFF];
            memset(buff,0,0xFF);
            clientSocket->async_receive(asio::buffer(buff,0xFF),std::bind(&ServerEcho::receive_handler,this,clientSocket,buff));
            this->start();
        }   
        catch(const std::exception& e)
        {  
            std::cerr << e.what() << '\n';
        }
    }
    void receive_handler(socket_ptr sock,char* buff){
        try{
            cout<<"socket receive:";
            cout<<buff<<endl;
            memset(buff,0,0xFF);
            sock->async_receive(asio::buffer(buff,0xFF),std::bind(&ServerEcho::receive_handler,this,sock,buff));

            //sock->async_send(asio::buffer(buff,0xFF),std::bind(&ServerEcho::send_handle,this,sock,buff));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    void send_handle(socket_ptr sock,char* buff){
        try{
            cout<<"socket send:";
            cout<<buff<<endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }  
private:
    asio::io_context& _ioContext;
    asio::ip::tcp::acceptor _acceptor;
};

void serverEcho(){
    try{
        asio::io_context ioContext;
        ServerEcho s(ioContext);
        ioContext.run();
    }
    catch(std::exception& _e){
        cout<<_e.what()<<endl;
    }
    cout<<"server end."<<endl;
}

#endif