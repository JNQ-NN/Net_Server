#ifndef __COMMON_OPERATION__
#define __COMMON_OPERATION__

#include <iostream>
using namespace std;
#include "mysql_operation.h"
#include "redis_operation.h"

namespace Common{

    void mysqlSyncRedis();

}

#endif
