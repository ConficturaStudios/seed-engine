/**
 * @file CommonSTL.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_COMMON_STL_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_COMMON_STL_H_

#include "CommonAPI.hpp"

#include <cstddef>
#include <cstdint>
#include <cstring>

// STL Includes:

#include <iostream>
#include <fstream>
#include <cstdio>

#if defined(_WIN32)
// Windows only includes

    #include <winsock2.h>

    #include <windows.h>
    #include <windowsx.h>
    
#else

    #include <arpa/inet.h>

    inline float ntohf(uint32_t net) {
        union {
            uint32_t bytes;
            float value;
        } pair;
        pair.bytes = ntohl(net);
        return pair.value;
    }

    inline uint32_t htonf(float host) {
        union {
            uint32_t bytes;
            float value;
        } pair;
        pair.value = host;
        return htonl(pair.bytes);
    }

#endif

#include <string>
#include <sstream>

#include <stdexcept>
#include <cstdarg>

#include <thread>
#include <chrono>
#include <memory>
#include <mutex>

#include <array>
#include <queue>
#include <map>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <initializer_list>

#include <regex>
#include <functional>
#include <algorithm>

#include <exception>
#include <type_traits>

#include <limits>

// STL Extensions

namespace std {

#ifndef _WIN32

    template<typename T, typename... Args>
    inline unique_ptr<T> make_unique(Args&& ... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

#endif

/*
// C++14 or newer code
#if __cplusplus >= 201400L

// Pre C++14 code
#else

    template<typename T, T... Ints>
    struct integer_sequence {
        typedef T value_type;

        static constexpr std::size_t size() noexcept {
            return sizeof...(Ints);
        }
    };

    template<typename T, std::size_t... Ints>
    struct __make_integer_sequence;

    template<typename T, std::size_t N, std::size_t... Ints>
    struct __make_integer_sequence<T, N, Ints...> {
       using type = typename __make_integer_sequence<T, N - 1, N - 1, Ints...>::type;
    };

    template<typename T, std::size_t... Ints>
    struct __make_integer_sequence<T, 0, Ints...> {
        using type = integer_sequence<T, ((T)Ints)...>;
    };

    template<std::size_t... Ints>
    using index_sequence = std::integer_sequence<std::size_t, Ints...>;

    template<typename T, T N>
    using make_integer_sequence = typename __make_integer_sequence<T, N>::type;

    template<std::size_t N>
    using make_index_sequence = std::make_integer_sequence<std::size_t, N>;

    template<typename... T>
    using index_sequence_for = std::make_index_sequence<sizeof...(T)>;

#endif*/

}

#endif