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
    }
}
