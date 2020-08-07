/**
 * EventDispatcher.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_EVENT_DISPATCHER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_EVENT_DISPATCHER_H_

#include "EventCoreAPI.hpp"

#include <queue>
#include <map>
#include <functional>
#include <memory>

#include "Event.hpp"

namespace seedengine {

    /**
     * @brief An event dispatcher for handling event buffering and the distribution of events to deligates.
     * @details
     */
    class ENGINE_API EventDispatcher final {

        public:

            /** A function deligate that recieves an event. */
            typedef ::std::function<void(Event&)> EventDeligate;

            /**
             * @brief Registers a function delegate to a specific Event ID to bind the actions.
             * 
             * @param event_id The ID of the event to bind to.
             * @param deligate The function to bind to the event.
             */
            static void registerDeligate(const unsigned int event_id, EventDeligate deligate);

            /**
             * @brief Pushs an event into the event queue. This is a non-blocking event.
             *
             * @tparam E The event type to force.
             * @tparam Args The variadic parameter pack used to construct the Event.
             * @tparam typename Conditional compilation based on the base type of E.
             * @param args The arguments used when constructing the Event of type E.
             */
            template <
                class E,
                class... Args,
                typename = typename std::enable_if<std::is_base_of<Event, E>::value>::type
            >
            static void push(Args&&... args) {
                event_buffer.push(std::make_shared<E>(std::forward<Args>(args)...));
            }

            /**
             * @brief Removes and returns the next event in the buffer.
             * 
             * @return std::shared_ptr<Event> The next event in the buffer.
             */
            static std::shared_ptr<Event> pop();

            /**
             * @brief Forces an event to notify its bound functions without adding
             *        it to the queue. This is a blocking event.
             * 
             * @tparam E The event type to force.
             * @tparam Args The variadic parameter pack used to construct the Event.
             * @tparam std::enable_if<std::is_base_of<Event, E>::value>::type Conditional
             *         compilation based on the base type of E.
             * @param args The arguments used when constructing the Event of type E.
             */
            template <
                class E,
                class... Args,
                typename = typename std::enable_if<std::is_base_of<Event, E>::value>::type
            >
            static void force(Args&&... args) {
                auto event_ptr = std::make_shared<E>(std::forward<Args>(args)...);
                // Iterate through all delegates bound to this event
                for (EventDeligate deligate : deligate_regtistry[event_ptr->getId()])
                {
                    // Call the function
                    deligate(*event_ptr);
                }
            }

            /**
             * @brief Runs the deligate functions for every event in the buffer of the specified type.
             *        The events are removed after execution of its deligates.
             * @param type_filter The types that will be run, skipping all others
             */
            static void run(unsigned int type_filter);


        private:

            /** The event buffer queue. */
            static std::queue<std::shared_ptr<Event>> event_buffer;
            /** A mapped registry of all events and their bound functions. */
            static std::map<const unsigned int, std::vector<EventDeligate>> deligate_regtistry;

    };

}

#endif