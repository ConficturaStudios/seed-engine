/**
 * MouseEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_MOUSE_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_MOUSE_EVENT_H_

#include "EventCoreAPI.hpp"

#include "PeripheralEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered by mouse input.
     * @details
     */
    class ENGINE_API MouseEvent : public PeripheralEvent {

        public:

            /**
             * @brief Constructs a new Mouse Event.
             * 
             * @param x The new x position of the mouse.
             * @param y The new y position of the mouse.
             */
            MouseEvent(float x, float y)
                : PeripheralEvent(), x_(x), y_(y) {
                cur_x_ = x;
                cur_y_ = y;
            }

            /**
             * @brief Get this Event's type.
             *
             * @return EventType The Event type.
             */
            EventType getEventType() const { return EventType::MOUSE; }

            /**
             * @brief Returns the new x position of the mouse.
             * 
             * @return float The new x position of the mouse.
             */
            inline float x() const { return x_; }
            /**
             * @brief Returns the new y position of the mouse.
             * 
             * @return float The new y position of the mouse.
             */
            inline float y() const { return y_; }

        protected:

            /** The new x position of the mouse. */
            float x_;
            /** The new y position of the mouse. */
            float y_;
            /** The current x position of the mouse. */
            static float cur_x_;
            /** The current y position of the mouse. */
            static float cur_y_;

    };

}

#endif