#ifndef SEEDENGINE_INCLUDE_TIME_H_
#define SEEDENGINE_INCLUDE_TIME_H_

#include "Core.hpp"

namespace Engine {

    #pragma warning(disable: 4251)
    // Controls time related data for the application.
    class ENGINE_DLL Time {

    // Allow Program::run(int*) to access private members
    friend class Program;

    public:

        // Starts the clock on the program. This should only be called by the Program class.
        static void start();

        // Toggles the game paused setting.
        // @returns: The new paused state.
        static bool togglePause();

        // Returns the game paused setting.
        // @returns: The paused state.
        inline static bool isPaused() { return paused_; }

        // Returns the current delta time.
        // @returns: The current delta time.
        inline static float getDeltaTime() { return delta_time_; }

        // Sets the time scale of the program to the passed value.
        // @param(float) time_scale: The new time scale value.
        // @returns: The previous time scale.
        static float setTimeScale(float);

        // Returns the current time scale.
        // @returns: The current time scale.
        inline static float getTimeScale() { return time_scale_; }

        // Returns the time between updates.
        // @returns: The current update time in milliseconds.
        static float getUpTime();

        // Returns the time of the last update loop.
        // @returns: The time of the last update loop.
        inline static float getLastLoopTime() { return (float)(last_loop_time_.count()); }

        // Returns the current system time in milliseconds.
        // @returns: The current system time in milliseconds.
        static std::chrono::milliseconds currentSysTimeMS();

        // Returns the time since the program began in milliseconds.
        // @returns: The time since the program began in milliseconds.
        static std::chrono::milliseconds elapsedTimeMS();

        // Returns the current system time in seconds.
        // @returns: The current system time in seconds.
        static std::chrono::seconds currentSysTimeS();

        // Returns the time since the program began in seconds.
        // @returns: The time since the program began in seconds.
        static std::chrono::seconds elapsedTimeS();


        // Converts milliseconds into seconds.
        // @param(long) ms: Milliseconds to convert.
        // @returns: The seconds conversion of the passed value.
        static float msToSec(long);

    private:

        // The time between frames in milliseconds.
        static float delta_time_;
        // Is the game paused.
        static bool paused_;

        // The current time scale.
        static float time_scale_;
        // The last active time scale.
        static float last_time_scale_;
        // The start time of the program
        static std::chrono::milliseconds start_time_;
        // The last update loop time value.
        static std::chrono::milliseconds last_loop_time_;

    };
}

#endif