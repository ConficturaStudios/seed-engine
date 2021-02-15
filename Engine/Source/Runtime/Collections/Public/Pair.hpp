/**
 * Pair.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_PAIR_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_PAIR_H_

#include "CollectionsAPI.hpp"

namespace seedengine {

    /**
     * @brief A pair of two generic objects of any type.
     * @details An ordered pair of generic objects. The first element is of type T1
     *          while the second is of type T2. 
     * 
     * @tparam T1 The type of the first element in this pair.
     * @tparam T2 The type of the second element in this pair.
     */
    template <typename T1, typename T2>
    struct ENGINE_API Pair {

        public:

            /** The type of the first element in this pair. */
            using FirstType = T1;
            /** The type of the second element in this pair. */
            using SecondType = T2;

            /** The first element of this pair. */
            T1 first;
            /** The second element of this pair. */
            T2 second;

        // Constructors and destructor

            /**
             * @brief The default constructor for Pair objects.
             * @details Constructs a new Pair with default initialization for all members.
             */
            constexpr Pair() : Pair(T1(), T2()) {
                
            }

            /**
             * @brief Constructs a Pair from the two provided values.
             * @details Constructs a new Pair with the specified value for each member.
             * 
             * @param first The first element value to store in this pair.
             * @param second The second element value to store in this pair.
             */
            constexpr Pair(const T1& first, const T2& second) : first(first), second(second) {

            }

            /**
             * @brief The copy constructor for Pair objects.
             * @details Constructs a new Pair by copying an existing Pair.
             */
            Pair(const Pair& ref) = default;
            
            /**
             * @brief The move constructor for Pair objects.
             * @details Constructs a new Pair by moving the data of a Pair into this object.
             */
            Pair(Pair&& ref) = default;

            /**
             * @brief The destructor for Pair objects.
             * @details Called when an instance of Pair is deleted.
             */
            virtual ~Pair() = default;

        // Functions

            /**
             * @brief Returns a copy of this pair in reverse order.
             * 
             * @return Pair<T2, T1> A reversed copy of this Pair.
             */
            [[nodiscard]] Pair<T2, T1> reverse() const {
                return Pair<T2, T1>(second, first);
            }

        // Assignment Operators

            /**
             * @brief The copy assignment operator for Pair objects.
             * @details Reassigns the value of this object by copying the data of a Pair into this object.
             */
            Pair& operator=(const Pair& rhs) = default;

            /**
             * @brief The move assignment operator for Pair objects.
             * @details Reassigns the value of this object by moving the data of a Pair into this object.
             */
            Pair& operator=(Pair&& rhs) = default;

        // Comparison Operators

            /**
             * @brief Checks if two Pairs are equal.
             * 
             * @param rhs The Pair to check against.
             * @return true If the Pairs are equal.
             * @return false  If the Pairs are not equal.
             */
            [[nodiscard]] bool operator==(const Pair& rhs) const {
                return first == rhs.first && second == rhs.second;
            }

            /**
             * @brief Checks if two Pairs are not equal.
             * 
             * @param rhs The Pair to check against.
             * @return true If the Pairs are not equal.
             * @return false  If the Pairs are equal.
             */
            [[nodiscard]] bool operator!=(const Pair& rhs) const {
                return first != rhs.first || second != rhs.second;
            }

    };

}

#endif