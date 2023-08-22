#ifndef __USER_H__
#define __USER_H__

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#include "../tool/mysql_operation.h"

#define USER_COMMON = 1
#define USER_ADMIN  = 2
#define USER_SUPER  = 3
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

class UerCommon:public User{

};

class UserAdmin:public User{

};

class UserSuper:public User{

};

#endif