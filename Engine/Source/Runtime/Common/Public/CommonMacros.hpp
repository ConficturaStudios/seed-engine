/**
 * CommonMacros.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_COMMON_MACROS_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_COMMON_MACROS_H_

#include "CommonAPI.hpp"

// TODO: Move into CommonDefinitions.hpp

/**
 * @brief Creates a bitwise flag.
 */
#define FLAG(x) (1 << x)

/**
 * @brief Checks if the option has the flag enabled.
 */
#define CHECK_FLAG(option, flag) (option & flag) == flag

#endif