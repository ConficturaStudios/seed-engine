/**
 * WindowEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_EVENT_H_

#include "EventCoreAPI.hpp"

#include "Event.hpp"

namespace seedengine {

    class Window; // Forward declare Window class

    /**
     * @brief An event triggered by the application window.
     * @details
     */
    class ENGINE_API WindowEvent : public Event {

        friend class Window;

        public:

            /**
             * @brief Constructs a new Window Event.
             * 
             * @param window A pointer to the affected window.
             */
            WindowEvent(Window* window)
                : Event(), window_(window) {}

            /**
             * @brief Get this Event's type.
             *
             * @return EventType The Event type.
             */
            EventType getEventType() const { return EventType::WINDOW; }

            /**
             * @brief Returns a pointer to the affected window.
             * 
             * @return Window* A pointer to the affected window.
             */
            inline Window* window() const { return window_; }

        protected:

            /** The affected window */
            Window* window_;

    };

}

#endif