#ifndef SEEDENGINE_INCLUDE_NOISE_H_
#define SEEDENGINE_INCLUDE_NOISE_H_

#include "Math.hpp"

namespace seedengine {

    namespace math {

        namespace noise {

            //TODO: Add tiling functionality option for noise generation

            /**
             * A noise generation function that takes in an x, y, z coordinate and returns a float value.
             */
            typedef float (*noise_func)(float, float, float);
            /**
             * A function that modifies the value of a fractal noise function on a per-point basis. Parameters should be ordered
             * value, x, y, z.
             */
            typedef float (*point_func)(float, float, float, float);
            /**
             * A function that modifies the value of a fractal noise function on a per-octave basis. Parameters should be ordered
             * value, x, y, z, octave, frequency, amplitude.
             */
            typedef float (*octave_func)(float, float, float, float, unsigned int, float, float);

            /**
             * Generates value noise at the passed coordinate.
             * 
             * @param x The x coordinate.
             * @param y The y coordinate. Defaults to 0.
             * @param z The z coordinate. Defaults to 0.
             * @return Computed value noise.
             */
            float value(float x, float y = 0, float z = 0);

            /**
             * Generates perlin noise at the passed coordinate.
             * 
             * @param x The x coordinate.
             * @param y The y coordinate. Defaults to 0.
             * @param z The z coordinate. Defaults to 0.
             * @return Computed perlin noise.
             */
            float perlin(float x, float y = 0, float z = 0);

            /**
             * Generates simplex noise at the passed coordinate.
             * 
             * @param x The x coordinate.
             * @param y The y coordinate. Defaults to 0.
             * @param z The z coordinate. Defaults to 0.
             * @return Computed simplex noise.
             */
            float simplex(float x, float y = 0, float z = 0);

            /**
             * Generates cubic noise at the passed coordinate.
             * 
             * @param x The x coordinate.
             * @param y The y coordinate. Defaults to 0.
             * @param z The z coordinate. Defaults to 0.
             * @return Computed cubic noise.
             */
            float cubic(float x, float y = 0, float z = 0);

            /**
             * Generates white noise at the passed coordinate.
             * 
             * @param x The x coordinate.
             * @param y The y coordinate. Defaults to 0.
             * @param z The z coordinate. Defaults to 0.
             * @return Computed white noise.
             */
            float white(float x, float y = 0, float z = 0);

            /**
             * Generates cellular noise at the passed coordinate.
             * 
             * @param x The x coordinate.
             * @param y The y coordinate. Defaults to 0.
             * @param z The z coordinate. Defaults to 0.
             * @return Computed cellular noise.
             */
            float cellular(float x, float y = 0, float z = 0);


            /**
             * Computes a fractal noise value at the specified coordinate. Noise can be computed in 1, 2, or 3 dimensions,
             * using 0 as the coordinate value for the unused dimensions. The noise function used can be specified
             * with a function pointer and defaults to Perlin noise. 
             *
             * Features such as frequency, amplitude, laucnarity, and gain can all be controlled, default values are provided.
             *
             * @param x The x-coordinate within the noise field.
             * @param y The y-coordinate within the noise field. Defaults to 0.
             * @param z The z-coordinate within the noise field. Defaults to 0.
             * @param func The noise generation function in the form float (*)(float, float, float). Defaults to perlin.
             * @param octaves The number of octaves to run. A value of 0 results in a return value of 0. Defaults to 1.
             * @param frequency The starting frequency of the generated noise. Defaults to 2.
             * @param amplitude The starting amplitude of the generated noise. Defaults to 1.
             * @param lacunarity The multiplier to apply to the frequency after each octave. Defaults to 2.
             * @param gain The multiplier to apply to the amplitude after each octave. Defaults to 0.5.
             * @return The value of a fractal noise field at the specified coordinate.
             */
            float fractal(float x, float y = 0, float z = 0, noise_func func = perlin, unsigned int octaves = 1,
                float frequency = 2, float amplitude = 1, float lacunarity = 2, float gain = 0.5f);


        }

    }

}

#endif