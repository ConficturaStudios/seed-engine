/**
 * CommonTypes.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_COMMON_TYPES_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_COMMON_TYPES_H_

#include "CommonAPI.hpp"

#include <cstdint>
#include <cstddef>

// Typedefs and Aliases

using int8  = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

using uint8  = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

#if __cplusplus >= 201703L
    using byte = ::std::byte;
#else
    using byte = uint8;
#endif

using size_t = ::std::size_t;

// *** Functions ***

// Bitwise functions

/**
 * @brief Returns the provided data with the specified bit set to 1. The
 *        provided data itself is not modified.
 * 
 * @param data The data to evaluate.
 * @param bit The bit index from the right to set.
 * @return byte The provided data with the specified bit set to 1.
 */
constexpr inline byte bit_set(byte data, uint8 bit) noexcept {
    return data | (byte{1} << bit);
}

/**
 * @brief Returns the provided data with the specified bit cleared to 0. The
 *        provided data itself is not modified.
 * 
 * @param data The data to evaluate.
 * @param bit The bit index from the right to set.
 * @return byte The provided data with the specified bit cleared to 0.
 */
constexpr inline byte bit_clear(byte data, uint8 bit) noexcept {
    return data & ~(byte{1} << bit);
}

/**
 * @brief Returns the provided data with the specified bit flipped. The
 *        provided data itself is not modified.
 * 
 * @param data The data to evaluate.
 * @param bit The bit index from the right to set.
 * @return byte The provided data with the specified bit flipped.
 */
constexpr inline byte bit_flip(byte data, uint8 bit) noexcept {
    return data ^ (byte{1} << bit);
}

/**
 * @brief Checks if the specified bit is 1, returning true if it is, false otherwise. The
 *        provided data itself is not modified.
 * 
 * @param data The data to evaluate.
 * @param bit The bit index from the right to set.
 * @return true If the specified bit is 1.
 * @return false If the specified bit is 0.
 */
constexpr inline bool bit_check(byte data, uint8 bit) noexcept {
    return (data & (byte{1} << bit)) != byte{0};
}

#endif