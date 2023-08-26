#include "iostream"
#include <asio.hpp>
using namespace std;
#include "tool/log.h"
#include "tool/json.h"
#include "tool/lock.h"
#include "tool/tool.h"
#include "net_server/server.h"
#include "net_client/client.h"
#include "tool/include/threadPool.h"
#include <vector>
// #include "net_client/include/clientEchoSync.h"
// #include "net_server/include/serverEchoAsync.h"

log4cplus::Initializer initializer;



int main(int args,char** argv){
    /* log4cplus config*/
    log4cplus::PropertyConfigurator::doConfigure(log4cplus_Conf_File);
    Log log;
    // Log::test();
    // log.test();

    if(args>1 && !strcmp(argv[1],"server")){
        asio::io_context ioc;
        Server server(ioc,6666);
        server.start_accept();
        ioc.run();
        //serverEcho();
    }else if(args>1 && !strcmp(argv[1],"client")){
        // cout<<"client"<<endl;
        // clientEcho();
        asio::io_context ioc;
        Client client(ioc,"111.231.12.131",6666);
        ioc.run();
    }
    
    // int* ii = fun();
    // cout<<ii<<endl;
    // cout<<*ii<<endl;
   
}