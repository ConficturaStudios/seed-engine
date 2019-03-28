#include "Time.hpp"

namespace Engine {

    float Time::delta_time = 0;
    bool Time::paused = false;

    float Time::time_scale = 1;
    float Time::last_time_scale = 1;
    std::chrono::milliseconds Time::start_time = currentSysTimeMS();
    std::chrono::milliseconds Time::last_loop_time = start_time;

    void Time::start() {
        Time::start_time = Time::currentSysTimeMS();
        Time::last_loop_time = start_time;
    }

    bool Time::togglePause() {
        paused = !paused;
        if (paused) {
            last_time_scale = time_scale;
            time_scale = 0;
        }
        else {
            time_scale = last_time_scale;
            last_time_scale = 0;
        }
        return paused;
    }

    bool Time::isPaused() {
        return Time::paused;
    }

    float Time::getDeltaTime() {
        return Time::delta_time;
    }

    float Time::setTimeScale(float time_scale) {
        float t = Time::time_scale;
        if (time_scale == 0 && !Time::paused) {
            togglePause();
        }
        else if (time_scale > 0) {
            if (paused) togglePause();
            Time::time_scale = time_scale;
        }
        return t;
    }

    float Time::getTimeScale()
    {
        return Time::time_scale;
    }

    float Time::getUpTime()
    {
        float time = Time::elapsedTimeMS().count();
        float deltaTime = time - Time::last_loop_time.count();
        std::chrono::milliseconds llt((int)(time));
        Time::last_loop_time = llt;
        return deltaTime * Time::getTimeScale();
    }

    float Time::getLastLoopTime()
    {
        return Time::last_loop_time.count();
    }

    std::chrono::milliseconds Time::currentSysTimeMS()
    {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    }

    std::chrono::milliseconds Time::elapsedTimeMS()
    {
        return currentSysTimeMS() - start_time;
    }

    std::chrono::seconds Time::currentSysTimeS()
    {
        using namespace std::chrono;
        return duration_cast<seconds>(system_clock::now().time_since_epoch());
    }

    std::chrono::seconds Time::elapsedTimeS()
    {
        using namespace std::chrono;
        return duration_cast<seconds>(currentSysTimeMS() - start_time);
    }

    float Time::msToSec(long ms)
    {
        return ms / 1000.0f;
    }

}