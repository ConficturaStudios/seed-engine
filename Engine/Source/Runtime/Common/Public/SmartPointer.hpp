/**
 * SmartPointer.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_SMART_POINTER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_SMART_POINTER_H_

#include "CommonAPI.hpp"
#include <memory>

namespace seedengine {

    template<typename T>
    using SharedPtr = std::shared_ptr<T>;
    template<typename T, typename... Args>
    constexpr SharedPtr<T> CreateSharedPtr(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using UniquePtr = std::unique_ptr<T>;
    template<typename T, typename... Args>
    constexpr UniquePtr<T> CreateUniquePtr(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    template<typename T>
    constexpr void TransferUniquePtr(UniquePtr<T>& target, UniquePtr<T>& source) {
        target = std::move(source);
    }

    template<typename T>
    using WeakPtr = std::weak_ptr<T>;

}

#endif