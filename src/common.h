#ifndef COMMON_H
#define COMMON_H


#include <chrono>
#include <string>
#include <random>


// Returns random integer in closed range [low, high]. Example:
// UniformRandomInt rng(0, nbWords5Letters - 1);
// int index = rng.get();
class UniformRandomInt
{
    std::random_device _rd{};
    std::mt19937 _gen{_rd()};
    std::uniform_int_distribution<int> _dist;

public:
    UniformRandomInt() {
        set(1, 10);
    }
    UniformRandomInt(int low, int high) {
        set(low, high);
    }

    // Set the distribution parameters low and high.
    void set(int low, int high) {
        std::uniform_int_distribution<int>::param_type param(low, high);
        _dist.param(param);
    }

    // Get random integer.
    int get() {
        return _dist(_gen);
    }
};



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
