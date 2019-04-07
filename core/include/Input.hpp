#ifndef SEEDENGINE_INCLUDE_INPUT_H_
#define SEEDENGINE_INCLUDE_INPUT_H_

#include "Core.hpp"

namespace Engine {
    namespace Input {

        enum class Key : unsigned int {

        };

        enum class MouseButton : unsigned int {
            LEFT         = 0,
            RIGHT        = 1,
            MIDDLE       = 2,
            ACTION_0     = 3,
            ACTION_1     = 4,
            ACTION_2     = 5,
            ACTION_3     = 6,
            ACTION_4     = 7,
            ACTION_5     = 8,
            ACTION_6     = 9,
            ACTION_7     = 10,
            ACTION_8     = 11,
            ACTION_9     = 12,
            ACTION_10    = 13
        };

        enum class ControllerButton : unsigned int {
            SYSTEM       = 0,
            HOME         = 1,
            OPTION       = 2,

            ACTION_0     = 3,
            ACTION_1     = 4,
            ACTION_2     = 5,
            ACTION_3     = 6,

            DPAD_UP      = 7,
            DPAD_LEFT    = 8,
            DPAD_DOWN    = 9,
            DPAD_RIGHT   = 10,

            BUMPER_R     = 11,
            TRIGGER_R    = 12,
            BUMPER_L     = 13,
            TRIGGER_L    = 14,

            JOYSTICK_R   = 15,
            JOYSTICK_L   = 16,

            SPECIAL_0    = 17,
            SPECIAL_1    = 18,
            SPECIAL_2    = 19,
            SPECIAL_3    = 20
        };

        enum class ControllerAxis : unsigned int {
            L_AXIS_X     = 0,
            L_AXIS_Y     = 1,

            R_AXIS_X     = 2,
            R_AXIS_Y     = 3,

            SPECIAL_X    = 4,
            SPECIAL_Y    = 5
        };

        enum class XBoxButton : unsigned int {
            XBOX         = static_cast<unsigned int>(ControllerButton::SYSTEM),
            MENU         = static_cast<unsigned int>(ControllerButton::HOME),
            VIEW         = static_cast<unsigned int>(ControllerButton::OPTION),

            A_BUTTON     = static_cast<unsigned int>(ControllerButton::ACTION_0),
            B_BUTTON     = static_cast<unsigned int>(ControllerButton::ACTION_1),
            X_BUTTON     = static_cast<unsigned int>(ControllerButton::ACTION_2),
            Y_BUTTON     = static_cast<unsigned int>(ControllerButton::ACTION_3),

            DPAD_UP      = static_cast<unsigned int>(ControllerButton::DPAD_UP),
            DPAD_LEFT    = static_cast<unsigned int>(ControllerButton::DPAD_LEFT),
            DPAD_DOWN    = static_cast<unsigned int>(ControllerButton::DPAD_DOWN),
            DPAD_RIGHT   = static_cast<unsigned int>(ControllerButton::DPAD_RIGHT),

            BUMPER_R     = static_cast<unsigned int>(ControllerButton::BUMPER_R),
            TRIGGER_R    = static_cast<unsigned int>(ControllerButton::TRIGGER_R),
            BUMPER_L     = static_cast<unsigned int>(ControllerButton::BUMPER_L),
            TRIGGER_L    = static_cast<unsigned int>(ControllerButton::TRIGGER_L),

            JOYSTICK_R   = static_cast<unsigned int>(ControllerButton::JOYSTICK_R),
            JOYSTICK_L   = static_cast<unsigned int>(ControllerButton::JOYSTICK_L)
        };

        enum class XBoxAxis : unsigned int {
            L_STICK_X    = static_cast<unsigned int>(ControllerAxis::L_AXIS_X),
            L_STICK_Y    = static_cast<unsigned int>(ControllerAxis::L_AXIS_Y),

            R_STICK_X    = static_cast<unsigned int>(ControllerAxis::R_AXIS_X),
            R_STICK_Y    = static_cast<unsigned int>(ControllerAxis::R_AXIS_Y)
        };

        enum class PS4Button : unsigned int {
            PLAYSTATION      = static_cast<unsigned int>(ControllerButton::SYSTEM),
            OPTIONS          = static_cast<unsigned int>(ControllerButton::HOME),
            SHARE            = static_cast<unsigned int>(ControllerButton::OPTION),

            X_BUTTON         = static_cast<unsigned int>(ControllerButton::ACTION_0),
            O_BUTTON         = static_cast<unsigned int>(ControllerButton::ACTION_1),
            SQUARE_BUTTON    = static_cast<unsigned int>(ControllerButton::ACTION_2),
            TRIANGLE_BUTTON  = static_cast<unsigned int>(ControllerButton::ACTION_3),

            DPAD_UP          = static_cast<unsigned int>(ControllerButton::DPAD_UP),
            DPAD_LEFT        = static_cast<unsigned int>(ControllerButton::DPAD_LEFT),
            DPAD_DOWN        = static_cast<unsigned int>(ControllerButton::DPAD_DOWN),
            DPAD_RIGHT       = static_cast<unsigned int>(ControllerButton::DPAD_RIGHT),

            R1               = static_cast<unsigned int>(ControllerButton::BUMPER_R),
            R2               = static_cast<unsigned int>(ControllerButton::TRIGGER_R),
            L1               = static_cast<unsigned int>(ControllerButton::BUMPER_L),
            L2               = static_cast<unsigned int>(ControllerButton::TRIGGER_L),

            R3               = static_cast<unsigned int>(ControllerButton::JOYSTICK_R),
            L3               = static_cast<unsigned int>(ControllerButton::JOYSTICK_L),

            TOUCH_PAD        = static_cast<unsigned int>(ControllerButton::SPECIAL_0)
        };

        enum class PS4Axis : unsigned int {
            L_STICK_X        = static_cast<unsigned int>(ControllerAxis::L_AXIS_X),
            L_STICK_Y        = static_cast<unsigned int>(ControllerAxis::L_AXIS_Y),

            R_STICK_X        = static_cast<unsigned int>(ControllerAxis::R_AXIS_X),
            R_STICK_Y        = static_cast<unsigned int>(ControllerAxis::R_AXIS_Y),

            TOUCH_PAD_X      = static_cast<unsigned int>(ControllerAxis::SPECIAL_X),
            TOUCH_PAD_Y      = static_cast<unsigned int>(ControllerAxis::SPECIAL_Y)
        };

    }
}

#endif