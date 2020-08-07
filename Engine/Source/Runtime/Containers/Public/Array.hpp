/**
 * Array.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_CONTAINERS_ARRAY_H_
#define SEEDENGINE_INCLUDE_RUNTIME_CONTAINERS_ARRAY_H_

#include "ContainersAPI.hpp"

namespace seedengine {

    /**
     * @brief A generic array container of a fixed size.
     * @details
     * 
     * 
     * @tparam T The type stored by this array.
     * @tparam Size The size of this array.
     */
    template <typename T, std::size_t Size>
    class Array final {

        public:

            /** The type stored by this array. */
            using Type = T;
            /** The size of this array. */
            static constexpr const std::size_t SIZE = Size;

        private:

            class ArrayIterator final {

                friend class Array<T, Size>;

            };

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Array objects.
             * @details Constructs a new Array with default initialization for all members.
             */
            Array() {
                
            }

            /**
             * @brief The copy constructor for Array objects.
             * @details Constructs a new Array by copying an existing Array.
             */
            Array(const Array& ref) = default;
            
            /**
             * @brief The move constructor for Array objects.
             * @details Constructs a new Array by moving the data of a Array into this object.
             */
            Array(Array&& ref) = default;

            /**
             * @brief The destructor for Array objects.
             * @details Called when an instance of Array is deleted.
             */
            ~Array() {
                
            }

        // Functions



        // Access Operators

            T& operator[](const std::size_t& index) {
                return m_data[index];
            }

            const T& operator[](const std::size_t& index) const {
                return m_data[index];
            }

        // Assignment Operators

            /**
             * @brief The copy assignment operator for Array objects.
             * @details Reassigns the value of this object by copying the data of a Array into this object.
             */
            Array& operator=(const Array& rhs) = default;

            /**
             * @brief The move assignment operator for Array objects.
             * @details Reassigns the value of this object by moving the data of a Array into this object.
             */
            Array& operator=(Array&& rhs) = default;

        private:

            T m_data[Size];

    };

}

#endif