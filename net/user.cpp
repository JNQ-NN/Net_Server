#include "user.h"

User::User(){
    ms_ = new Mysql();
}

User::~User(){
    if(ms_ != nullptr){
        delete ms_;
        ms_ = nullptr;
    }
}
