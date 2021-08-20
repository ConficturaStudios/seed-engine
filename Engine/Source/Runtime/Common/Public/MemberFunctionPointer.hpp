/**
 * MemberFunctionPointer.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_MEMBER_FUNCTION_POINTER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_MEMBER_FUNCTION_POINTER_H_

#include "CommonAPI.hpp"
#include <utility>
#include <tuple>
#include "Debug.hpp"

namespace seedengine {

    /**
     * @brief A wrapper class for class member function pointers.
     * @details A wrapper class for raw class member function pointers.
     * 
     * @tparam CT The class type that contains this function.
     * @tparam RT The return type of the function.
     * @tparam Args The parameter types for the function.
     */
    template<class CT, typename RT, typename... Args>
    class MemberFunctionPointer final {

            // TODO: Add support for const member function pointers

        public:

        // Type aliases

            /** The type of the class that contains this function. */
            using ClassType = CT;
            /** The type of the raw function pointer wrapped by this class. */
            using PointerType = RT (CT::*)(Args... args);
            /** The type returned by this function pointer. */
            using ReturnType = RT;
            /** The parameter types of this function pointer wrapped in a tuple. */
            using Parameters = std::tuple<Args&&...>;

            /** The nth parameter type of this function. */
            template<std::size_t n>
            using Parameter = typename std::tuple_element<n, Parameters>::type;

        // Constructors and destructor

            /**
             * @brief The default constructor for MemberFunctionPointer objects.
             * @details Constructs a new MemberFunctionPointer with default initialization for all members.
             */
            MemberFunctionPointer() = delete;

            /**
             * @brief Constructs a new MemberFunctionPointer from a raw function pointer or lambda.
             * @details Constructs a new MemberFunctionPointer from a raw function pointer or lambda.
             * 
             * @param ptr The raw function pointer.
             */
            MemberFunctionPointer(const PointerType& ptr) {
                ENGINE_ASSERT(ptr != nullptr, "Cannot create a member function pointer from a null pointer")
                this->m_ptr = ptr;
            }

            /**
             * @brief The copy constructor for MemberFunctionPointer objects.
             * @details Constructs a new MemberFunctionPointer by copying an existing MemberFunctionPointer.
             */
            MemberFunctionPointer(const MemberFunctionPointer& ref) noexcept = default;
            
            /**
             * @brief The move constructor for MemberFunctionPointer objects.
             * @details Constructs a new MemberFunctionPointer by moving the data of a MemberFunctionPointer into this object.
             */
            MemberFunctionPointer(MemberFunctionPointer&& ref) noexcept = default;

            /**
             * @brief The destructor for MemberFunctionPointer objects.
             * @details Called when an instance of MemberFunctionPointer is deleted.
             */
            ~MemberFunctionPointer() = default;

        // Functions

            /**
             * @brief Calls the stored function pointer using the passed parameters.
             * 
             * @param inst The instance of the containing class type to call this function on.
             * @param args The parameters to call this function with.
             * @return ReturnType The return value of this function.
             */
            RT invoke(CT* inst, Args&&... args) const {
                return (inst->*(m_ptr))(std::forward<Args>(args)...);
            }

        // Call Operator

            /**
             * @brief Calls the stored function pointer using the passed parameters.
             *
             * @param inst The instance of the containing class type to call this function on.
             * @param args The parameters to call this function with.
             * @return ReturnType The return value of this function.
             */
            RT operator()(CT* inst, Args&&... args) const {
                return (inst->*(m_ptr))(std::forward<Args>(args)...);
            }

        // Cast Operators

            [[nodiscard]] operator PointerType() const noexcept {
                return m_ptr;
            }

        // Comparison Operators

            [[nodiscard]] bool operator==(const MemberFunctionPointer& rhs) const {
                return this->m_ptr == rhs.m_ptr;
            }
            [[nodiscard]] bool operator==(const PointerType& rhs) const {
                return this->m_ptr == rhs;
            }

            [[nodiscard]] bool operator!=(const MemberFunctionPointer& rhs) const {
                return this->m_ptr != rhs.m_ptr;
            }
            [[nodiscard]] bool operator!=(const PointerType& rhs) const {
                return this->m_ptr != rhs;
            }

        // Assignment Operators

            /**
             * @brief The copy assignment operator for MemberFunctionPointer objects.
             * @details Reassigns the value of this object by copying the data of a MemberFunctionPointer into this object.
             */
            MemberFunctionPointer& operator=(const MemberFunctionPointer& ref) noexcept = default;

            /**
             * @brief The move assignment operator for MemberFunctionPointer objects.
             * @details Reassigns the value of this object by moving the data of a MemberFunctionPointer into this object.
             */
            MemberFunctionPointer& operator=(MemberFunctionPointer&& ref) noexcept = default;

        private:

            /** The pointer to the wrapped function. */
            PointerType m_ptr;

    };

}

#endif