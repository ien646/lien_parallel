#include <ien/task_queue.hpp>

namespace ien
{
    task_queue::task_queue(size_t max_concurrent_tasks) noexcept
        : _max_concurrent(max_concurrent_tasks)
    { }

    void task_queue::run(bool detached)
    {
        {
            std::lock_guard<std::mutex> lock(_run_mux);
            if (_started) { return; }
            _started = true;
        }

        _detached = detached;
        for(size_t i = 0; i < _max_concurrent; ++i)
        {
            _threads.push_back(std::thread(&task_queue::worker_thread, this));
        }
        
        if(!_detached) { join_threads(); }
    }

    void task_queue::add_task(task_t task)
    {
        _tasks.push_back(task);
    }

    void task_queue::join()
    {
        if(_detached) { join_threads(); }
    }

    const task_t* task_queue::dequeue_task()
    {
        if(_tasks.size() > _current_task)
        {
            task_t* res = &_tasks.at(_current_task);
            ++_current_task;
            return res;
        }
        return nullptr;
    }

    void task_queue::worker_thread()
    {
        while(const task_t* task = dequeue_task())
        {
            if(task == nullptr) { break; }
            (*task)();
        }
    }

    void task_queue::join_threads()
    {
        for(auto& th : _threads) { th.join(); }
    }
}