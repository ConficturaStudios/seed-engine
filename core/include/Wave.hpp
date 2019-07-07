#ifndef SEEDENGINE_INCLUDE_WAVE_H_
#define SEEDENGINE_INCLUDE_WAVE_H_

#include "Math.hpp"

namespace seedengine {

    namespace math {

        namespace wave {

            inline float triangle(float t, float period = 1, float amplitude = 1) {
                return abs(fmod(t, period) - amplitude);
            }

            inline float square(float t, float period = 1, float min = 0, float max = 1) {
                return fmod(t, period) < max ? max : min;
            }

            inline float sine(float t, float period = 1, float amplitude = 1) {
                return amplitude * sin(2 * PI * t / period);
            }

            inline float ripple(float x, float y, float period = 1, float amplitude = 1) {
                return sine(x * x + y * y, period, amplitude);
            }

        }

    }

    

}

#endif