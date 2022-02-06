#ifndef MOTUSGUI_H
#define MOTUSGUI_H

#include "motus.h"
#include "imgui.h"
#include <chrono>

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

class MotusGui
{
public:
    MotusGui(uint32_t w, uint32_t h);

    bool Process();

private:
    Motus mMotus;

    uint32_t mWidth;
    uint32_t mHeight;

    std::string mMessage;
    Timer<std::chrono::milliseconds, std::chrono::steady_clock> mTimer;

    bool DrawMenuBar();
    void DrawWords();
    void DrawKeyboard();
    void DrawInfoWindow();
};


#endif // MOTUSGUI_H
