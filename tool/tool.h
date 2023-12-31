#ifndef __TOOL__H__
#define __TOOL__H__

#include <iostream>
#include "string.h"
using namespace std;

namespace TOOL{
    int cmd(const char* command);
    int cmd(const char* command,char* res,size_t size);
    string getCurTime();
}

namespace TOOL_Str{
    size_t strToNum(const char* str);
}

#endif