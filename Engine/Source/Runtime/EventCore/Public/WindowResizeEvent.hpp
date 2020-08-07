/**
 * WindowResizedEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_RESIZED_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_RESIZED_EVENT_H_

#include "EventCoreAPI.hpp"

#include "WindowEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered when a window is resized.
     * @details
     */
    class ENGINE_API WindowResizeEvent : public WindowEvent {

        public:

            /**
             * @brief Constructs a new Window Resize Event.
             * 
             * @param window The ID of the affected window.
             * @param width The new width of the window.
             * @param height The new height of the window.
             */
            WindowResizeEvent(Window* window, unsigned int width, unsigned int height)
                : WindowEvent(window), width_(width), height_(height) {}

            /**
             * @brief Get the name of this Event.
             *
             * @return const char* The name of this Event.
             */
            const char* getName() const { return "Window Resize Event"; }
            /**
             * @brief Get the ID of this Event.
             *
             * @return const unsigned int The ID of this Event.
             */
            const unsigned int getId() const { return EVENT_ID; }

            /**
             * @brief Returns the new width.
             * 
             * @return unsigned int The new width.
             */
            inline unsigned int width() const { return width_; }
            
            /**
             * @brief Returns the new height.
             * 
             * @return unsigned int The new height.
             */
            inline unsigned int height() const { return height_; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 1;

        protected:

            /** The new width. */
            unsigned int width_;
            /** The new height. */
            unsigned int height_;

    };

}

#endif