#ifndef __MYSQL_OPERATION__
#define __MYSQL_OPERATION__
#include <iostream>
#include <mysql/mysql.h>
#include <vector>
using namespace std;

typedef MYSQL* mysql_t;

/*
 *@breif Mysql数据库
*/
class Mysql{ 
public:
    Mysql();
    ~Mysql();

    bool mysqlConnection(const char* hostName="localhost",
                         const char* userName="root",const char* userPwd="123456789",
                         const char* userDatabase="netDatabase",unsigned int port=3306);
    MYSQL_RES* mysqlQuery(const char* queryCmd);
    MYSQL_RES* mysqlAppend(const char* appendCmd);
    //vector<string> mysqlQueryV(const char* queryCmd);
    
private:
    mysql_t mysql_;
    MYSQL_RES* res_ = nullptr;
    void init();
    bool isConnection();
    void freeRes();
};

#endif