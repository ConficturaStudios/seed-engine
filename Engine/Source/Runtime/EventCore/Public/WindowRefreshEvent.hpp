/**
 * WindowRefreshEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_REFRESH_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_REFRESH_EVENT_H_

#include "EventCoreAPI.hpp"

#include "WindowEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered when a window is refreshed.
     * @details
     */
    class ENGINE_API WindowRefreshEvent : public WindowEvent {

        public:

            /**
             * @brief Constructs a new Window Refresh Event.
             * 
             * @param window The ID of the affected window.
             */
            WindowRefreshEvent(Window* window)
                : WindowEvent(window) {}

            /**
             * @brief Get the name of this Event.
             *
             * @return const char* The name of this Event.
             */
            const char* getName() const { return "Window Refresh Event"; }
            /**
             * @brief Get the ID of this Event.
             *
             * @return const unsigned int The ID of this Event.
             */
            const unsigned int getId() const { return EVENT_ID; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 4;

        protected:

    };

}

#endif