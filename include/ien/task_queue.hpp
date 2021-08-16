#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>
#include <type_traits>
#include <vector>

namespace ien
{
    typedef std::function<void()> task_t;
    class task_queue
    {
    private:
        std::vector<task_t> _tasks;
        std::atomic<int> _current_task = 0;
        std::vector<std::thread> _threads;
        std::mutex _run_mux;
        size_t _max_concurrent;
        bool _detached = false;
        bool _started = false;

    public:
        task_queue(size_t max_concurrent_tasks = std::thread::hardware_concurrency()) noexcept;

        void add_task(task_t task);

        void run(bool detached = false);
        void join();

    private:
        const task_t* dequeue_task();
        void worker_thread();
        void join_threads();
    };
}