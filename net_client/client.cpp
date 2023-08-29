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

    while(1){
        system("clear");
        cout<<"###########"<<endl;
        cout<<"1.发送消息"<<endl;
        cout<<"2.查看用户消息"<<endl;
        cout<<"3.查看群组消息"<<endl;
        cout<<"4.查看所有消息"<<endl;
        cout<<"q.退出"<<endl;
        cout<<"请选择:";
        cin>>choice;
        switch (choice)
        {
        case '1':
            sendMsg();
            break;
        case '2':
            showUserMSG();
            break;
        case 'q':
            std::exit(0);
            break;
        default:
            break;
        }
    }
    
 
    
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
    handle_sendMsg(json);
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
    json->appendInt("mode",MSGMODE_REDIS_USER_SENDMSG);
    json->appendStr("time",TOOL::getCurTime());
    json->appendCharPtr("fromUser",user_->getName());
    json->appendCharPtr("toUser",toUser);
    json->appendStr("msg",msg);
    handle_sendMsg(json);
    delete json;
}

void Client::showUserMSG(){
    //选择目标用户
    char toUser[USER_NAME_LEN];
    cout<<"请输入目标用户:";
    cin>>toUser;
    system("clear");
    cout<<"To:"<<toUser;
    //发送消息请求
    Json* json = new Json();
    json->appendInt("mode",MSGMODE_REDIS_USER_SHOWMSG);
    json->appendCharPtr("fromUser",user_->getName());
    json->appendCharPtr("toUser",toUser);
    handle_sendMsg(json);
    delete json;
    //接受查询结果
    session_->receive();
    auto userMsg = session_->getMsgNode()->getMsg();
    cout<<userMsg<<endl;
    this_thread::sleep_for(std::chrono::seconds(1000));  //断点
    

}

void Client::handle_sendMsg(Json* json){
    string msg = MSG::packing(json);
    session_->send(const_cast<char*>(msg.c_str()),msg.length());
}

