#ifndef SEEDENGINE_INCLUDE_RANDOM_H_
#define SEEDENGINE_INCLUDE_RANDOM_H_

#include <type_traits>

namespace seedengine {
    
    class Random {

    public:

        Random() : Random(1) {}
        Random(const unsigned int& seed) : seed_(seed), next_(seed) {

        }
        ~Random() {}

        int next() {
            next_ = next_ * 1103515245 + 12345;
            return (unsigned int)(next_/65536) % 32768;
        }

        
        template <typename T = float, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
        T range(const T& min = 0, const T& max = 1) {
            return min + (static_cast<T>(next()) / static_cast<T>(RANDOM_MAX)) * static_cast<T>(max - min);
        }

    protected:

    private:

        unsigned int seed_;
        unsigned long int next_;

        static const int RANDOM_MAX = 32767;

    };

}

#endif