#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <future>
#include <functional>


class ThreadPool
{
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex m;
    std::condition_variable condition;
    bool stop;

public:
    explicit ThreadPool(size_t poolSize)
    {
    	stop = false;
    	for (size_t i = 0; i < poolSize; i++)
    		workers.emplace_back([this]
    		{
    			while(true)
    			{
    				std::function<void()> task;
    				{
    					std::unique_lock<std::mutex> lock(m);
    					condition.wait(lock, [this]{return (stop || !tasks.empty());});
    					if (stop && tasks.empty())
    						return;
    					task = std::move(tasks.front());
    					tasks.pop();
    				}
    				task();
    			}
    		});
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
    	using return_type = decltype(func(args...));

    	auto task = std::make_shared< std::packaged_task<return_type()> >(
    		std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
    		);
        
	    std::future<return_type> res = task->get_future();
	    {
	        std::unique_lock<std::mutex> lock(m);
	        if(stop)
	            throw std::runtime_error("");
	        tasks.emplace([task](){ (*task)(); });
	    }
	    condition.notify_one();
	    return res;
    }

    ~ThreadPool()
    {
    	{
	        std::unique_lock<std::mutex> lock(m);
	        stop = true;
    	}
	    condition.notify_all();
	    for(std::thread &worker: workers)
	        worker.join();
    }
};


