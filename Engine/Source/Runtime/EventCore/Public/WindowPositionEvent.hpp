/**
 * WindowPositionEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_POSITION_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_POSITION_EVENT_H_

#include "EventCoreAPI.hpp"

#include "WindowEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered when a window is moved.
     * @details
     */
    class ENGINE_API WindowPositionEvent : public WindowEvent {

        public:

            /**
             * @brief Constructs a new Window Position Event.
             * 
             * @param window The ID of the affected window.
             * @param x The new x position of the window.
             * @param y The new y position of the window.
             */
            WindowPositionEvent(Window* window, unsigned int x, unsigned int y)
                : WindowEvent(window), x_(x), y_(y) {}

            /**
             * @brief Get the name of this Event.
             *
             * @return const char* The name of this Event.
             */
            const char* getName() const { return "Window Position Event"; }
            /**
             * @brief Get the ID of this Event.
             *
             * @return const unsigned int The ID of this Event.
             */
            const unsigned int getId() const { return EVENT_ID; }

            /**
             * @brief Returns the new x position.
             * 
             * @return unsigned int The new x position.
             */
            inline unsigned int x() const { return x_; }
            
            /**
             * @brief Returns the new y position.
             * 
             * @return unsigned int The new y position.
             */
            inline unsigned int y() const { return y_; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 2;

        protected:

            /** The new x position. */
            unsigned int x_;
            /** The new y position. */
            unsigned int y_;

    };

}

#endif