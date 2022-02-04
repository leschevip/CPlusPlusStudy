#pragma once

class Timer {

private:
    bool active = false;
public:
	Timer();
    
	template <typename TFunc, typename... TT>
    void SetInterval(int interval, TFunc&& func, TT&& ... args);
    void Stop();
};