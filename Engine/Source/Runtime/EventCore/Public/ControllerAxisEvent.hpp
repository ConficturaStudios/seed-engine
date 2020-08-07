/**
 * ControllerAxisEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_CONTROLLER_AXIS_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_CONTROLLER_AXIS_EVENT_H_

#include "EventCoreAPI.hpp"

#include "ControllerEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered by a controller axis change, such as moving a joystick.
     * @details
     */
    class ENGINE_API ControllerAxisEvent : public ControllerEvent {

        public:

            /**
             * @brief Constructs a new Controller Axis Event.
             * 
             * @param controller_id The ID of the affected controller.
             * @param axis_id The ID of the affected axis.
             * @param x The x input of the axis.
             * @param y The y input of the axis.
             */
            ControllerAxisEvent(unsigned int controller_id, unsigned int axis_id, float x, float y)
                : ControllerEvent(controller_id), axis_id_(axis_id), x_(x), y_(y) {}

            /**
             * @brief Get the name of this Event.
             *
             * @return const char* The name of this Event.
             */
            const char* getName() const { return "Controller Axis Event"; }
            /**
             * @brief Get the ID of this Event.
             *
             * @return const unsigned int The ID of this Event.
             */
            const unsigned int getId() const { return EVENT_ID; }

            /**
             * @brief Returns the ID of the affected axis.
             * 
             * @return unsigned int The ID of the affected axis.
             */
            inline unsigned int axisId() const { return axis_id_; }
            /**
             * @brief Returns the x input of the axis.
             * 
             * @return float The x input of the axis.
             */
            inline float x() const { return x_; }
            /**
             * @brief Returns the y input of the axis.
             * 
             * @return float The y input of the axis.
             */
            inline float y() const { return y_; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::CONTROLLER) << 4) | 1;

        private:

            /** The ID of the affected axis. */
            unsigned int axis_id_;
            /** The x input of the axis. */
            float x_;
            /** The y input of the axis. */
            float y_;

    };

}

#endif