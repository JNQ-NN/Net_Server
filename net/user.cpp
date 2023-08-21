#include "user.h"

User::User(){
    ms_ = new Mysql();
    ms_->mysqlConnection();
    login();
}

User::~User(){
    if(ms_ != nullptr){
        delete ms_;
        ms_ = nullptr;
    }
}

/*
 *@brief 登录
*/
bool User::login(){
    char tempName[10];
    char tempPwd[20];
    while (1)
    {
        cout<<"请输入用户名:";
        cin >> tempName;
        cout<<"请输入密码:";
        cin>>tempPwd;
        if(verify(tempName,tempPwd)){ 
            break;
        }else{
            cout<<"用户名或密码错误"<<endl;
        }
    }
    cout<<"登录成功！"<<endl;
    return true;
}

/*
 *登录验证
*/
bool User::verify(const char* tempName,const char* tempPwd){
    char queryCmd[100];
    sprintf(queryCmd,"select * from user where name=\"%s\" and pwd=\"%s\";",tempName,tempPwd);
    cout<<queryCmd<<endl;
    MYSQL_RES* res = nullptr;
    res = ms_->mysqlQuery(queryCmd);
    switch (mysql_num_rows(res))
    {
    case 0:
        return false;
    case 1:
        return true;
    default:
        return false;
    }
}