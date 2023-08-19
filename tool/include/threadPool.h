#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <atomic>
#include <future>
#include <condition_variable>
using namespace std;
#include "../log.h"


class ThreadPool{
    using Task = function<void()>;
public:
    inline ThreadPool(unsigned short threadNumber=0){         
        getMaxThread();
        consoleLog_INFO("Init ThreadPool");
        try{
            addThread(threadNumber>0?threadNumber:maxThreads_);
        }catch( ... ){
            cout<<"error"<<endl;
        }
        maxThreads_ = maxThreads_>threadNumber?maxThreads_:threadNumber;
        consoleLog_INFO("Init ThreadPool");
    }

    ~ThreadPool(){
        run_ = false;
        cond.notify_all();
        for(auto& tp:threadPool_){
            if(tp.joinable()){
                tp.join();
            }
        } 
    }

    /*
     *@brief 向线程池添加线程
    */
    void addThread(unsigned short size) {
        for (unsigned short i = 0; i < size; i++){
            threadPool_.emplace_back([this]{
                while(run_){
                    Task task;
                    {
                        unique_lock<mutex> ul{ mutex_ };
                        cond.wait(ul,[this](){  //->false 阻塞
                            return !run_ || !tasks_.empty();  //运行|非空
                        });
                        if(!run_ && tasks_.empty()){  //不在运行 或 队列为空 -> 继续阻塞
                            return;
                        }
                        task = tasks_.front();
                        tasks_.pop();
                    }
                    curThreads_--;
                    task();
                    curThreads_++;
                }
            });
            curThreads_++;
        }
    }

    /*
     *@brief 向请求队列添加任务
    */
    template<class F,class ...Args>
    auto commit(F&& f,Args&&... args)->future<decltype(f(args...))>{
        using RetType = decltype(f(args...));
        auto task = make_shared<packaged_task<RetType()>>(bind(forward<F>(f),forward<Args>(args)...));
        future<RetType> future = task->get_future();
        {
            lock_guard<mutex> lg(mutex_);
            this->tasks_.emplace([task]() {
                (*task)();
                });
            }
            cond.notify_one();
        return future;
    }

    
private:  
    vector<thread> threadPool_;            //存储线程的容器
    unsigned short maxThreads_;            //最大线程数量
    atomic<unsigned short> curThreads_{0}; //当前线程数量
    atomic<bool> run_{true};               //线程池运行状态
    queue<Task> tasks_;                    //请求队列 
    unsigned int maxTasks_;                //请求队列的最大请求数量
    atomic<unsigned int> curTasks_;        //当前请求队列的数量
    mutex mutex_;                          //用于添加线程&添加添加任务
    condition_variable cond;               //用于阻塞闲置线程

    /*
     *@brief 获得CPU的最大线程数
    */
    unsigned int getMaxThread(){
        maxThreads_ = thread::hardware_concurrency();
        return maxThreads_;
    }

    /*
     *@brief 获得线程池的线程数量
    */
    unsigned int getCurThread(){
        curThreads_ = threadPool_.size();
        return curThreads_;
    }
};

