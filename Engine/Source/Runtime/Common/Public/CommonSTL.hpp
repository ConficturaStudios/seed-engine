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
#include <cerrno>

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

}

#endif