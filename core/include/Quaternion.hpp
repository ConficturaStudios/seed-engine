#ifndef SEEDENGINE_INCLUDE_QUATERNION_H_
#define SEEDENGINE_INCLUDE_QUATERNION_H_

#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdarg>
#include "Math.hpp"
#include "Property.hpp"

namespace seedengine {

    //TODO: Finish Quaternion wrapper class.

    template<
        typename T = float,
        typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0
    >
    class Quaternion {

    public:

    protected:

    private:

    };

}

#endif