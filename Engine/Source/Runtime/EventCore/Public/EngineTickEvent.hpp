/**
 * EngineTickEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_ENGINE_TICK_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_ENGINE_TICK_EVENT_H_

#include "EventCoreAPI.hpp"

#include "EngineEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered by an engine logic tick.
     * @details
     */
    class ENGINE_API EngineTickEvent : public EngineEvent {

        public:

            /**
             * @brief Construct a new Engine Tick Event.
             * 
             * @param delta_time The delta time of the application.
             */
            EngineTickEvent(float delta_time)
                : EngineEvent(), delta_time_(delta_time) {}

            /**
             * @brief Get the name of this Event.
             *
             * @return const char* The name of this Event.
             */
            const char* getName() const { return "Engine Tick Event"; }
            /**
             * @brief Get the ID of this Event.
             *
             * @return const unsigned int The ID of this Event.
             */
            const unsigned int getId() const { return EVENT_ID; }

            /**
             * @brief Returns the delta time during this event.
             * 
             * @return float The delta time when this event occured.
             */
            inline float deltaTime() const { return delta_time_; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::ENGINE) << 4);

        protected:

            /** The delta time when this event occured. */
            float delta_time_;

    };

}

#endif