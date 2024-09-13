// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

// https://www.cnblogs.com/pandamohist/p/15228995.html
// https://blog.csdn.net/sijia5135/article/details/115356079

#include "threadpool.h"

#if defined(LINUX) || defined(ANDROID)
#   include <pthread.h>
#elif !defined(WIN) 
#   include <pthread/pthread.h>
#endif // !WIN

NS_CU_BEGIN

threadpool::threadpool(size_t thread_size, std::string &&name)
: is_stop_(false), name_(name) {
    for (int idx=0; idx<thread_size; idx++) {
        workers_.emplace_back([this, idx, name] {
//            LOGI(TAG, "threadpool start %s%zu", name_.c_str(), idx);
#if defined(LINUX) || defined(ANDROID)
            pthread_setname_np(pthread_self(), name_.append(std::to_string(idx)).c_str());
#elif !defined(WIN)
            pthread_setname_np(name_.append(std::to_string(idx)).c_str());
#endif
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queue_mtx_);
                    this->condition_.wait(lock, [this] {
                        return this->is_stop_ || !this->tasks_.empty();
                    });
                    
                    if (this->is_stop_ && this->tasks_.empty()) {
//                        LOGI(TAG, "threadpool is_stop_ %s%zu", name_.c_str(), idx);
                        return;
                    }
                    task = std::move(this->tasks_.front());
                    this->tasks_.pop();
                }
                task();
            }
        });
    }
}

void threadpool::clear() {
    std::unique_lock<std::mutex> lock(queue_mtx_);
    std::queue<std::function<void()>> empty_queue;
    std::swap(tasks_, empty_queue);
}

threadpool::~threadpool() {
    {
        std::unique_lock<std::mutex> lock(queue_mtx_);
        is_stop_ = true;
    }
    condition_.notify_all();
    for (std::thread &worker : workers_) {
        worker.join();
    }
//    LOGI(TAG, "threadpool stopped !");
}

NS_CU_END
