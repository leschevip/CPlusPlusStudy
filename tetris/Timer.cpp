#include "Timer.h"

template <typename TFunc, typename... TT>
void Timer::SetInterval(int interval, TFunc&& func, TT&& ... args )
{
    this->active = true;
    /*
    std::thread t([=]() {
        while (true) {
            if (this->active) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if (this->active) return;
            std::invoke(std::forward<TFunc>(func), std::forward<TT>(args)...);
        }
        });
    
    t.detach();
    */
}

Timer::Timer()
{
}

void Timer::Stop() {
    this->active = false;
}