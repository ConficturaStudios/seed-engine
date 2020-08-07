/**
 * MouseButtonEvent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_MOUSE_BUTTON_EVENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_EVENT_CORE_MOUSE_BUTTON_EVENT_H_

#include "EventCoreAPI.hpp"

#include "MouseEvent.hpp"

namespace seedengine {

    /**
     * @brief An event triggered by a mouse button.
     * @details
     */
    class ENGINE_API MouseButtonEvent : public MouseEvent {

        public:

            /**
             * @brief Constructs a new Mouse Button Event.
             * 
             * @param button_id The ID of the button affected.
             * @param state The state of the affected button.
             * @param mods Applied modifier flags.
             */
            MouseButtonEvent(unsigned int button_id, input::ButtonState state, unsigned int mods)
                : MouseEvent(cur_x_, cur_y_), button_id_(button_id), state_(state), mods_(mods) {}

            /**
             * @brief Get the name of this Event.
             *
             * @return const char* The name of this Event.
             */
            const char* getName() const { return "Mouse Button Event"; }
            /**
             * @brief Get the ID of this Event.
             *
             * @return const unsigned int The ID of this Event.
             */
            const unsigned int getId() const { return EVENT_ID; }

            /**
             * @brief Returns the ID of the button affected.
             * 
             * @return unsigned int The ID of the button affected.
             */
            inline unsigned int buttonId() const { return button_id_; }
            /**
             * @brief Returns the state of the affected button.
             * 
             * @return input::ButtonState The state of the affected button.
             */
            inline input::ButtonState state() const { return state_; }
            /**
             * @brief Returns the applied modifiers.
             * 
             * @return unsigned int The applied modifiers.
             */
            inline unsigned int mods() const { return mods_; }

            /** The ID number of this event type. */
            static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::MOUSE) << 4) | 1;

        private:

            /** The ID of the button affected. */
            unsigned int button_id_;
            /** The state of the affected button. */
            input::ButtonState state_;
            /** Any shift, ctrl, alt, super modifier flags applied to the key. */
            unsigned int mods_;

    };

}

#endif