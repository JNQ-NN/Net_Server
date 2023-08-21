#ifndef __MYSQL_OPERATION__
#define __MYSQL_OPERATION__
#include <iostream>
#include <mysql/mysql.h>
using namespace std;

/*
 *@breif Mysql数据库
*/
class Mysql{
    typedef MYSQL* mysql_t;
public:
    Mysql();
    ~Mysql();

    bool mysqlConnection(const char* hostName="localhost",
                         const char* userName="root",const char* userPwd="123456789",
                         const char* userDatabase="netDatabase",unsigned int port=3306);
    string mysqlQuery(string queryCmd);
private:
    mysql_t mysql_;
    MYSQL_RES* mysqlRes_;
};
#endif