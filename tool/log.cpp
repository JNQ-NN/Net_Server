#include "log.h"

log4cplus::Logger Log::mainLogger_    = log4cplus::Logger::getInstance("mainLog");
log4cplus::Logger Log::consoleLogger_ = log4cplus::Logger::getInstance("consoleLog");

Log::Log(){
}

log4cplus::Logger& Log::getMainLogger(){
    return mainLogger_;
}

log4cplus::Logger& Log::getConsoleLogger(){
    return consoleLogger_;
}

void Log::test(){
    mainLog_TRACE("trace");
    mainLog_DEBUG("debug");
    mainLog_INFO("info");
    mainLog_WARN("warn");
    mainLog_ERROR("error");
    mainLog_FATAL("fatal");
}