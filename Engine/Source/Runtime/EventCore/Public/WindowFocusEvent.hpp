/**
 * WindowFocusEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_FOCUS_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_FOCUS_EVENT_H_

#include "EventCoreAPI.hpp"

#include "WindowEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered when a window changes focus.
     * @details
     */
    class ENGINE_API WindowFocusEvent : public WindowEvent {

        public:

            /**
             * @brief Constructs a new Window Focus Event.
             * 
             * @param window The ID of the affected window.
             * @param has_focus True if the window has gained focus.
             */
            WindowFocusEvent(Window* window, bool has_focus)
                : WindowEvent(window), has_focus_(has_focus) {}

            /**
             * @brief Get the name of this Event.
             *
             * @return const char* The name of this Event.
             */
            const char* getName() const { return "Window Focus Event"; }
            /**
             * @brief Get the ID of this Event.
             *
             * @return const unsigned int The ID of this Event.
             */
            const unsigned int getId() const { return EVENT_ID; }

            /**
             * @brief Returns true if the window has focus.
             * 
             * @return true If the window has focus.
             * @return false If the window does not have focus.
             */
            inline bool hasFocus() const { return has_focus_; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 5;

        protected:

            /** True if the window has focus. */
            bool has_focus_;

    };

}

#endif