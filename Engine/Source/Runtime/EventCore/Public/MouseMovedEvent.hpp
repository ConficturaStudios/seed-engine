/**
 * MouseMovedEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_MOUSE_MOVED_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_MOUSE_MOVED_EVENT_H_

#include "EventCoreAPI.hpp"

#include "MouseEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered by mouse movement.
     * @details
     */
    class ENGINE_API MouseMovedEvent : public MouseEvent {

        public:

            /**
             * @brief Constructs a new Mouse Moved Event.
             * 
             * @param x The new x position of the mouse.
             * @param y The new y position of the mouse.
             */
            MouseMovedEvent(float x, float y)
                : MouseEvent(x, y) {
                dx_ = x - cur_x_;
                dy_ = y - cur_y_;
            }

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
             * @brief Returns the change in the x position of the mouse.
             * 
             * @return float The change in the x position of the mouse.
             */
            inline float dx() const { return dx_; }
            /**
             * @brief Returns the change in the y position of the mouse.
             * 
             * @return float The change in the y position of the mouse.
             */
            inline float dy() const { return dy_; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::MOUSE) << 4);

        private:

            /** The change in the x position of the mouse. */
            float dx_;
            /** The change in the y position of the mouse. */
            float dy_;

    };

}

#endif