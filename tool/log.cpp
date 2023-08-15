#include "log.h"

void logTest(){
    BasicConfigurator config;
    config.configure();

    Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("main"));
    LOG4CPLUS_WARN(logger,LOG4CPLUS_TEXT("Hello Log4cplus!"));
}