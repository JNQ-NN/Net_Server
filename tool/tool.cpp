#include "tool.h"

/*
* @brief  执行linux命令
* @return 执行linux指令的返回值，即`$?`
*/
int TOOL::cmd(const char* command,char* res,size_t size){
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