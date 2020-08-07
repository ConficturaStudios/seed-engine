/**
 * Time.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_ENGINE_CORE_TIME_H_
#define SEEDENGINE_INCLUDE_RUNTIME_ENGINE_CORE_TIME_H_

#include "EngineCoreAPI.hpp"

#include <chrono>

namespace seedengine {

    /**
     * @brief Container for time data.
     * @details Controls the flow of time within the active game and stores
     *          the time statistics for the engine.
     */
    class ENGINE_API Time final {

        
        /** Allow Program::run(int*) to access private members */
        friend class Program;

        public:

            /**
             * @brief Toggles the game paused setting.
             * 
             * @return true If the game is now paused.
             * @return false If the game is now unpaused.
             */
            static bool togglePause();

            /**
             * @brief Returns the game paused setting.
             * 
             * @return true If the game is paused.
             * @return false If the game is not paused.
             */
            inline static bool isPaused() { return paused_; }

            /**
             * @brief Returns the current delta time.
             * 
             * @return float The current delta time.
             */
            inline static float getDeltaTime() { return delta_time_; }

            /**
             * @brief Sets the time scale of the program.
             * 
             * @param time_scale The new time scale value.
             * @return float The previous time scale.
             */
            static float setTimeScale(float time_scale);

            /**
             * @brief Returns the current time scale.
             * 
             * @return float The current time scale.
             */
            inline static float getTimeScale() { return time_scale_; }

            /**
             * @brief Returns the time between updates.
             * 
             * @return float The current update time in milliseconds.
             */
            static float getUpTime();

            /**
             * @brief Returns the time of the last update loop.
             * 
             * @return float The time of the last update loop.
             */
            inline static float getLastLoopTime() { return (float)(last_loop_time_.count()); }

            /**
             * @brief Returns the current system time in milliseconds.
             * 
             * @return std::chrono::milliseconds The current system time in milliseconds.
             */
            static std::chrono::milliseconds currentSysTimeMS();

            /**
             * @brief Returns the time since the program began in milliseconds.
             * 
             * @return std::chrono::milliseconds The time since the program began in milliseconds.
             */
            static std::chrono::milliseconds elapsedTimeMS();

            /**
             * @brief Returns the current system time in seconds.
             * 
             * @return std::chrono::seconds The current system time in seconds.
             */
            static std::chrono::seconds currentSysTimeS();

            /**
             * @brief Returns the time since the program began in seconds.
             * 
             * @return std::chrono::seconds The time since the program began in seconds.
             */
            static std::chrono::seconds elapsedTimeS();


            /**
             * @brief Converts milliseconds into seconds.
             * 
             * @param ms Milliseconds to convert.
             * @return float The seconds conversion of the passed value.
             */
            static float msToSec(long ms);

        private:

            /**
             * @brief Starts the clock on the program. This should only be called
             *        by the Program class.
             * 
             * @see #Program
             */
            static void start();

            /** The time between frames in milliseconds. */
            static float delta_time_;
            /** Is the game paused. */
            static bool paused_;

            /** The current time scale. */
            static float time_scale_;
            /** The last active time scale. */
            static float last_time_scale_;
            /** The start time of the program */
            static std::chrono::milliseconds start_time_;
            /** The last update loop time value. */
            static std::chrono::milliseconds last_loop_time_;

    };

}

#endif