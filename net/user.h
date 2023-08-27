#ifndef __USER_H__
#define __USER_H__

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#include "../tool/mysql_operation.h"


#define USER_COMMON  1
#define USER_ADMIN   2
#define USER_SUPER   3

#define USER_NAME_LEN      10
#define USER_PWD_LEN    20
#define USER_IPADDRESS_LEN 16
class User{
public:
    User();
    User(char* name,char* pwd);
    virtual ~User();
    // int getId();
    void setName(char* name);
    char* getName();
private:
    int id_;
    int identity_;
    char* name_;
    char* pwd_;
    char ipAddress_[USER_IPADDRESS_LEN];
    Mysql* ms_;
    bool isConnection_;
};

class UerCommon:public User{

};

class UserAdmin:public User{

};

class UserSuper:public User{

};

#endif