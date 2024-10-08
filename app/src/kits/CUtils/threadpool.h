// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef __CU_THREADPOOL_H__
#define __CU_THREADPOOL_H__

#include <CUtils/def_build.h>
#include "CUtilsDef.h"

#include <string>
#include <vector>
#include <queue>
#include <functional>

#include <thread>
#include <future>
#include <condition_variable>
#include <mutex>

NS_CU_BEGIN
class threadpool {
public:
    explicit threadpool(size_t thread_size, std::string &&name);
    ~threadpool();

    template<class F, class... Args>
    auto enqueue(F &&f, Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type>;

    template<class F, class... Args>
    void enqueue_void(F &&f, Args &&... args);

    size_t task_size() { return tasks_.size(); }
    
    void clear();

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex queue_mtx_;
    std::condition_variable condition_;
    bool is_stop_;

    // for debug
    std::string name_;
};

template<class F, class... Args>
auto threadpool::enqueue(F &&f, Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
    using ret_type = typename std::result_of<F(Args...)>::type;
    using task_type = std::packaged_task<ret_type()>;
    auto task_param = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    
    auto task = std::make_shared<task_type>(task_param);
    std::future<ret_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mtx_);
        if (is_stop_) {
            throw std::runtime_error("enqueue on stopped threadpool is not allowed");
        }
        tasks_.emplace([task]() { (*task)(); });
    }
    condition_.notify_one();
    return res;
}

template<class F, class... Args>
void threadpool::enqueue_void(F &&f, Args &&... args) {
    auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    {
        std::unique_lock<std::mutex> lock(queue_mtx_);
        if (is_stop_) {
            throw std::runtime_error("enqueue on stopped threadpool is not allowed");
        }
        tasks_.emplace([task]() { (*task)(); });
    }
    condition_.notify_one();
}

NS_CU_END

#endif // __CU_THREADPOOL_H__
