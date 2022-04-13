#ifndef COMMON_H
#define COMMON_H


#include <chrono>
#include <string>

std::string replaceStringAll(std::string str, const std::string& old, const std::string& new_s);


template <class DT = std::chrono::milliseconds,
          class ClockT = std::chrono::steady_clock>
class Timer
{
    using timep_t = typename ClockT::time_point;
    timep_t _start = ClockT::now(), _end = {};

public:
    void tick() {
        _end = timep_t{};
        _start = ClockT::now();
    }

    void tock() { _end = ClockT::now(); }

    template <class T = DT>
    auto duration() const {
        return std::chrono::duration_cast<T>(_end - _start);
    }
};



#endif // COMMON_H
