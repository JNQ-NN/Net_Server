#include "mysql_operation.h"

Mysql::Mysql(){
    mysql_ = new MYSQL();
    init();
}

Mysql::~Mysql(){
    cout<<"析构调用"<<endl;
    if(mysql_!=nullptr){
        delete mysql_;
        mysql_ = nullptr;
    }
}

void test(MYSQL* mysql,string s){
    mysql_query(mysql,s.c_str());
    cout<<"test success"<<endl;
}

/*
 *@brief 数据库连接
*/
bool Mysql::mysqlConnection(const char* hostName,
                            const char* userName,const char* userPwd,
                            const char* userDatabase,unsigned int port){
    
    if(mysql_ == nullptr){
        cout<<"connection mysql nullplr"<<endl;
    }
    if(mysql_real_connect(mysql_,hostName,userName,userPwd,userDatabase,port,NULL,0)){//返回false则连接失败，返回true则连接成功
        //中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等）
        cout<<"mysql connection "<<endl;
        return true;
    }else{
        cout<<"mysql disconnection "<<mysql_error(mysql_);
        return false;
    }
    return false;                       
}

/*
 *@brief 数据库查询
*/
MYSQL_RES* Mysql::mysqlQuery(const char* queryCmd){
    cout<<queryCmd<<endl;
    mysql_query(mysql_,queryCmd);
    res_ = mysql_store_result(mysql_);
    cout<<"1*1"<<endl;
    return res_;
}

void Mysql::init(){
    mysql_init(mysql_);
}

/**
 *@breif 判断数据库是否连接
*/
bool Mysql::isConnection(){
    if(mysql_){
        return (0==mysql_ping(mysql_));
    }
    return false;
 }
