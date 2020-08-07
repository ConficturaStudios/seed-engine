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

namespace seedengine {

    /**
     * @brief A wrapper class for class member function pointers.
     * @details A wrapper class for raw class member function pointers.
     * 
     * @tparam Class The class type that contains this function.
     * @tparam ReturnType The return type of the function.
     * @tparam Args The parameter types for the function.
     */
    template<class Class, typename ReturnType, typename... Args>
    class ENGINE_API MemberFunctionPointer final {

        public:

        // Type aliases

            /** The type of the class that contains this function. */
            using class_t = Class;
            /** The type of the raw function pointer wrapped by this class. */
            using pointer_t = ReturnType (Class::*)(Args... args);
            /** The type returned by this function pointer. */
            using return_t = ReturnType;
            /** The parameter types of this function pointer wrapped in a tuple. */
            using parameters = std::tuple<Args&&...>;

            /** The nth paramter type of this function. */
            template<std::size_t n>
            using parameter = typename std::tuple_element<n, parameters>::type;

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
            MemberFunctionPointer(const pointer_t& ptr) {
                this->ptr = ptr;
            }

            /**
             * @brief The copy constructor for MemberFunctionPointer objects.
             * @details Constructs a new MemberFunctionPointer by copying an existing MemberFunctionPointer.
             */
            MemberFunctionPointer(const MemberFunctionPointer& ref) = default;
            
            /**
             * @brief The move constructor for MemberFunctionPointer objects.
             * @details Constructs a new MemberFunctionPointer by moving the data of a MemberFunctionPointer into this object.
             */
            MemberFunctionPointer(MemberFunctionPointer&& ref) = default;

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
            ReturnType invoke(Class* inst, Args&&... args) {
                return (inst->*(ptr))(std::forward<Args>(args)...);
            }

        // Cast Operators

            operator pointer_t() const {
                return ptr;
            }

        // Comparison Operators

            bool operator==(const MemberFunctionPointer& rhs) const {
                return this->ptr == rhs.ptr;
            }
            bool operator==(const pointer_t& rhs) const {
                return this->ptr == rhs;
            }

            bool operator!=(const MemberFunctionPointer& rhs) const {
                return this->ptr != rhs.ptr;
            }
            bool operator!=(const pointer_t& rhs) const {
                return this->ptr != rhs;
            }

        // Assignment Operators

            /**
             * @brief The copy assignment operator for MemberFunctionPointer objects.
             * @details Reassigns the value of this object by copying the data of a MemberFunctionPointer into this object.
             */
            MemberFunctionPointer& operator=(const MemberFunctionPointer& ref) = default;

            /**
             * @brief The move assignment operator for MemberFunctionPointer objects.
             * @details Reassigns the value of this object by moving the data of a MemberFunctionPointer into this object.
             */
            MemberFunctionPointer& operator=(MemberFunctionPointer&& ref) = default;

        private:

            /** The pointer to the wrapped function. */
            pointer_t ptr;

    };

}

#endif