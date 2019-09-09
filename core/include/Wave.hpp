#ifndef SEEDENGINE_INCLUDE_WAVE_H_
#define SEEDENGINE_INCLUDE_WAVE_H_

#include "Math.hpp"

namespace seedengine {

    namespace math {

        namespace wave {

            /**
             * @brief Samples a triangle wave at time t.
             * 
             * @param t The time at which to sample the wave.
             * @param period The period of the wave function.
             * @param amplitude The amplitude of the wave function.
             * @return float The wave value.
             */
            inline float triangle(float t, float period = 1, float amplitude = 1) {
                return abs(fmod(t, period) - amplitude);
            }

            /**
             * @brief Samples a square wave at time t.
             * 
             * @param t The time at which to sample the wave.
             * @param period The period of the wave function.
             * @param min The minimum value of the square wave.
             * @param max The maximum value of the square wave.
             * @return float The wave value.
             */
            inline float square(float t, float period = 1, float min = 0, float max = 1) {
                return fmod(t, period) < max ? max : min;
            }

            /**
             * @brief Samples a sine wave at time t.
             * 
             * @param t The time at which to sample the wave.
             * @param period The period of the wave function.
             * @param amplitude The amplitude of the wave function.
             * @return float The wave value.
             */
            inline float sine(float t, float period = 1, float amplitude = 1) {
                return amplitude * sin(2 * PI * t / period);
            }

            /**
             * @brief Samples a circular ripple noise field at the specified position.
             * 
             * @param x The x position at which to sample the wave.
             * @param y The y position at which to sample the wave.
             * @param period The period of the wave function.
             * @param amplitude The amplitude of the wave function.
             * @return float The wave value.
             */
            inline float ripple(float x, float y, float period = 1, float amplitude = 1) {
                return sine(x * x + y * y, period, amplitude);
            }

        }

    }

    

}

#endif