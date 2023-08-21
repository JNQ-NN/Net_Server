#include "mysql_operation.h"

Mysql::Mysql(){
    mysql_ = new MYSQL();
}

Mysql::~Mysql(){
    if(mysql_!=nullptr){
        delete mysql_;
        mysql_ = nullptr;
    }
}

bool Mysql::mysqlConnection(const char* hostName,
                            const char* userName,const char* userPwd,
                            const char* userDatabase,unsigned int port){
    cout<<"1"<<endl;
    mysql_init(mysql_);
    cout<<"2"<<endl;
    if(mysql_real_connect(mysql_,hostName,userName,userPwd,userDatabase,port,NULL,0)){//返回false则连接失败，返回true则连接成功
        //中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等）
        cout<<"mysql connection"<<endl;
        return true;
    }else{
        cout<<"mysql disconnection "<<mysql_error(mysql_);
        return false;
    }
    return false;                       
}

string Mysql::mysqlQuery(string queryCmd){
    string res = "";
    if(mysql_query(mysql_,queryCmd.c_str())){ //返回0查询成功
        cout<<"mysql query default"<<endl;
        return res;
    }
    if(!(mysqlRes_ = mysql_store_result(mysql_))){
        cout<<"mysql get result default"<<endl;
        return res;
    }
    MYSQL_ROW row;
    while(row = mysql_fetch_row(mysqlRes_)){
        cout<<row[0]<<":"<<row[1]<<endl;
    }
    return res;
}