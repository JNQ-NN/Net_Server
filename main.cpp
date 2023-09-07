#include "iostream"
#include <asio.hpp>
#include <vector>
#include <stack>
using namespace std;
#include "tool/log.h"
#include "tool/json.h"
#include "tool/tool.h"
#include "net_server/server.h"
#include "net_client/client.h"
#include "tool/include/threadPool.h"
#include "tool/redis_operation.h" 
#include "tool/common_operation.h"
#include <stdlib.h>
#include "net_server_http/server_http.h"

log4cplus::Initializer initializer;


void print(const asio::error_code& error,asio::steady_timer* timer,int* count){
    timer->expires_at(timer->expires_at() + std::chrono::seconds(1));
    cout<<1<<endl;
}

int main(int args,char** argv){
    /* log4cplus config*/
    log4cplus::PropertyConfigurator::doConfigure(log4cplus_Conf_File);
    Log log;
    RedisMSG::checkRedisConnection();
    Common::mysqlSyncRedis();

    if(args>1 && !strcmp(argv[1],"server")){
        asio::io_context ioc;
        Server server(ioc,6666);
        server.start_accept();
        ioc.run();  
    }else if(args>1 && !strcmp(argv[1],"client")){
        asio::io_context ioc;
        Client client(ioc,"111.231.12.131",6666);
        ioc.run();
    }else if(args>1 && !strcmp(argv[1],"serverHTTP")){
        asio::io_context ioc;
        ServerHTTP server(ioc,8888);
        server.start_accept();
        ioc.run();  
    }else if(args>1 && !strcmp(argv[1],"test")){
        asio::io_context ioc;
        asio::steady_timer timer = asio::steady_timer(ioc,std::chrono::seconds(3));
        int count = 0;
        cout<<"1111"<<endl;
        timer.async_wait(std::bind(&print,std::placeholders::_1,&timer,&count));
        cout<<"2222"<<endl;
        ioc.run();

    }
}
