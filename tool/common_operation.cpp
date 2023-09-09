#include "common_operation.h"

/*
* 用于同步持久层数据库和缓冲层数据库
*/
void Common::mysqlSyncRedis(){
    Mysql* ms = new Mysql();
    MYSQL_RES* queryRes = nullptr;
    MYSQL_ROW row;
    ms->mysqlConnection();
    
    /*用户同步*/
    queryRes = ms->mysqlQuery("select * from user;");
    while(true){
        row = mysql_fetch_row(queryRes);
        if(row == NULL) break;
        RedisMSG::appendSet("User",row[1]);
    }

    cout<<"mysql-Sync-Redis"<<endl;
    mainLog_INFO("mysql-Sync-Redis");
}
