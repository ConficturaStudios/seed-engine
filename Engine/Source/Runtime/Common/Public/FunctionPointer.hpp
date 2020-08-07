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

namespace seedengine {

    /**
     * @brief A wrapper class for function pointers.
     * @details A wrapper class for raw function pointers and captureless lambda statements.
     * 
     * @tparam ReturnType The return type of the function.
     * @tparam Args The parameter types for the function.
     */
    template<typename ReturnType, typename... Args>
    class ENGINE_API FunctionPointer final {

        public:

        // Type aliases

            /** The type of the raw function pointer wrapped by this class. */
            using pointer_t = ReturnType (*)(Args... args);
            /** The type returned by this function pointer. */
            using return_t = ReturnType;
            /** The parameter types of this function pointer wrapped in a tuple. */
            using parameters = std::tuple<Args&&...>;

            /** The nth paramter type of this function. */
            template<std::size_t n>
            using parameter = typename std::tuple_element<n, parameters>::type;

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
            FunctionPointer(const pointer_t& ptr) {
                this->ptr = ptr;
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
            FunctionPointer(FunctionPointer&& ref) = default;

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
            ReturnType invoke(Args&&... args) {
                return (ptr)(std::forward<Args>(args)...);
            }

        // Cast Operators

            operator pointer_t() const {
                return ptr;
            }

        // Comparison Operators

            bool operator==(const FunctionPointer& rhs) const {
                return this->ptr == rhs.ptr;
            }
            bool operator==(const pointer_t& rhs) const {
                return this->ptr == rhs;
            }

            bool operator!=(const FunctionPointer& rhs) const {
                return this->ptr != rhs.ptr;
            }
            bool operator!=(const pointer_t& rhs) const {
                return this->ptr != rhs;
            }

        // Assignment Operators

            /**
             * @brief The copy assignment operator for FunctionPointer objects.
             * @details Reassigns the value of this object by copying the data of a FunctionPointer into this object.
             */
            FunctionPointer& operator=(const FunctionPointer& ref) = default;

            /**
             * @brief The move assignment operator for FunctionPointer objects.
             * @details Reassigns the value of this object by moving the data of a FunctionPointer into this object.
             */
            FunctionPointer& operator=(FunctionPointer&& ref) = default;

        private:

            /** The pointer to the wrapped function. */
            pointer_t ptr;

    };

}

#endif