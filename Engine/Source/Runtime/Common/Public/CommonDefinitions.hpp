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

#include "CommonSTL.hpp"

// Typedefs and Aliases

using int8  = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

using uint8  = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using size_t = ::std::size_t;



// *** Macros ***

/**
 * @brief Converts the token(s) passed to a c style string expression.
 */
#define STR(...) #__VA_ARGS__

/**
 * Expands the provided macro argument x.
 */
#define EXPAND(x) x

/**
 * @brief Creates a bitwise flag.
 */
#define FLAG(x) (1 << (x))

/**
 * @brief Checks if the option has the flag enabled.
 */
#define CHECK_FLAG(option, flag) (((option) & (flag)) == (flag))



// *** Functions ***

// Bitwise functions

// TODO: Extend bitwise functions to support more integral types


namespace Memory {

#if __cplusplus >= 201703L
    using byte = ::std::byte;
#else
    using byte = uint8;
#endif

    /**
     * Represents the possible byte order representations used by the system.
     */
    enum class EByteOrder {
#ifdef _WIN32
        /** Little endian byte order. */
        LITTLE = 0,
        /** Big endian byte order. */
        BIG    = 1,
        /** The current system's byte order. */
        NATIVE = LITTLE,
#else
        /** Little endian byte order. */
        LITTLE = __ORDER_LITTLE_ENDIAN__,
        /** Big endian byte order. */
        BIG    = __ORDER_BIG_ENDIAN__,
        /** The current system's byte order. */
        NATIVE = __BYTE_ORDER__,
#endif
        /** The standard network byte order. */
        NETWORK = BIG
    };

    /**
     * Reverses the order of the bytes pointed to by start in memory.
     * @param start The address of the first byte to reverse.
     * @param size The number of bytes to reverse.
     */
    constexpr void ReverseBytes(void* start, size_t size) {
        uint8* low = (uint8*)start;
        uint8* high = (uint8*)(low + size - 1);
        uint8 temp = 0;
        while (low < high) {
            temp    = *low;
            *low++  = *high;
            *high-- = temp;
        }
    }

    // Network byte order to host byte order

    template <typename T>
    [[nodiscard]] constexpr T ntoh(T network) noexcept = delete;

    template <>
    [[nodiscard]] constexpr uint8 ntoh(uint8 network) noexcept {
        return network;
    }
    template <>
    [[nodiscard]] constexpr uint16 ntoh(uint16 network) noexcept {
        if constexpr (EByteOrder::NATIVE == EByteOrder::NETWORK) return network;
        else {
            uint16 result = network;
            ReverseBytes(&result, sizeof(uint16));
            return result;
        }
    }
    template <>
    [[nodiscard]] constexpr uint32 ntoh(uint32 network) noexcept {
        if constexpr (EByteOrder::NATIVE == EByteOrder::NETWORK) return network;
        else {
            uint32 result = network;
            ReverseBytes(&result, sizeof(uint32));
            return result;
        }
    }
    template <>
    [[nodiscard]] constexpr uint64 ntoh(uint64 network) noexcept {
        if constexpr (EByteOrder::NATIVE == EByteOrder::NETWORK) return network;
        else {
            uint64 result = network;
            ReverseBytes(&result, sizeof(uint64));
            return result;
        }
    }
    template <>
    [[nodiscard]] constexpr float ntoh(float network) noexcept {
        if constexpr (EByteOrder::NATIVE == EByteOrder::NETWORK) return network;
        else {
            float result = network;
            ReverseBytes(&result, sizeof(float));
            return result;
        }
    }
    template <>
    [[nodiscard]] constexpr double ntoh(double network) noexcept {
        if constexpr (EByteOrder::NATIVE == EByteOrder::NETWORK) return network;
        else {
            double result = network;
            ReverseBytes(&result, sizeof(double));
            return result;
        }
    }

    // Host byte order to network byte order

    template <typename T>
    [[nodiscard]] constexpr T hton(T host) noexcept = delete;

    template <>
    [[nodiscard]] constexpr uint8 hton(uint8 host) noexcept {
        return host;
    }
    template <>
    [[nodiscard]] constexpr uint16 hton(uint16 host) noexcept {
        if constexpr (EByteOrder::NATIVE == EByteOrder::NETWORK) return host;
        else {
            uint16 result = host;
            ReverseBytes(&result, sizeof(uint16));
            return result;
        }
    }
    template <>
    [[nodiscard]] constexpr uint32 hton(uint32 host) noexcept {
        if constexpr (EByteOrder::NATIVE == EByteOrder::NETWORK) return host;
        else {
            uint32 result = host;
            ReverseBytes(&result, sizeof(uint32));
            return result;
        }
    }
    template <>
    [[nodiscard]] constexpr uint64 hton(uint64 host) noexcept {
        if constexpr (EByteOrder::NATIVE == EByteOrder::NETWORK) return host;
        else {
            uint64 result = host;
            ReverseBytes(&result, sizeof(uint64));
            return result;
        }
    }
    template <>
    [[nodiscard]] constexpr float hton(float host) noexcept {
        if constexpr (EByteOrder::NATIVE == EByteOrder::NETWORK) return host;
        else {
            float result = host;
            ReverseBytes(&result, sizeof(float));
            return result;
        }
    }
    template <>
    [[nodiscard]] constexpr double hton(double host) noexcept {
        if constexpr (EByteOrder::NATIVE == EByteOrder::NETWORK) return host;
        else {
            double result = host;
            ReverseBytes(&result, sizeof(double));
            return result;
        }
    }

    // Bit manipulation

    /**
     * @brief Returns the provided data with the specified bit set to 1. The
     *        provided data itself is not modified.
     *
     * @param data The data to evaluate.
     * @param bit The bit index from the right to set.
     * @return byte The provided data with the specified bit set to 1.
     */
    [[nodiscard]] constexpr inline byte BitSet(byte data, uint8 bit) noexcept {
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
    [[nodiscard]] constexpr inline byte BitClear(byte data, uint8 bit) noexcept {
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
    [[nodiscard]] constexpr inline byte BitFlip(byte data, uint8 bit) noexcept {
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
    [[nodiscard]] constexpr inline bool BitCheck(byte data, uint8 bit) noexcept {
        return (data & (byte{1} << bit)) != byte{0};
    }

}



// Compile Time String Functions

/**
 * @brief Generates a unique hash identifier given a c style string. This
 *        function is designed to be able to run at compile time.
 * 
 * @param cstr The c style string to process.
 * @return uint64 A unique 64 bit unsigned hash value representing the given string.
 */
[[nodiscard]] constexpr inline uint64 strhash(const char* cstr) noexcept {
    return (cstr && *cstr != '\0') ?
        static_cast<uint64>(*cstr) + 33 * strhash(cstr + 1) : 5381;
}

#endif