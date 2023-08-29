#include "tool.h"

int TOOL::cmd(const char* command){
    if(command==nullptr) return -1;
    FILE* fp = NULL;
    if((fp = popen(command,"r")) != NULL){
          return pclose(fp);
    }
    return -1;
}

/*
* @brief  执行linux命令
* @return 执行linux指令的返回值，即`$?`
*/
int TOOL::cmd(const char* command,char* res,size_t size){
    //popen()  创建管道，调用fork产生子进程，执行一个shell运行命令
    //wget()   读取标准I/O流信息
    //pclose() 关闭管道，即关闭标准I/O流
    if(command==nullptr) return -1;
    char* buff = res;
    size_t len = 0;
    FILE* fp = NULL;
    if((fp = popen(command,"r")) != NULL){
        while(fgets(buff,size,fp) != NULL){
            if((len == strlen(buff)) == 0){
                break;
            }
            size -= len;
            buff += len;
        }
        return pclose(fp);
    }
    return -1;
}

string TOOL::getCurTime(){
    time_t t = time(NULL);
    struct tm* stime=localtime(&t);
    char curTime[32]{0};
    snprintf(curTime,sizeof(curTime),"%04d-%02d-%02d %02d:%02d:%02d",1900+stime->tm_year,1+stime->tm_mon,stime->tm_mday, stime->tm_hour,stime->tm_min,stime->tm_sec);
    string curTimeString = curTime;
    return curTimeString;
}

/*
* @brief 字符串转int，不做校验
*/
size_t TOOL_Str::strToNum(const char* str){
    return atoi(str);
}