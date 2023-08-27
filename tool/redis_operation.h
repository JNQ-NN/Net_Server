#include <iostream>
#include <sw/redis++/redis++.h>
using namespace std;
using namespace sw::redis;
#include <hiredis/read.h>
static auto redis = Redis("tcp://127.0.0.1:6379");
void redisTest(){
    redis.set("key","value");
    auto value = redis.get("key");
    cout<<*value<<endl;
}

