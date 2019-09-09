#ifndef SEEDENGINE_INCLUDE_RANDOM_H_
#define SEEDENGINE_INCLUDE_RANDOM_H_

#include <type_traits>

namespace seedengine {
    
    /**
     * @brief A random number generator.
     * @details
     */
    class Random {

    public:

        /** Constructs a new Random object. */
        Random() : Random(1) {}
        /**
         * @brief Constructs a new Random object.
         * 
         * @param seed The initial seed to use when generating random numbers.
         */
        Random(const unsigned int& seed) : seed_(seed), next_(seed) {

        }
        /** Destroy the Random object. */
        ~Random() {}

        /**
         * @brief Set the seed value.
         * 
         * @param seed The new seed value.
         */
        void setSeed(const unsigned int& seed) {
            this->seed_ = seed;
            this->next_ = seed;
        }

        /**
         * @brief Get the seed of this random number generator.
         * 
         * @return unsigned int The seed of this random number generator.
         */
        unsigned int getSeed() {
            return this->seed_;
        }

        /**
         * @brief Resets the random number generator to its value when it
         *        was first initialized using the original seed.
         * 
         */
        void reset() {
            this->next_ = this->seed_;
        }

        /**
         * @brief Gets the next random integer.
         * 
         * @return int The next random integer.
         */
        int next() {
            next_ = next_ * 1103515245 + 12345;
            return (unsigned int)(next_/65536) % 32768;
        }

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