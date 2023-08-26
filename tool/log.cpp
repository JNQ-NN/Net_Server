#include "log.h"

log4cplus::Logger Log::mainLogger_    = log4cplus::Logger::getInstance("mainLog");
log4cplus::Logger Log::consoleLogger_ = log4cplus::Logger::getInstance("consoleLog");

Log::Log(){
    mainLog_INFO("#############");
    mainLog_INFO("main log init");
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

    consoleLog_TRACE("trace");
    consoleLog_DEBUG("debug");
    consoleLog_INFO("info");
    consoleLog_WARN("warn");
    consoleLog_ERROR("error");
    consoleLog_FATAL("fatal");
}