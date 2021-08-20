/**
 * FunctionPointer.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_FUNCTION_POINTER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_FUNCTION_POINTER_H_

#include "CommonAPI.hpp"
#include <utility>
#include <tuple>
#include "Debug.hpp"

namespace seedengine {

    /**
     * @brief A wrapper class for function pointers.
     * @details A wrapper class for raw function pointers and captureless lambda statements.
     * 
     * @tparam RT The return type of the function.
     * @tparam Args The parameter types for the function.
     */
    template<typename RT, typename... Args>
    class FunctionPointer final {

        public:

        // Type aliases

            /** The type of the raw function pointer wrapped by this class. */
            using PointerType = RT (*)(Args... args);
            /** The type returned by this function pointer. */
            using ReturnType = RT;
            /** The parameter types of this function pointer wrapped in a tuple. */
            using Parameters = std::tuple<Args&&...>;

            /** The nth parameter type of this function. */
            template<std::size_t n>
            using Parameter = typename std::tuple_element<n, Parameters>::type;

        // Constructors and destructor

            /**
             * @brief The default constructor for FunctionPointer objects.
             * @details Constructs a new FunctionPointer with default initialization for all members.
             */
            FunctionPointer() = delete;

            /**
             * @brief Constructs a new FunctionPointer from a raw function pointer or lambda.
             * @details Constructs a new FunctionPointer from a raw function pointer or lambda.
             * 
             * @param ptr The raw function pointer.
             */
            FunctionPointer(const PointerType& ptr) {
                ENGINE_ASSERT(ptr != nullptr, "Cannot create a function pointer from a null pointer")
                this->m_ptr = ptr;
            }

            /**
             * @brief The copy constructor for FunctionPointer objects.
             * @details Constructs a new FunctionPointer by copying an existing FunctionPointer.
             */
            FunctionPointer(const FunctionPointer& ref) = default;
            
            /**
             * @brief The move constructor for FunctionPointer objects.
             * @details Constructs a new FunctionPointer by moving the data of a FunctionPointer into this object.
             */
            FunctionPointer(FunctionPointer&& ref) noexcept = default;

            /**
             * @brief The destructor for FunctionPointer objects.
             * @details Called when an instance of FunctionPointer is deleted.
             */
            ~FunctionPointer() = default;

        // Functions

            /**
             * @brief Calls the stored function pointer using the passed parameters.
             * 
             * @param args The parameters to call this function with.
             * @return ReturnType The return value of this function.
             */
            RT invoke(Args&&... args) const {
                return (m_ptr)(std::forward<Args>(args)...);
            }

        // Call operator

            /**
             * @brief Calls the stored function pointer using the passed parameters.
             *
             * @param args The parameters to call this function with.
             * @return ReturnType The return value of this function.
             */
            RT operator()(Args&&... args) const {
                return (m_ptr)(std::forward<Args>(args)...);
            }

        // Cast Operators

            [[nodiscard]] operator PointerType() const noexcept {
                return m_ptr;
            }

        // Comparison Operators

            [[nodiscard]] bool operator==(const FunctionPointer& rhs) const {
                return this->m_ptr == rhs.m_ptr;
            }
            [[nodiscard]] bool operator==(const PointerType& rhs) const {
                return this->m_ptr == rhs;
            }

            [[nodiscard]] bool operator!=(const FunctionPointer& rhs) const {
                return this->m_ptr != rhs.m_ptr;
            }
            [[nodiscard]] bool operator!=(const PointerType& rhs) const {
                return this->m_ptr != rhs;
            }

        // Assignment Operators

            /**
             * @brief The copy assignment operator for FunctionPointer objects.
             * @details Reassigns the value of this object by copying the data of a FunctionPointer into this object.
             */
            FunctionPointer& operator=(const FunctionPointer& ref) noexcept = default;

            /**
             * @brief The move assignment operator for FunctionPointer objects.
             * @details Reassigns the value of this object by moving the data of a FunctionPointer into this object.
             */
            FunctionPointer& operator=(FunctionPointer&& ref) noexcept = default;

        private:

            /** The pointer to the wrapped function. */
            PointerType m_ptr;

    };

}

#endif