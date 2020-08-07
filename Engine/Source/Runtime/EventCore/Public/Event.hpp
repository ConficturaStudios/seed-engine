/**
 * Event.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_EVENT_H_

#include "EventCoreAPI.hpp"

namespace seedengine {

    /** The type classification assigned to an event. */
    enum class ENGINE_API EventType : uint32_t {
        /** A generic event. */
        EVENT         = 0,
        /** A system event generated from outside of the program. */
        SYSTEM        = 1 << 0,
        /** An event generated by client code such as an editor or game. */
        CLIENT        = 1 << 1,
        /** An event generated within the engine itself. */
        ENGINE        = 1 << 2,
        /** An event generated by a window under the control of the engine. */
        WINDOW        = 1 << 3,
        /** An event generated by a hardware peripheral such as a mouse or keyboard. */
        PERIPHERAL    = 1 << 4,
        /** An event generated by a mouse. This is a type of peripheral event. */
        MOUSE         = PERIPHERAL | (PERIPHERAL << 1),
        /** An event generated by a keyboard. This is a type of peripheral event. */
        KEYBOARD      = PERIPHERAL | (PERIPHERAL << 2),
        /** An event generated by a controller. This is a type of peripheral event. */
        CONTROLLER    = PERIPHERAL | (PERIPHERAL << 3)
    };

    /**
     * @brief An event to be processed by the program.
     * @details
     */
    class ENGINE_API Event {

        friend class EventDispatcher;

        public:

            /** Constructs a new Event object */
            Event() {}
            /** Destroy the Event object */
            virtual ~Event() {}

            /**
             * @brief Get this Event's type.
             * 
             * @return EventType The Event type.
             */
            virtual EventType getEventType() const = 0;
            /**
             * @brief Get the name of this Event.
             * 
             * @return const char* The name of this Event.
             */
            virtual const char* getName() const = 0;
            /**
             * @brief Get the ID of this Event.
             * 
             * @return const unsigned int The ID of this Event.
             */
            virtual const unsigned int getId() const = 0;

            /**
             * @brief Checks if this Event is of a specific type.
             * 
             * @param type The type to check against.
             * @return true If this Event is the specified type.
             * @return false If this Event is not the specified type.
             */
            inline bool isType(EventType type) const {
                unsigned int uint_type = static_cast<unsigned int>(type);
                return ((static_cast<unsigned int>(getEventType()) & uint_type) == uint_type);
            }

        protected:

            /** Has this event been handled? */
            bool handled = false;

    };

}

#endif