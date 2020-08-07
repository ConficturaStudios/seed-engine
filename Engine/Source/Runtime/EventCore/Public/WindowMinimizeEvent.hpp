/**
 * WindowMinimizeEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_MINIMIZE_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_MINIMIZE_EVENT_H_

#include "EventCoreAPI.hpp"

#include "WindowEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered when a window is minimized.
     * @details
     */
    class ENGINE_API WindowMinimizeEvent : public WindowEvent {

        public:

            /**
             * @brief Constructs a new Window Minimize Event.
             * 
             * @param window The ID of the affected window.
             * @param minimized True if the window has been minimized.
             */
            WindowMinimizeEvent(Window* window, bool minimized)
                : WindowEvent(window), minimized_(minimized) {}

            /**
             * @brief Get the name of this Event.
             *
             * @return const char* The name of this Event.
             */
            const char* getName() const { return "Window Minimze Event"; }
            /**
             * @brief Get the ID of this Event.
             *
             * @return const unsigned int The ID of this Event.
             */
            const unsigned int getId() const { return EVENT_ID; }

            /**
             * @brief Returns true if the window has been minimized.
             * 
             * @return true If the window has been minimized.
             * @return false If the window has not been minimized.
             */
            inline bool minimized() const { return minimized_; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 6;

        protected:

            /** True if the window has been minimized. */
            bool minimized_;

    };

}

#endif