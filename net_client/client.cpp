#include "client.h"

Client::Client(asio::io_context& ioc,const char* serverAddress,unsigned short port):ioc_(ioc){
    auto ep = asio::ip::tcp::endpoint(asio::ip::address::from_string(serverAddress),port);
    cout<<"############"<<endl;
    cout<<"client start"<<endl;
    session_ = make_shared<CSession>(ioc,ep);
    //session_->start_receive();
    start_client();
}

void Client::start_client(){
    while(1){
        if(verify_identity()){
            break;
        }else{
            cout<<"请输入正确的账户和密码"<<endl;
        }
         
    }
    

}

/*
* @brief 身份验证
*/
bool Client::verify_identity(){
    char name[10];
    char pwd [20];
    cout<<"请输入用户名:";
    cin>>name;
    cout<<"请输入密码:";
    cin>>pwd;
    string queryCmd;
    queryCmd.append("select * from user where name=\"");
    queryCmd.append(name);
    queryCmd.append("\" and pwd=\"");
    queryCmd.append(pwd);
    queryCmd.append("\";");
    queryCmd.shrink_to_fit();
    Json* json = new Json();
    json->appendInt("mode",1);
    json->appendCharPtr("queryCmd",queryCmd.c_str());
    string msg = MSG::packing(json);
    session_->send(const_cast<char*>(msg.c_str()),msg.length());
    delete json;
    session_->receive();
    return session_->getMsgNode()->getJson().getBool("queryRes");
}