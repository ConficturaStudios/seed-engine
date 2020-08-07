/**
 * InputType.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_INPUT_INPUT_TYPE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_INPUT_INPUT_TYPE_H_

#include "InputAPI.hpp"

#include <cstdint>

namespace seedengine {

    namespace input {

        /** The state of a given button or key. */
        enum class ENGINE_API ButtonState : uint8_t {
            /** The button was released. */
            RELEASED  = 0,
            /** The button was pressed. */
            PRESSED   = 1,
            /** The button was held until repeated. */
            REPEAT    = 2
        };

        /** All US keyboard keycodes, based on GLFW definitions https://www.glfw.org/docs/latest/group__keys.html */
        enum class ENGINE_API Key : uint32_t {
            /** Unknown */
            UNKNOWN = 0,
            /** Space */
            SPACE = 32,
            /** Apostrophe ( ' ) */
            APOSTROPHE = 39,
            /** Comma ( , ) */
            COMMA = 44,
            /** Minus ( - ) */
            MINUS = 45,
            /** Period ( . ) */
            PERIOD = 46,
            /** Forward Slash ( / ) */
            FORWARD_SLASH = 47,
            /** Keyboard 0 */
            KB_0 = 48,
            /** Keyboard 1 */
            KB_1 = 49,
            /** Keyboard 2 */
            KB_2 = 50,
            /** Keyboard 3 */
            KB_3 = 51,
            /** Keyboard 4 */
            KB_4 = 52,
            /** Keyboard 5 */
            KB_5 = 53,
            /** Keyboard 6 */
            KB_6 = 54,
            /** Keyboard 7 */
            KB_7 = 55,
            /** Keyboard 8 */
            KB_8 = 56,
            /** Keyboard 9 */
            KB_9 = 57,
            /** Semicolon ( ; ) */
            SEMICOLON = 59,
            /** Equal ( = ) */
            EQUAL = 61,
            /** A */
            A = 65,
            /** B */
            B = 66,
            /** C */
            C = 67,
            /** D */
            D = 68,
            /** E */
            E = 69,
            /** F */
            F = 70,
            /** G */
            G = 71,
            /** H */
            H = 72,
            /** I */
            I = 73,
            /** J */
            J = 74,
            /** K */
            K = 75,
            /** L */
            L = 76,
            /** M */
            M = 77,
            /** N */
            N = 78,
            /** O */
            O = 79,
            /** P */
            P = 80,
            /** Q */
            Q = 81,
            /** R */
            R = 82,
            /** S */
            S = 83,
            /** T */
            T = 84,
            /** U */
            U = 85,
            /** V */
            V = 86,
            /** W */
            W = 87,
            /** X */
            X = 88,
            /** Y */
            Y = 89,
            /** Z */
            Z = 90,
            /** Left Bracket ( [ ) */
            LEFT_BRACKET = 91,
            /** Backslash ( \ ) */
            BACKSLASH = 92,
            /** Right Bracket ( ] ) */
            RIGHT_BRACKET = 93,
            /** Grave Accent ( ` ) */
            GRAVE_ACCENT = 96,
            /** World 1 (non-US #1) */
            WORLD_1 = 161,
            /** World 2 (non-US #2) */
            WORLD_2 = 162,
            /** Escape */
            ESCAPE = 256,
            /** Enter */
            ENTER = 257,
            /** Tab */
            TAB = 258,
            /** Backspace */
            BACKSPACE = 259,
            /** Insert */
            INS = 260,
            /** Delete */
            DEL = 261,
            /** Right */
            RIGHT = 262,
            /** Left */
            LEFT = 263,
            /** Down */
            DOWN = 264,
            /** Up */
            UP = 265,
            /** Page Up */
            PAGE_UP = 266,
            /** Page Down */
            PAGE_DOWN = 267,
            /** Home */
            HOME = 268,
            /** End */
            END = 269,
            /** Caps Lock */
            CAPS_LOCK = 280,
            /** Scroll Lock */
            SCROLL_LOCK = 281,
            /** Num Lock */
            NUM_LOCK = 282,
            /** Print Screen */
            PRINT_SCREEN = 283,
            /** Pause */
            PAUSE = 284,
            /** F1 */
            F1 = 290,
            /** F2 */
            F2 = 291,
            /** F3 */
            F3 = 292,
            /** F4 */
            F4 = 293,
            /** F5 */
            F5 = 294,
            /** F6 */
            F6 = 295,
            /** F7 */
            F7 = 296,
            /** F8 */
            F8 = 297,
            /** F9 */
            F9 = 298,
            /** F10 */
            F10 = 299,
            /** F11 */
            F11 = 300,
            /** F12 */
            F12 = 301,
            /** F13 */
            F13 = 302,
            /** F14 */
            F14 = 303,
            /** F15 */
            F15 = 304,
            /** F16 */
            F16 = 305,
            /** F17 */
            F17 = 306,
            /** F18 */
            F18 = 307,
            /** F19 */
            F19 = 308,
            /** F20 */
            F20 = 309,
            /** F21 */
            F21 = 310,
            /** F22 */
            F22 = 311,
            /** F23 */
            F23 = 312,
            /** F24 */
            F24 = 313,
            /** F25 */
            F25 = 314,
            /** Numberpad 0 */
            NP_0 = 320,
            /** Numberpad 1 */
            NP_1 = 321,
            /** Numberpad 2 */
            NP_2 = 322,
            /** Numberpad 3 */
            NP_3 = 323,
            /** Numberpad 4 */
            NP_4 = 324,
            /** Numberpad 5 */
            NP_5 = 325,
            /** Numberpad 6 */
            NP_6 = 326,
            /** Numberpad 7 */
            NP_7 = 327,
            /** Numberpad 8 */
            NP_8 = 328,
            /** Numberpad 9 */
            NP_9 = 329,
            /** Numberpad Decimal */
            NP_DECIMAL = 330,
            /** Numberpad Divide */
            NP_DIVIDE = 331,
            /** Numberpad Multiply */
            NP_MULTIPLY = 332,
            /** Numberpad Subtract */
            NP_SUBTRACT = 333,
            /** Numberpad Add */
            NP_ADD = 334,
            /** Numberpad Enter */
            NP_ENTER = 335,
            /** Numberpad Equal */
            NP_EQUAL = 336,
            /** Left Shift */
            LEFT_SHIFT = 340,
            /** Left Control */
            LEFT_CONTROL = 341,
            /** Left Alt */
            LEFT_ALT = 342,
            /** Left Windows/CMD */
            LEFT_SUPER = 343,
            /** Right Shift */
            RIGHT_SHIFT = 344,
            /** Right Control */
            RIGHT_CONTROL = 345,
            /** Right Alt */
            RIGHT_ALT = 346,
            /** Right Windows/CMD */
            RIGHT_SUPER = 347,
            /** Menu */
            MENU = 348,
            /** Last */
            LAST = 348
        };

        /** Keyboard modifier buttons. */
        enum class ENGINE_API KeyMod : uint8_t {
            SHIFT = 1,
            CTRL = 2,
            ALT = 4,
            SUPER = 8
        };

        /** Mouse button code bindings. */
        enum class ENGINE_API MouseButton : uint8_t {
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

        /** Controller button code bindings. */
        enum class ENGINE_API ControllerButton : uint8_t {
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

        /** Controller axis code bindings. */
        enum class ENGINE_API ControllerAxis : uint8_t {
            L_AXIS_X     = 0,
            L_AXIS_Y     = 1,

            R_AXIS_X     = 2,
            R_AXIS_Y     = 3,

            SPECIAL_X    = 4,
            SPECIAL_Y    = 5
        };

        /** XBox button code bindings. */
        enum class ENGINE_API XBoxButton : uint8_t {
            XBOX         = static_cast<uint8_t>(ControllerButton::SYSTEM),
            MENU         = static_cast<uint8_t>(ControllerButton::HOME),
            VIEW         = static_cast<uint8_t>(ControllerButton::OPTION),

            A_BUTTON     = static_cast<uint8_t>(ControllerButton::ACTION_0),
            B_BUTTON     = static_cast<uint8_t>(ControllerButton::ACTION_1),
            X_BUTTON     = static_cast<uint8_t>(ControllerButton::ACTION_2),
            Y_BUTTON     = static_cast<uint8_t>(ControllerButton::ACTION_3),

            DPAD_UP      = static_cast<uint8_t>(ControllerButton::DPAD_UP),
            DPAD_LEFT    = static_cast<uint8_t>(ControllerButton::DPAD_LEFT),
            DPAD_DOWN    = static_cast<uint8_t>(ControllerButton::DPAD_DOWN),
            DPAD_RIGHT   = static_cast<uint8_t>(ControllerButton::DPAD_RIGHT),

            BUMPER_R     = static_cast<uint8_t>(ControllerButton::BUMPER_R),
            TRIGGER_R    = static_cast<uint8_t>(ControllerButton::TRIGGER_R),
            BUMPER_L     = static_cast<uint8_t>(ControllerButton::BUMPER_L),
            TRIGGER_L    = static_cast<uint8_t>(ControllerButton::TRIGGER_L),

            JOYSTICK_R   = static_cast<uint8_t>(ControllerButton::JOYSTICK_R),
            JOYSTICK_L   = static_cast<uint8_t>(ControllerButton::JOYSTICK_L)
        };

        /** XBox axis code bindings. */
        enum class ENGINE_API XBoxAxis : uint8_t {
            L_STICK_X    = static_cast<uint8_t>(ControllerAxis::L_AXIS_X),
            L_STICK_Y    = static_cast<uint8_t>(ControllerAxis::L_AXIS_Y),

            R_STICK_X    = static_cast<uint8_t>(ControllerAxis::R_AXIS_X),
            R_STICK_Y    = static_cast<uint8_t>(ControllerAxis::R_AXIS_Y)
        };

        /** PS4 button code bindings. */
        enum class ENGINE_API PS4Button : uint8_t {
            PLAYSTATION      = static_cast<uint8_t>(ControllerButton::SYSTEM),
            OPTIONS          = static_cast<uint8_t>(ControllerButton::HOME),
            SHARE            = static_cast<uint8_t>(ControllerButton::OPTION),

            X_BUTTON         = static_cast<uint8_t>(ControllerButton::ACTION_0),
            O_BUTTON         = static_cast<uint8_t>(ControllerButton::ACTION_1),
            SQUARE_BUTTON    = static_cast<uint8_t>(ControllerButton::ACTION_2),
            TRIANGLE_BUTTON  = static_cast<uint8_t>(ControllerButton::ACTION_3),

            DPAD_UP          = static_cast<uint8_t>(ControllerButton::DPAD_UP),
            DPAD_LEFT        = static_cast<uint8_t>(ControllerButton::DPAD_LEFT),
            DPAD_DOWN        = static_cast<uint8_t>(ControllerButton::DPAD_DOWN),
            DPAD_RIGHT       = static_cast<uint8_t>(ControllerButton::DPAD_RIGHT),

            R1               = static_cast<uint8_t>(ControllerButton::BUMPER_R),
            R2               = static_cast<uint8_t>(ControllerButton::TRIGGER_R),
            L1               = static_cast<uint8_t>(ControllerButton::BUMPER_L),
            L2               = static_cast<uint8_t>(ControllerButton::TRIGGER_L),

            R3               = static_cast<uint8_t>(ControllerButton::JOYSTICK_R),
            L3               = static_cast<uint8_t>(ControllerButton::JOYSTICK_L),

            TOUCH_PAD        = static_cast<uint8_t>(ControllerButton::SPECIAL_0)
        };

        /** PS4 axis code bindings. */
        enum class ENGINE_API PS4Axis : uint8_t {
            L_STICK_X        = static_cast<uint8_t>(ControllerAxis::L_AXIS_X),
            L_STICK_Y        = static_cast<uint8_t>(ControllerAxis::L_AXIS_Y),

            R_STICK_X        = static_cast<uint8_t>(ControllerAxis::R_AXIS_X),
            R_STICK_Y        = static_cast<uint8_t>(ControllerAxis::R_AXIS_Y),

            TOUCH_PAD_X      = static_cast<uint8_t>(ControllerAxis::SPECIAL_X),
            TOUCH_PAD_Y      = static_cast<uint8_t>(ControllerAxis::SPECIAL_Y)
        };

    }

}

#endif