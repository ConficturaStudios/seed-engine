#include "Event.hpp"

namespace Engine {
    namespace Event {

        std::queue<Event*> EventDispatcher::event_buffer;
        std::map<const unsigned int, std::vector<std::function<bool(Event*)>>> EventDispatcher::deligate_regtistry;

        void EventDispatcher::registerDeligate(const unsigned int event_id, std::function<bool(Event*)> deligate) {

            // Check if event has been registered
            if (EventDispatcher::deligate_regtistry.find(event_id) == EventDispatcher::deligate_regtistry.end()) {
                // Register event reference if not found
                std::vector<std::function<bool(Event*)>> deligates;
                EventDispatcher::deligate_regtistry[event_id] = deligates;
            }
            // Add delegate to binding list
            EventDispatcher::deligate_regtistry[event_id].push_back(deligate);
        }

        void EventDispatcher::push(Event* event_ref) {
            EventDispatcher::event_buffer.push(event_ref);
        }

        Event* EventDispatcher::pop() {
            Event* next_event = EventDispatcher::event_buffer.front();
            EventDispatcher::event_buffer.pop();
            return next_event;
        }

        void EventDispatcher::run(unsigned int type_filter) {

            int q_size = EventDispatcher::event_buffer.size();
            int buffer_count = 0;

            // Iterate through each event in the queue once, passing filtered out events to back of queue
            while (buffer_count < q_size) {
                Event* next = EventDispatcher::pop();
                if (next->isType(static_cast<EventType>(type_filter))) {
                    // Iterate through all delegates bound to this event
                    for each (std::function<bool(Event*)> deligate in EventDispatcher::deligate_regtistry[next->getId()])
                    {
                        // Call the function
                        deligate(next);
                    }
                }
                else {
                    // Move event to the back of the buffer
                    EventDispatcher::event_buffer.push(next);
                }
                buffer_count++;
            }
        }

        float MouseEvent::cur_x_ = 0;
        float MouseEvent::cur_y_ = 0;

    }
}