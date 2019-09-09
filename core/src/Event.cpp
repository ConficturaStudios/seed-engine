#include "Event.hpp"

namespace seedengine {

    std::queue<std::shared_ptr<Event>> EventDispatcher::event_buffer;
    std::map<const unsigned int, std::vector<EventDispatcher::EventDeligate>> EventDispatcher::deligate_regtistry;

    void EventDispatcher::registerDeligate(const unsigned int event_id, EventDispatcher::EventDeligate deligate) {

        // Check if event has been registered
        if (deligate_regtistry.find(event_id) == deligate_regtistry.end()) {
            // Register event reference if not found
            std::vector<EventDeligate> deligates;
            deligate_regtistry[event_id] = deligates;
        }
        // Add delegate to binding list
        deligate_regtistry[event_id].push_back(deligate);
    }

    std::shared_ptr<Event> EventDispatcher::pop() {
        auto next_event = event_buffer.front();
        event_buffer.pop();
        return next_event;
    }

    void EventDispatcher::run(unsigned int type_filter) {

        int q_size = (int)event_buffer.size();
        int buffer_count = 0;

        // Iterate through each event in the queue once, passing filtered out events to back of queue
        while (buffer_count < q_size) {
            auto next = pop();
            if (next->isType(static_cast<EventType>(type_filter))) {
                // Iterate through all delegates bound to this event
                for (EventDeligate deligate : deligate_regtistry[next->getId()])
                {
                    // Call the function
                    deligate(*next);
                }
            }
            else {
                // Move event to the back of the buffer
                event_buffer.push(next);
            }
            buffer_count++;
        }
    }

    float MouseEvent::cur_x_ = 0;
    float MouseEvent::cur_y_ = 0;

}