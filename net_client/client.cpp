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
    case '2':
        sign();
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
        cout<<"User:"<<user_->getName()<<endl;
        cout<<"1.发送用户消息"<<endl;
        cout<<"2.发送群组消息"<<endl;
        cout<<"3.查看用户消息"<<endl;
        cout<<"4.查看群组消息"<<endl;
        cout<<"5.查看所有消息"<<endl;
        cout<<"q.退出"<<endl;
        cout<<"请选择:";
        cin>>choice;
        switch (choice)
        {
        case '1':
            sendMsg(MSGMODE_REDIS_USER_SENDMSG);
            break;
        case '2':
            sendMsg(MSGMODE_REDIS_GROUP_SENDMSG);
            break;
        case '3':
            showUserMSG();
            break;
        case '4':
            showGroupMSG();
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
        if(login_verify_identity()){
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
* @brief 注册
*/
bool Client::sign(){
//1.验证注册用户是否在Reids User存在
//2.若存在，注册失败
//3.若不存在，存储至Mysql，再同步至Redis

    system("clear");
    while(1){
        if(sign_verify_identity()){
            cout<<"注册成功"<<endl;
            break;
        }else{
            system("clear");
            cout<<"账户已存在，请重新输入"<<endl;
        }    
    }
    return true;
}

/*
* @brief 登录身份验证
*/
bool Client::login_verify_identity(){
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

bool Client::sign_verify_identity(){
    char name[USER_NAME_LEN];
    char pwd [USER_PWD_LEN];
    cout<<"请输入用户名:";
    cin>>name;

    Json* json = new Json();
    json->appendInt("mode",MSGMODE_REDIS_QUERY_EXIST);
    json->appendInt("REDIS_TYPE",REDIS_SET);
    json->appendCharPtr("key","User");
    json->appendCharPtr("value",name);
    handle_sendMsg(json);
    delete json;
    session_->receive();
    auto queryRes = session_->getMsgNode()->getJson().getBool("queryRes");
    if( queryRes ){ 
        return false; 
    }
    cout<<"请输入密码:";
    cin>>pwd;

    stringstream appendCmd;
    appendCmd<<"insert into user (name,pwd,identity) values";
    appendCmd<<"(\""<<name<<"\",";
    appendCmd<<"\""<<pwd<<"\",";
    appendCmd<<"\""<<1<<"\")";    //identity 1
    Json* userJson = new Json();
    userJson->appendInt("mode",MSGMODE_MYSQL_USER_APPEND);
    userJson->appendCharPtr("name",name);
    userJson->appendCharPtr("appendCmd",appendCmd.str().c_str());
    handle_sendMsg(userJson);
    delete userJson;
    session_->receive();
    auto appendRes = session_->getMsgNode()->getJson().getBool("appendRes");
    if(!appendRes){
        return false;
    }

    this->user_->setName(name);
    return true;
    
    // return !queryRes;
    

}

/*
* @brief 发送消息
*/
void Client::sendMsg(int sendMode){
    system("clear");
    cout<<"你好,"<<user_->getName()<<endl;
    char toWhom[USER_NAME_LEN];
    if(sendMode == MSGMODE_REDIS_USER_SENDMSG){
        cout<<"请输入消息发送用户:";
    }else if(sendMode == MSGMODE_REDIS_GROUP_SENDMSG){
        cout<<"请输入消息发送群组:";
    }
    cin>>toWhom;
    cout<<"请输入发送的消息:";
    string msg;
    cin>>msg;

    Json* json = new Json();
    json->appendInt("mode",sendMode);
    json->appendStr("time",TOOL::getCurTime());
    json->appendCharPtr("fromUser",user_->getName());
    if(sendMode == MSGMODE_REDIS_USER_SENDMSG){
        json->appendCharPtr("toUser",toWhom);
    }else if(sendMode == MSGMODE_REDIS_GROUP_SENDMSG){
        json->appendCharPtr("toGroup",toWhom);
    }
    json->appendStr("msg",msg);
    handle_sendMsg(json);
    delete json;
}

/*
* @brief 显示和指定用户的聊天记录 
*/
void Client::showUserMSG(){
    /*选择目标用户*/
    char toUser[USER_NAME_LEN];
    cout<<"请输入查看信息的目标用户:";
    cin>>toUser;
    system("clear");
    cout<<"To: "<<toUser<<endl;
    /*发送消息请求*/
    Json* json = new Json();
    json->appendInt("mode",MSGMODE_REDIS_USER_SHOWMSG);
    json->appendCharPtr("fromUser",user_->getName());
    json->appendCharPtr("toUser",toUser);
    handle_sendMsg(json);
    delete json;
    /*接受查询结果*/
    session_->receive();
    /*显示查询结果*/
    vector<string> userMsgs; 
    session_->getMsgNode()->getJson().getStrArr("msgs",userMsgs);
    for(auto& um:userMsgs){
        Json jsonUm(um);
        if(!strcmp(jsonUm.getCharPtr("fromUser"),toUser) || !strcmp(jsonUm.getCharPtr("toUser"),toUser)){
            cout<<"["<<jsonUm.getCharPtr("time")<<"]";
            cout<<"["<<jsonUm.getCharPtr("fromUser")<<"] ";
            cout<<jsonUm.getCharPtr("msg")<<endl;
        }
    }
    cout<<endl;
    cout<<"1.发送消息"<<endl;
    cout<<"q.退出"<<endl;
    cout<<"请选择:";
    char choice = 'q';
    cin>>choice;
    switch(choice){
        case '1':
            sendMsg(MSGMODE_REDIS_USER_SENDMSG);
            break;
        case 'q':
            break;
    }
}

/*
* @brief 将封装好的Json对象,封装成消息协议
*/
void Client::handle_sendMsg(Json* json){
    string msg = MSG::packing(json);
    session_->send(const_cast<char*>(msg.c_str()),msg.length());
}

void Client::showGroupMSG(){
    /*选择目标群组*/
    char toGroup[USER_NAME_LEN];
    cout<<"请输入查看信息的目标群组:";
    cin>>toGroup;
    system("clear");
    cout<<"To: "<<toGroup<<endl;
    /*发送消息请求*/
    Json* json = new Json();
    json->appendInt("mode",MSGMODE_REDIS_GROUP_SHOWMSG);
    json->appendCharPtr("fromUser",user_->getName());
    json->appendCharPtr("toGroup",toGroup);
    handle_sendMsg(json);
    delete json;
    /*接受查询结果*/
    session_->receive();
    /*显示查询结果*/
    vector<string> userMsgs; 
    session_->getMsgNode()->getJson().getStrArr("msgs",userMsgs);
    for(auto& um:userMsgs){
        Json jsonUm(um);
        if(1){
            cout<<"["<<jsonUm.getCharPtr("time")<<"]";
            cout<<"["<<jsonUm.getCharPtr("fromUser")<<"] ";
            cout<<jsonUm.getCharPtr("msg")<<endl;
        }
    }
    cout<<endl;
    cout<<"1.发送消息"<<endl;
    cout<<"q.退出"<<endl;
    cout<<"请选择:";
    char choice = 'q';
    cin>>choice;
    switch(choice){
        case '1':
            sendMsg(MSGMODE_REDIS_GROUP_SENDMSG);
        case 'q':
            break;
    }
}
