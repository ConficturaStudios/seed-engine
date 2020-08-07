/**
 * KeyboardEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_KEYBOARD_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_KEYBOARD_EVENT_H_

#include "EventCoreAPI.hpp"

#include "PeripheralEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered by a keyboard action.
     * @details
     */
    class ENGINE_API KeyboardEvent : public PeripheralEvent {

        public:

            /**
             * @brief Constructs a new Keyboard Event.
             * 
             * @param keycode The keycode of the affected key.
             * @param repeat The repeat count.
             * @param state The state of the affected key.
             * @param mods Applied modifier flags.
             */
            KeyboardEvent(unsigned int keycode, unsigned int repeat, input::ButtonState state, unsigned int mods)
                : PeripheralEvent(), keycode_(keycode), repeat_(repeat), state_(state), mods_(mods) {}


            /**
             * @brief Get this Event's type.
             *
             * @return EventType The Event type.
             */
            EventType getEventType() const { return EventType::KEYBOARD; }
            /**
             * @brief Get the name of this Event.
             *
             * @return const char* The name of this Event.
             */
            const char* getName() const { return "Keyboard Event"; }
            /**
             * @brief Get the ID of this Event.
             *
             * @return const unsigned int The ID of this Event.
             */
            const unsigned int getId() const { return EVENT_ID; }

            /**
             * @brief Returns the keycode of the affected key.
             * 
             * @return unsigned int The keycode of the affected key.
             */
            inline unsigned int keycode() const { return keycode_; }
            /**
             * @brief Returns the repeat count.
             * 
             * @return unsigned int The repeat count.
             */
            inline unsigned int repeat() const { return repeat_; }
            /**
             * @brief Returns the state of the affected key.
             * 
             * @return input::ButtonState The state of the affected key.
             */
            inline input::ButtonState state() const { return state_; }
            /**
             * @brief Returns the applied modifiers.
             * 
             * @return unsigned int The applied modifiers.
             */
            inline unsigned int mods() const { return mods_; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::KEYBOARD) << 4);

        private:

            /** The keycode of the affected key. */
            unsigned int keycode_;
            /** The repeat count. */
            unsigned int repeat_;
            /** The state of the affected key. */
            input::ButtonState state_;
            /** Any shift, ctrl, alt, super modifier flags applied to the key. */
            unsigned int mods_;

    };

}

#endif