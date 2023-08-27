#include "client.h"

Client::Client(asio::io_context& ioc,const char* serverAddress,unsigned short port):ioc_(ioc){
    auto ep = asio::ip::tcp::endpoint(asio::ip::address::from_string(serverAddress),port);
    system("clear");
    cout<<"############"<<endl;
    cout<<"client start"<<endl;
    session_ = make_shared<CSession>(ioc,ep);
    user_ = new User();
    start_client();
}

Client::~Client(){
    delete user_;
}

void Client::start_client(){
    system("clear");
    cout<<"######"<<endl;
    cout<<"1.登录"<<endl;
    cout<<"2.注册"<<endl;
    cout<<"q.退出"<<endl;
    char choice = 'q';
    cout<<"请选择:";
    cin>>choice;
    switch (choice)
    {
    case '1':
        login();
        break;
    case 'q':
        std::exit(0);
        break;
    default:
        break;
    }
    sendMsg();
    
}

/*
* @brief 登录
*/
bool Client::login(){
    system("clear");
    while(1){
        if(verify_identity()){
            cout<<"登录成功"<<endl;
            break;
        }else{
            system("clear");
            cout<<"请输入正确的账户和密码"<<endl;
        }    
    }
    return true;
}
/*
* @brief 身份验证
*/
bool Client::verify_identity(){
    char name[USER_NAME_LEN];
    char pwd [USER_PWD_LEN];
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
    json->appendInt("mode",MSGMODE_MYSQL_QUERY_EXIST);
    json->appendCharPtr("queryCmd",queryCmd.c_str());
    string msg = MSG::packing(json);
    session_->send(const_cast<char*>(msg.c_str()),msg.length());
    delete json;
    session_->receive();
    auto queryRes = session_->getMsgNode()->getJson().getBool("queryRes");
    user_->setName(name);
    cout<<user_->getName()<<endl;
    return queryRes;
}

/*
* @brief 发送消息
*/
void Client::sendMsg(){
    cout<<"你好,"<<user_->getName()<<endl;
    char toUser[USER_NAME_LEN];
    cout<<"请输入消息发送用户:";
    cin>>toUser;
    cout<<"请输入发送的消息:";
    string msg;
    cin>>msg;

    cout<<"testt:"<<user_->getName()<<endl;
    Json* json = new Json();
    json->appendInt("mode",MSGMODE_REDIS_SEND_MSG);
    // json->appendCharPtr("time",TOOL::getCurTime());
    json->appendCharPtr("fromUser",user_->getName());
    json->appendCharPtr("toUser",toUser);
    json->appendStr("msg",msg);
    cout<<json->serialization()<<endl;
    msg = MSG::packing(json);
    delete json;
}