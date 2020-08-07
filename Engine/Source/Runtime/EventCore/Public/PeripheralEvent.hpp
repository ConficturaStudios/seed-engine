/**
 * PeripheralEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_PERIPHERAL_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_PERIPHERAL_EVENT_H_

#include "EventCoreAPI.hpp"

#include "Event.hpp"

namespace seedengine {

    /**
     * @brief An event triggered by peripheral hardware.
     * @details
     */
    class ENGINE_API PeripheralEvent : public Event {

        public:

            /** Constructs a new Peripheral Hardware Event. */
            PeripheralEvent() : Event() {}

            /**
             * @brief Get this Event's type.
             *
             * @return EventType The Event type.
             */
            EventType getEventType() const { return EventType::PERIPHERAL; }

        protected:

    };

}

#endif