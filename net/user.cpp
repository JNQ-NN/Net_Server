#include "user.h"

User::User(){
    ms_ = new Mysql();
    name_ = new char[USER_NAME_LEN];
    pwd_ = new char[USER_PWD_LEN];
}

User::User(char* name,char* pwd):name_(name),pwd_(pwd){
    cout<<"test:"<<name_<<endl;
}

User::~User(){
    if(ms_ != nullptr){
        delete ms_;
        ms_ = nullptr;
    }
    delete[] name_;
    delete[] pwd_;
}

void User::setName(char* name){
    snprintf(name_,USER_NAME_LEN,"%s",name);
}

char* User::getName(){
    return name_;
}
