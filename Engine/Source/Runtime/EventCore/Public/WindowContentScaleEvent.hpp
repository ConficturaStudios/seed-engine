/**
 * WindowContentScaleEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_CONTENT_SCALE_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_WINDOW_CONTENT_SCALE_EVENT_H_

#include "EventCoreAPI.hpp"

#include "WindowEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered when a window has its content scaled.
     * @details
     */
    class ENGINE_API WindowConentScaleEvent : public WindowEvent {

        public:

            /**
             * @brief Constructs a new Window Conent Scale Event.
             * 
             * @param window The ID of the affected window.
             * @param x_scale The new x content scale of the window.
             * @param y_scale The new y content scale of the window.
             */
            WindowConentScaleEvent(Window* window, float x_scale, float y_scale)
                : WindowEvent(window), x_scale_(x_scale), y_scale_(y_scale) {}

            /**
             * @brief Get the name of this Event.
             *
             * @return const char* The name of this Event.
             */
            const char* getName() const { return "Window Content Scale Event"; }
            /**
             * @brief Get the ID of this Event.
             *
             * @return const unsigned int The ID of this Event.
             */
            const unsigned int getId() const { return EVENT_ID; }

            /**
             * @brief Returns the new x content scale.
             * 
             * @return float The new x content scale.
             */
            inline float x_scale() const { return x_scale_; }
            /**
             * @brief Returns the new y content scale.
             * 
             * @return float The new y content scale.
             */
            inline float y_scale() const { return y_scale_; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 9;

        protected:

            /** The new x content scale. */
            float x_scale_;
            /** The new y content scale. */
            float y_scale_;

    };

}

#endif