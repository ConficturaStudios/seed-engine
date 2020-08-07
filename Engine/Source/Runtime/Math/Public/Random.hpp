/**
 * Random.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_MATH_RANDOM_H_
#define SEEDENGINE_INCLUDE_RUNTIME_MATH_RANDOM_H_

#include "MathAPI.hpp"

#include <type_traits>

namespace seedengine {

    /**
     * @brief A random number generator.
     * @details A seeded psuedorandom number generator.
     */
    class ENGINE_API Random final {

        public:

            /** Constructs a new Random object. */
            Random();
            /**
             * @brief Constructs a new Random object.
             * 
             * @param seed The initial seed to use when generating random numbers.
             */
            Random(const unsigned int& seed);

            /** Destroy the Random object. */
            ~Random();

            /**
             * @brief Set the seed value.
             * 
             * @param seed The new seed value.
             */
            void setSeed(const unsigned int& seed);

            /**
             * @brief Get the seed of this random number generator.
             * 
             * @return unsigned int The seed of this random number generator.
             */
            unsigned int getSeed();

            /**
             * @brief Resets the random number generator to its value when it
             *        was first initialized using the original seed.
             * 
             */
            void reset();

            /**
             * @brief Gets the next random integer.
             * 
             * @return int The next random integer.
             */
            int next();

            /**
             * @brief Gets the next random number in the specified range.
             * 
             * @tparam T The type to generate.
             * @tparam enabled if T is an arithmatic type. 
             * @param min The minimum value of the range to use.
             * @param max The maximum value of the range to use.
             * @return T The next random number in range.
             */
            template <typename T = float, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
            T range(const T& min = 0, const T& max = 1) {
                return min + (static_cast<T>(next()) / static_cast<T>(RANDOM_MAX)) * static_cast<T>(max - min);
            }

        protected:

        private:

            /** The initial seed value. */
            unsigned int seed_;
            /** The seed value as it is advanced each call. */
            unsigned long int next_;

            /** The maximum possible random integer. */
            static const int RANDOM_MAX = 32767;

    };

}

#endif