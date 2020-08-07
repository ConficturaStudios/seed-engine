/**
 * EnginePreRenderEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_ENGINE_PRE_RENDER_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_ENGINE_PRE_RENDER_EVENT_H_

#include "EventCoreAPI.hpp"

#include "EngineEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered before rendering a frame.
     * @details
     */
    class ENGINE_API EnginePreRenderEvent : public EngineEvent {

        public:

            /** Constructs a new Engine Pre-Render Event. */
            EnginePreRenderEvent()
                : EngineEvent() {}

            /**
             * @brief Get the name of this Event.
             *
             * @return const char* The name of this Event.
             */
            const char* getName() const { return "Engine Pre-Render Event"; }
            /**
             * @brief Get the ID of this Event.
             *
             * @return const unsigned int The ID of this Event.
             */
            const unsigned int getId() const { return EVENT_ID; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::ENGINE) << 4) | 2;

        protected:

    };

}

#endif