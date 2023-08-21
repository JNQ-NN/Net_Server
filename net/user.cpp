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
    while (true)
    {
        cout<<"请输入用户名:";
        cin>>tempName;
        cout<<"请输入密码:";
        cin>>tempPwd;
        if((verify(tempName,tempPwd))){ 
            break;
        }
    }
    cout<<"登录成功！"<<endl;
    return true;
}

/*
 *登录验证
*/
bool User::verify(const char* tempName,const char* tempPwd){
    char* queryCmd; 
    snprintf(queryCmd,100,"select * from user where name=\"%s\" and pwd=\"%s\";",tempName,tempPwd);
    cout<<queryCmd<<endl;
    MYSQL_RES* res = ms_->mysqlQuery(queryCmd);
    MYSQL_ROW row ;
    while(row = mysql_fetch_row(res)){
        cout<<row[0]<<endl;
    }
    return true;
}