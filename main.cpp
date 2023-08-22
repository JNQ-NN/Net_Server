#include "iostream"
#include <asio.hpp>
using namespace std;
#include "tool/log.h"
#include "tool/json.h"
#include "tool/lock.h"
#include "tool/tool.h"
#include "net_server/server.h"
#include "tool/include/threadPool.h"
#include "net_client/include/clientEchoSync.h"

int main(int args,char** argv){
    /* log4cplus config*/
    log4cplus::Initializer initializer;
    log4cplus::PropertyConfigurator::doConfigure(log4cplus_Conf_File);
    Log log;

    if(args>1 && !strcmp(argv[1],"server")){
        asio::io_context ioc;
        Server server(ioc,6666);
        server.start_accept();
        ioc.run();
    }else if(args>1 && !strcmp(argv[1],"client")){
        cout<<"client"<<endl;
        clientEcho();
    }


}
