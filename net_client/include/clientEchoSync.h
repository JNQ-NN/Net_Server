#ifndef CLIENT_ECHO_SYNC_H
#define CLIENT_ECHO_SYNC_H
#include <iostream>
#include <asio.hpp>
using namespace std;

/*
 *@brief 同步echo客户端 TCP
 */
void clientEcho(){
    try{
        //1.build
        cout<<"client start."<<endl;
        asio::io_service ioService;                 //asio程序必须得io_service对象
        asio::ip::tcp::socket sock(ioService);      //创建socket对象
        asio::ip::tcp::endpoint endPoint(asio::ip::address::from_string("127.0.0.1"),6666); 
                                                    //绑定服务器地址和端口
        //2.connect                                   
        sock.connect(endPoint);                     //connect，若connect失败，则抛出异常
        
        //3.处理数据
        //char数组版本
        char buff[0xFF];
        //cin >> buff;        //cin遇到空格、回车则停止
        cin.get(buff,0XFF);   //cin.get()遇到回车则停止
		sock.send(asio::buffer(buff));
		memset(buff, 0, 0xFF);
		sock.receive(asio::buffer(buff));
		cout <<buff<<endl;
        sock.close();
        //TODO: string版本
    }
    catch (std::exception& _e) {
		std::cout << "server exceptional." << std::endl;
		std::cout << _e.what() << std::endl;
	}
	std::cout << "client end." << std::endl;
}

#endif