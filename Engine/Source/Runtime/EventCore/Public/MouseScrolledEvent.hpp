/**
 * MouseScrolledEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_MOUSE_SCROLLED_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_MOUSE_SCROLLED_EVENT_H_

#include "EventCoreAPI.hpp"

#include "MouseEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered by mouse movement.
     * @details
     */
    class ENGINE_API MouseScrolledEvent : public MouseEvent {

        public:

            /**
             * @brief Constructs a new Mouse Scrolled Event.
             * 
             * @param x_offset The amount to scroll in the x direction.
             * @param y_offset The amount to scroll in the y direction.
             */
            MouseScrolledEvent(float x_offset, float y_offset)
                : MouseEvent(cur_x_, cur_y_), x_offset_(x_offset), y_offset_(y_offset) {}

            /**
             * @brief Get the name of this Event.
             *
             * @return const char* The name of this Event.
             */
            const char* getName() const { return "Mouse Moved Event"; }
            /**
             * @brief Get the ID of this Event.
             *
             * @return const unsigned int The ID of this Event.
             */
            const unsigned int getId() const { return EVENT_ID; }

            /**
             * @brief Returns the amount to scroll in the x direction.
             * 
             * @return float The amount to scroll in the x direction.
             */
            inline float x_offset() const { return x_offset_; }
            /**
             * @brief Returns the amount to scroll in the y direction.
             * 
             * @return float The amount to scroll in the y direction.
             */
            inline float y_offset() const { return y_offset_; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::MOUSE) << 4) | 2;

        private:

            /** The amount to scroll in the x direction. */
            float x_offset_;
            /** The amount to scroll in the y direction. */
            float y_offset_;

    };

}

#endif