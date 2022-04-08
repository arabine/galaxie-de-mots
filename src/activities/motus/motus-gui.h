#ifndef MOTUS_GUI_H
#define MOTUS_GUI_H

#include "motus.h"
#include "gfx-engine.h"
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



class MotusGui : public Scene
{
public:
    MotusGui(GfxSystem &s);

private:
    Motus mMotus;

    std::string mTextWin;
    std::string mTextLost;

    Timer<std::chrono::milliseconds, std::chrono::steady_clock> mTimer;

    bool DrawMenuBar();
    void DrawWords();
    // void DrawKeyboard();
    void DrawInfoWindow();
};


#endif // MOTUS_GUI_H
