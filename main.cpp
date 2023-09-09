#include "iostream"

#include <stack>
#include <vector>
#include <asio.hpp>
#include <coroutine>
using namespace std;
#include "tool/log.h"
#include "tool/json.h"
#include "tool/tool.h"
#include "net_server/server.h"
#include "net_client/client.h"
#include "tool/include/threadPool.h"
#include "tool/redis_operation.h" 
#include "tool/common_operation.h"
#include <stdlib.h>
#include "net_server_http/server_http.h"

log4cplus::Initializer initializer;

/* 协程示例 */

struct TestAwait{
    bool await_ready(){
        cout<<"await_ready"<<endl;
        return false;
    }
    void await_resume(){
        cout<<"await_resum"<<endl;
    }
    void await_suspend(coroutine_handle<> h){
        cout<<"await_suspend"<<endl;
        coroutine_handle<> handle = h;
    }
};

struct TestCoroutine{
    struct TestPromise{
        TestCoroutine get_return_object(){
            return std::coroutine_handle<TestPromise>::from_promise(*this);
        }
        std::suspend_never initial_suspend(){ return {}; }
        std::suspend_always final_suspend () noexcept { return {}; }
        void unhandled_exception(){ }
    };
    using promise_type = TestPromise;
    TestCoroutine(std::coroutine_handle<TestPromise> h):handle(h){}
    std::coroutine_handle<TestPromise> handle;
};

TestCoroutine TestFun(){
    // cout<<"Hello"<<endl;
    // co_await std::suspend_always{};
    // cout<<"World"<<endl;
    // co_await std::suspend_never{};
    co_await TestAwait();
}

void print(const asio::error_code& error,asio::steady_timer* timer,int* count){
    timer->expires_at(timer->expires_at() + std::chrono::seconds(1));
    cout<<1<<endl;
}

int main(int args,char** argv){
    /* log4cplus config*/
    log4cplus::PropertyConfigurator::doConfigure(log4cplus_Conf_File);
    Log log;
    RedisMSG::checkRedisConnection();
    Common::mysqlSyncRedis();

    if(args>1 && !strcmp(argv[1],"server")){
        asio::io_context ioc;
        Server server(ioc,6666);
        server.start_accept();
        ioc.run();  
    }else if(args>1 && !strcmp(argv[1],"client")){
        asio::io_context ioc;
        Client client(ioc,"111.231.12.131",6666);
        ioc.run();
    }else if(args>1 && !strcmp(argv[1],"serverHTTP")){
        asio::io_context ioc;
        ServerHTTP server(ioc,8888);
        server.start_accept();
        ioc.run();  
    }else if(args>1 && !strcmp(argv[1],"test")){
        //timer
        // asio::io_context ioc;
        // asio::steady_timer timer = asio::steady_timer(ioc,std::chrono::seconds(3));
        // int count = 0;
        // cout<<"1111"<<endl;
        // timer.async_wait(std::bind(&print,std::placeholders::_1,&timer,&count));
        // cout<<"2222"<<endl;
        // ioc.run();

        //协程构成 promise + awaitable + handle
        TestCoroutine coro = TestFun();
        cout<<"calling resume"<<endl;
        coro.handle.resume();
        cout<<"destory"<<endl;
        coro.handle.destroy();
    }
}
