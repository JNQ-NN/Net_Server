#ifndef __LOG_H__
#define __LOG_H__
#include <iomanip>
#include <iostream>

#include <log4cplus/logger.h>
#include <log4cplus/initializer.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loglevel.h>
#include <log4cplus/appender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/loggingmacros.h>
using namespace std;
// using namespace log4cplus;

#define log4cplus_Conf_File "./conf/log_conf"

class Log{
public:
    Log();
    static log4cplus::Logger& getMainLogger();
    static log4cplus::Logger& getConsoleLogger();
    void test();
private:
    static log4cplus::Logger mainLogger_;     //用于核心日志
    static log4cplus::Logger consoleLogger_;  //用于临时调试，显示在console
};

/* mainLog */
#define mainLog_TRACE(logEvent) LOG4CPLUS_TRACE(Log::getMainLogger(),logEvent)
#define mainLog_DEBUG(logEvent) LOG4CPLUS_DEBUG(Log::getMainLogger(),logEvent)
#define mainLog_INFO(logEvent)  LOG4CPLUS_INFO(Log::getMainLogger(),logEvent)
#define mainLog_WARN(logEvent)  LOG4CPLUS_WARN(Log::getMainLogger(),logEvent)
#define mainLog_ERROR(logEvent) LOG4CPLUS_ERROR(Log::getMainLogger(),logEvent)
#define mainLog_FATAL(logEvent) LOG4CPLUS_FATAL(Log::getMainLogger(),logEvent)

/* consoleLog */
#define consoleLog_TRACE(logEvent) LOG4CPLUS_TRACE(Log::getConsoleLogger(),logEvent)
#define consoleLog_DEBUG(logEvent) LOG4CPLUS_DEBUG(Log::getConsoleLogger(),logEvent)
#define consoleLog_INFO(logEvent)  LOG4CPLUS_INFO(Log::getConsoleLogger(),logEvent)
#define consoleLog_WARN(logEvent)  LOG4CPLUS_WARN(Log::getConsoleLogger(),logEvent)
#define consoleLog_ERROR(logEvent) LOG4CPLUS_ERROR(Log::getConsoleLogger(),logEvent)
#define consoleLog_FATAL(logEvent) LOG4CPLUS_FATAL(Log::getConsoleLogger(),logEvent)

#endif

// toDo __FILE__ __LINE__ __FUNCTION