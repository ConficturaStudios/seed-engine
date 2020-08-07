/**
 * EngineEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_ENGINE_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_ENGINE_EVENT_H_

#include "EventCoreAPI.hpp"

#include "Event.hpp"

namespace seedengine {

    /**
     * @brief An event triggered by the engine itself.
     * @details
     */
    class ENGINE_API EngineEvent : public Event {

        public:

            /** Constructs a new Engine Event. */
            EngineEvent() : Event() {}

            /**
             * @brief Get this Event's type.
             *
             * @return EventType The Event type.
             */
            EventType getEventType() const { return EventType::ENGINE; }

        protected:

    };

}

#endif