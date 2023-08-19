#include "iostream"
#include <asio.hpp>
using namespace std;
#include "tool/json.h"
#include "tool/log.h"
#include "tool/lock.h"
#include "tool/include/threadPool.h"


int main(){
    /* log4cplus config*/
    log4cplus::Initializer initializer;
    log4cplus::PropertyConfigurator::doConfigure(log4cplus_Conf_File);
    Log log;
    Log::test();
    mainLog_INFO("main log test");
}
