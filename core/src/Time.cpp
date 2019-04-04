#include "Time.hpp"

namespace Engine {

    float Time::delta_time_ = 0;
    bool Time::paused_ = false;

    float Time::time_scale_ = 1;
    float Time::last_time_scale_ = 1;
    std::chrono::milliseconds Time::start_time_ = currentSysTimeMS();
    std::chrono::milliseconds Time::last_loop_time_ = start_time_;

    void Time::start() {
        Time::start_time_ = Time::currentSysTimeMS();
        Time::last_loop_time_ = start_time_;
    }

    bool Time::togglePause() {
        paused_ = !paused_;
        if (paused_) {
            last_time_scale_ = time_scale_;
            time_scale_ = 0;
        }
        else {
            time_scale_ = last_time_scale_;
            last_time_scale_ = 0;
        }
        return paused_;
    }

    float Time::setTimeScale(float time_scale) {
        float t = Time::time_scale_;
        if (time_scale == 0 && !Time::paused_) {
            togglePause();
        }
        else if (time_scale > 0) {
            if (paused_) togglePause();
            Time::time_scale_ = time_scale;
        }
        return t;
    }

    float Time::getUpTime()
    {
        float time = (float)(Time::elapsedTimeMS().count());
        float deltaTime = time - Time::last_loop_time_.count();
        std::chrono::milliseconds llt((int)(time));
        Time::last_loop_time_ = llt;
        return deltaTime * Time::getTimeScale();
    }

    std::chrono::milliseconds Time::currentSysTimeMS()
    {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    }

    std::chrono::milliseconds Time::elapsedTimeMS()
    {
        return currentSysTimeMS() - start_time_;
    }

    std::chrono::seconds Time::currentSysTimeS()
    {
        using namespace std::chrono;
        return duration_cast<seconds>(system_clock::now().time_since_epoch());
    }

    std::chrono::seconds Time::elapsedTimeS()
    {
        using namespace std::chrono;
        return duration_cast<seconds>(currentSysTimeMS() - start_time_);
    }

    float Time::msToSec(long ms)
    {
        return ms / 1000.0f;
    }

}