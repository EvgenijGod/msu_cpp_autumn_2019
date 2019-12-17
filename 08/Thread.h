#include <vector>
#include <thread>
#include <queue>
#include <future>
#include <functional>
#include <algorithm>

class ThreadPool {
    using my_func = std::function<void ()>;
private:
    std::queue<my_func> Q;
    std::condition_variable Q1;
    std::mutex sem;
    template <class Promise_ptr, class F, class... Args>
    void maker_of_task(Promise_ptr point, F func, Args... args) {
        point->set_value(func(args...));
        delete point;
    }
    template <class F, class... Args>
    void maker_of_task(std::promise<void> *point, F f, Args... args) {
        point->set_value();
        delete point;
        f(args...);
    }
    std::vector<std::thread> threads;
    std::atomic<bool> living;
    size_t size;
public:
    explicit ThreadPool(size_t poolSize) {
        living = true;
        size = poolSize;
        for (size_t i = 0; i < poolSize; i++) {
            threads.emplace_back(
                    [this](){
                        while (true) {
                            if (living == false) {
                                break;
                            }
                            std::unique_lock <std::mutex> lock(sem);
                            if (Q.empty() == false) {
                                auto m_tmp(std::move(Q.front()));
                                Q.pop();
                                lock.unlock();
                                m_tmp();
                            } else {
                                while (true) {
                                    if (living == false) {
                                        break;
                                    }
                                    Q1.wait(lock);
                                    if (Q.empty() == false) {
                                        break;
                                    }
                                }
                            }
                        }
                    });
        }
    }
    template <class F, class... Args>
    auto exec(F f, Args... args) -> std::future<decltype(f(args...))> {
        auto promise = new std::promise<decltype(f(args...))>();
        auto future = promise->get_future();
        auto task = [this](std::promise<decltype(f(args...))> *promise, F func, Args... args) {
            maker_of_task(promise, func, args...);
        };
        my_func t = std::bind(task, promise, f, args...);
        sem.lock();
        Q.push(t);
        sem.unlock();
        Q1.notify_one();
        return future;
    }
    ~ThreadPool() {
        if (living == true) {
            living = false;
            Q1.notify_all();
            for (size_t i = 0; i < size; i++) {
                threads[i].join();
            }
        }
    }
};