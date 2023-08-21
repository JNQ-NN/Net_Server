#include "iostream"
#include <asio.hpp>
using namespace std;
#include "tool/json.h"
#include "tool/log.h"
#include "tool/lock.h"
#include "tool/include/threadPool.h"

#include "net_client/include/clientEchoSync.h"
#include "net_server/include/serverEchoAsync.h"

#include "tool/mysql_operation.h"

int main(int args,char** argv){
    /* log4cplus config*/
    log4cplus::Initializer initializer;
    log4cplus::PropertyConfigurator::doConfigure(log4cplus_Conf_File);
    Log log;

    if(args>1 && !strcmp(argv[1],"server")){
        cout<<"server"<<endl;
        serverEcho();
    }else if(args>1 && !strcmp(argv[1],"client")){
        cout<<"client"<<endl;
        clientEcho();
    }

    Mysql m;
    m.mysqlConnection();
    m.mysqlQuery("select * from test;");
}
