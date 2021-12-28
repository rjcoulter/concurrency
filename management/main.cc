#include <iostream>
#include <thread>
#include <string>

// Dummy functions
void do_some_work() {};
void do_work_in_current_thread() {};

// RAII Class to handle joining
// threads in destructor
class thread_guard
{
    std::thread t;
public:
    explicit thread_guard(std::thread t_):
        t(std::move(t_))
    {
        if(!t.joinable())
            throw std::logic_error("No thread");
    }
    ~thread_guard()
    {
        t.join();
    }

    // Ensure copy/copy-assignment constructors
    // not auto provided by compiler
    thread_guard(thread_guard const&)=delete; 
    thread_guard& operator=(thread_guard const&)=delete;
};

// Automatically joins in the destructor
// on track for C++20 as std::jthread
class joining_thread
{
    std::thread t;
public:
    joining_thread() noexcept=default;
    template<typename Callable,typename ... Args>
    explicit joining_thread(Callable&& func,Args&& ... args):
        t(std::forward<Callable>(func),std::forward<Args>(args)...)
    {}
    explicit joining_thread(std::thread t_) noexcept:
        t(std::move(t_))
    {}
    joining_thread(joining_thread&& other) noexcept:
        t(std::move(other.t))
    {}
    joining_thread& operator=(joining_thread&& other) noexcept
    {
        if(joinable())
            join();
        t=std::move(other.t);
        return *this;
    }
    joining_thread& operator=(std::thread other) noexcept
    {
        if(joinable())
            join();
        t=std::move(other);
        return *this;
    }
    ~joining_thread() noexcept
    {
        if(joinable())
            join();
    }
    void swap(joining_thread& other) noexcept
    {
        t.swap(other.t);
    }
    std::thread::id get_id() const noexcept{
        return t.get_id();
    }
    bool joinable() const noexcept
    {
        return t.joinable();
    }
    void join()
    {
        t.join();
    }
    void detach()
    {
        t.detach();
    }
    std::thread& as_thread() noexcept
    {
        return t;
    }
    const std::thread& as_thread() const noexcept
    {
        return t;
    }
};

int main() 
{
    std::thread my_thread(do_some_work);
    my_thread.join();
}