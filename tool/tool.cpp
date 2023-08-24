#include "tool.h"

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
    int len = 0;
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
