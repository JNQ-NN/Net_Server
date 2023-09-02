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
        return false;
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
    freeRes();
    mysql_query(mysql_,queryCmd);
    res_ = mysql_store_result(mysql_);
    if(mysql_errno(mysql_)!=0){
        cout<<"错误编码:"<<mysql_errno(mysql_)<<endl;
        cout<<"错误信息:"<<mysql_error(mysql_)<<endl;
    }
    return res_;
}

MYSQL_RES* Mysql::mysqlAppend(const char* appendCmd){
    freeRes();
    mysql_query(mysql_,appendCmd);  //操作指令都用mysql_query
    
    if(mysql_errno(mysql_)!=0){
        cout<<"错误编码:"<<mysql_errno(mysql_)<<endl;
        cout<<"错误信息:"<<mysql_error(mysql_)<<endl;
    }
    return res_;
}



// vector<string> Mysql::mysqlQueryV(const char* queryCmd){
//     MYSQL_RES* queryRes = nullptr;
//     vector<string> queryResV;
//     queryRes = mysqlQuery(queryCmd);
//     MYSQL_ROW row;
//     while(row = mysql_fetch_row(queryRes)){
//         queryResV.push_back(row[0]);
//     }
// }

void Mysql::init(){
    mysql_init(mysql_);
}

/*
 *@breif 判断数据库是否连接
*/
bool Mysql::isConnection(){
    if(mysql_){
        return (0==mysql_ping(mysql_));
    }
    return false;
}

/*
 * MYSQL_RES* res_ 初始化,每次查询时调用
*/
void Mysql::freeRes(){
    if(res_!=nullptr){
        mysql_free_result(res_);
        res_ = nullptr;
    }
}