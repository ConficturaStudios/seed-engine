#include "Event.hpp"

namespace seedengine {

    //TODO: Clean up memory leaks with smart pointers

    std::queue<Event*> EventDispatcher::event_buffer;
    std::map<const unsigned int, std::vector<std::function<void(Event&)>>> EventDispatcher::deligate_regtistry;

    void EventDispatcher::registerDeligate(const unsigned int event_id, std::function<void(Event&)> deligate) {

        // Check if event has been registered
        if (deligate_regtistry.find(event_id) == deligate_regtistry.end()) {
            // Register event reference if not found
            std::vector<std::function<void(Event&)>> deligates;
            deligate_regtistry[event_id] = deligates;
        }
        // Add delegate to binding list
        deligate_regtistry[event_id].push_back(deligate);
    }

    void EventDispatcher::push(Event* event_ptr) {
        event_buffer.push(event_ptr);
    }

    Event* EventDispatcher::pop() {
        Event* next_event = event_buffer.front();
        event_buffer.pop();
        return next_event;
    }

    void EventDispatcher::force(Event* event_ptr) {
        // Iterate through all delegates bound to this event
        for each (std::function<void(Event&)> deligate in deligate_regtistry[event_ptr->getId()])
        {
            // Call the function
            deligate(*event_ptr);
        }
    }

    void EventDispatcher::run(unsigned int type_filter) {

        int q_size = event_buffer.size();
        int buffer_count = 0;

        // Iterate through each event in the queue once, passing filtered out events to back of queue
        while (buffer_count < q_size) {
            Event* next = pop();
            if (next->isType(static_cast<EventType>(type_filter))) {
                // Iterate through all delegates bound to this event
                for each (std::function<void(Event&)> deligate in deligate_regtistry[next->getId()])
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
            delete next;
        }
    }

    float MouseEvent::cur_x_ = 0;
    float MouseEvent::cur_y_ = 0;

}