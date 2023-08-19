#include "iostream"
#include <vector>
using namespace std;
#include "tool/json.h"
#include "tool/log.h"
#include "tool/lock.h"
#include "tool/include/threadPool.h"
#include <stdio.h>
void json_test(){
    cJSON* cj = cJSON_CreateObject();
    cJSON_AddNumberToObject(cj,"test",123);
    cJSON* arr = cJSON_CreateArray();
    cJSON* arrItem = cJSON_CreateObject();
    cJSON_AddStringToObject(arrItem,"cx","存储111");
    cJSON_AddItemToArray(arr,arrItem);
    cJSON* arrItem2 = cJSON_CreateObject();
    cJSON_AddStringToObject(arrItem2,"cx","存储222");
    cJSON_AddItemToArray(arr,arrItem2);
    cJSON_AddItemToObject(cj,"存储",arr);
    cout<<cJSON_Print(cj)<<endl;

    Json j(cj);
    json_t jt = cJSON_GetObjectItem(j.json(),"存储");
    cout<<jt->type<<endl;
    cout<<(1<<5)<<endl;
    cout<<cJSON_Print(jt)<<endl;
   
    for(int i = 0;i< cJSON_GetArraySize(jt);i++){
        json_t j = cJSON_GetArrayItem(jt,i);
        cout<<cJSON_GetObjectItem(j,"cx")->valuestring<<endl;
    }

}


// void threadTest(){
//     vector<thread> vt;
//     for(int i = 0;i<10;i++){
//         mx.lock();
//         this_thread::sleep_for(chrono::seconds(1));
//         vt.emplace_back(fun,i);
//         mx.unlock();
//     }
//     for(auto& v:vt){
//         if(v.joinable()){
//             v.join();
//         }
//     }
// }


void testt(){
    mutex m;
    condition_variable cond;
    unique_lock<mutex> ul(m);
    cond.wait(ul,[](){
        return false;
    });
    cout<<111<<endl;

}

// int fun(){
//     this_thread::sleep_for(chrono::seconds(1));
//     cout<<1<<endl;
//     return 0;
// }

int fun(int value){
    this_thread::sleep_for(chrono::seconds(1));
    cout<<value<<endl;
    return 0;
}
int main(){
    /* log4cplus config*/
    log4cplus::Initializer initializer;
    log4cplus::PropertyConfigurator::doConfigure(log4cplus_Conf_File);
    Log log;

    json_test();
    
    //threadTest();
    //testIncludeFun();
    //testt();   

    ThreadPool threadPool; 
    threadPool.commit(fun,8);
    threadPool.commit(fun,5);
    threadPool.commit(fun,7);

    cout<<__FILE__<<endl;
    cout<<__FUNCTION__<<endl;
    this_thread::sleep_for(chrono::seconds(5));
}

