/**
 * ControllerEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_CONTROLLER_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_CONTROLLER_EVENT_H_

#include "EventCoreAPI.hpp"

#include "PeripheralEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered by a controller action.
     * @details
     */
    class ENGINE_API ControllerEvent : public PeripheralEvent {

        public:

            /**
             * @brief Constructs a new Controller Event.
             * 
             * @param controller_id The ID of the affected controller.
             */
            ControllerEvent(unsigned int controller_id)
                : PeripheralEvent(), controller_id_(controller_id) {}


            /**
             * @brief Get this Event's type.
             *
             * @return EventType The Event type.
             */
            EventType getEventType() const { return EventType::CONTROLLER; }

            /**
             * @brief Returns the ID of the affected controller.
             * 
             * @return unsigned int The ID of the affected controller.
             */
            inline unsigned int controllerId() const { return controller_id_; }

        protected:

            /** The ID of the affected controller. */
            unsigned int controller_id_;

    };

}

#endif