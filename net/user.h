#ifndef __USER_H__
#define __USER_H__

#include <iostream>
#include <stdio.h>
using namespace std;
#include "../tool/mysql_operation.h"

class User{
public:
    User();
    virtual ~User();
    // int getId();
    // char* getName();
private:
    int id;
    int identity;
    char name[10];
    char pwd[20];
    char ipAddress[16];
    Mysql* ms_;
    bool isConnection;

    bool login();
    bool verify(const char* tempName,const char* tempPwd);
    //bool sign();
    //bool connectionMysql();
};

class CommonUser:public User{

};

class AdminUser:public User{

};

#endif