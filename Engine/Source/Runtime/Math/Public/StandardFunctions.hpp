/**
 * StandardFunctions.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_MATH_STANDARD_FUNCTIONS_H_
#define SEEDENGINE_INCLUDE_RUNTIME_MATH_STANDARD_FUNCTIONS_H_

#include "MathAPI.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <limits>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <initializer_list>

namespace seedengine {

    namespace math {

        /** The smallest floating point increment. */
        const float EPSILON = std::numeric_limits<float>::epsilon();
        /** Infinity. */
        const float INF = std::numeric_limits<float>::infinity();
        /** Negative Infinity. */
        const float NEG_INF = -INF;
        /** Pi (3.14159...). */
        const float PI = (float)M_PI;
        /** Euler's Number / The base of the natural logarithm. */
        const float E = (float)M_E;
        /** The conversion constant for converting degrees into radians. */
        const float DEG2RAD = PI / 180.0f;
        /** The conversion constant for converting radians into degrees. */
        const float RAD2DEG = 180.0f / PI;

        /**
         * @brief Is this number odd?
         * 
         * @tparam T the type to evaluate
         * @tparam enabled if T is an integral type.
         * @param value The number to check.
         * @return true If the number is odd.
         * @return false If the number is even.
         */
        template <typename T = int, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
        inline bool isOdd(const T& value) {
            return value & 1;
        }
        /**
         * @brief Is this number odd?
         * 
         * @tparam T the type to evaluate
         * @tparam enabled if T is a floating point type.
         * @param value The number to check.
         * @return true If the number is odd.
         * @return false If the number is even.
         */
        template <typename T = float, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
        inline bool isOdd(const T& value) {
            return (int)value % 2 == 1;
        }

        /**
         * @brief Returns the absolute value of the passed number.
         * 
         * @tparam T the type to evaluate
         * @tparam enabled if T is an arithmatic point type.
         * @param value The number to retrieve the absolute value of.
         * @return T The absolute value of value.
         */
        template <typename T = float, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
        inline T abs(const T& value) { return std::abs(value); }
        
        /**
         * @brief Returns the arc-cosine of value.
         * 
         * @param value The value to take the arc-cosine of.
         * @return float The angle in radians whose cosine is value.
         */
        ENGINE_API extern float acos(const float& value);
        /**
         * @brief Returns the nonnegative area hyperbolic cosine of value.
         * 
         * @param value The value to take the area hyperbolic cosine of.
         * @return float The nonnegative area hyperbolic cosine of value.
         */
        ENGINE_API extern float acosh(const float& value);
        /**
         * @brief Checks if the two values a and b are approximately equal.
         * 
         * @param a The value to check.
         * @param b The value to check against.
         * @return true If a is approximately equal to b.
         * @return false If a is not approximately equal to b.
         */
        ENGINE_API extern bool approx(const float& a, const float& b);
        /**
         * @brief Returns the arc-sine of value.
         * 
         * @param value The value to take the arc-sine of.
         * @return float The angle in radians whose sine is value.
         */
        ENGINE_API extern float asin(const float& value);
        /**
         * @brief Returns the area hyperbolic sine of value.
         * 
         * @param value The value to take the area hyperbolic sine of.
         * @return float The area hyperbolic sine of value.
         */
        ENGINE_API extern float asinh(const float& value);
        /**
         * @brief Returns the arc-tangent of value.
         * 
         * @param value The value to take the arc-tangent of.
         * @return float The angle in radians whose tangent is value.
         */
        ENGINE_API extern float atan(const float& value);
        /**
         * @brief Returns the arc-tangent of y / x.
         * 
         * @param y The numerator of the ratio to evaluate.
         * @param x The denominator of the ratio to evaluate.
         * @return float The angle in radians whose tangent is y / x.
         */
        ENGINE_API extern float atan2(const float& y, const float& x);
        /**
         * @brief Returns the area hyperbolic tangent of value.
         * 
         * @param value The value to take the area hyperbolic tangent of.
         * @return float The area hyperbolic tangent of value.
         */
        ENGINE_API extern float atanh(const float& value);
        /**
         * @brief Rounds value upwards to an integer value.
         * 
         * @param value The value to round.
         * @return int The smallest integer not less than value.
         */
        ENGINE_API extern int ceil(const float& value);

        /**
         * @brief Clamps value between min and max.
         * 
         * @tparam T The type to clamp.
         * @tparam enabled if T is a number type.
         * @param value The value to clamp.
         * @param min The minimum bound to clamp to.
         * @param max The maximum bound to clamp to.
         * @return T The clamped value.
         */
        template <typename T = float, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
        inline T clamp(const T& value, const T& min, const T& max) { return (value <= min) ? min : (value >= max) ? max : value; }
        /**
         * @brief Clamps value between 0 and 1.
         * 
         * @param value The value to clamp.
         * @return float The clamped value.
         */
        ENGINE_API extern float clamp(const float& value);
        
        /**
         * @brief Returns the number that is a power of 2 closest to value.
         * 
         * @param value The number to evaluate.
         * @return int The closest power of 2 to value.
         */
        ENGINE_API extern int closestPowerOf2(const float& value);
        
        // correlatedColorTempToRGB ? blackbodyColor
        
        /**
         * @brief Calculates the cosine of value.
         * 
         * @param value The angle in radians to evaluate.
         * @return float The cosine of value.
         */
        ENGINE_API extern float cos(const float& value);
        /**
         * @brief Calculates the hyperbolic cosine of value.
         * 
         * @param value The hyperbolic angle to evaluate.
         * @return float The hyperbolic cosine of value.
         */
        ENGINE_API extern float cosh(const float& value);
        /**
         * @brief Returns the shortest difference between two angles.
         * 
         * @param current The current angle in radians.
         * @param target The target angle in radians.
         * @return float The smallest angle between current and target in radians.
         */
        ENGINE_API extern float deltaAngle(const float& current, const float& target);
        /**
         * @brief Returns e raised to the power of value.
         * 
         * @param value The exponent to apply.
         * @return float Eulers number raised to value.
         */
        ENGINE_API extern float exp(const float& value);
        /**
         * @brief Rounds value downwards.
         * 
         * @param value The number to floor.
         * @return int The largest integer less than value.
         */
        ENGINE_API extern int floor(const float& value);
        /**
         * @brief Returns the remainder of value / denom.
         * 
         * @param value The numerator of the division.
         * @param denom The denominator of the division.
         * @return float The ramainder of value / denom.
         */
        ENGINE_API extern float fmod(const float& value, const float& denom);
        
        // gammaToLinearColor ?
        
        /**
         * @brief Returns the value t the would be used to produce value by linearly interpolating
         *        between a and b by t.
         * 
         * @param a The lower bound of the interpolation.
         * @param b The upper bound of the interpolation.
         * @param value The value produced by interpolation.
         * @return float The time t used to produce value.
         */
        ENGINE_API extern float invLerp(const float& a, const float& b, const float& value);
        /**
         * @brief Returns true if value is a power of 2.
         * 
         * @param value The number to evaluate.
         * @return true If value is a power of 2.
         * @return false If value is not a power of 2.
         */
        ENGINE_API extern bool isPowerOf2(const unsigned int& value);
        /**
         * @brief Linearly interpolates between two values a and b by a value t.
         * 
         * @tparam T The type to interpolate.
         * @param a The value represented at t = 0.
         * @param b The value represented at t = 1.
         * @param t The value used to interpolate between a and b. This value
         *          should be in a range of 0 to 1.
         * @return T The interpolated result.
         */
        template <typename T>
        inline T lerp(const T& a, const T& b, const T& t) { return a + t * (b - a); }
        
        // linearToGammaColor ?

        /**
         * @brief Evaluates the natural log of x.
         * 
         * @param x The number to evaluate.
         * @return float The natural log of x.
         */
        ENGINE_API extern float ln(const float& x);
        /**
         * @brief Evaluates the log with base b of x.
         * 
         * @param b The base of the logarithm.
         * @param x The number to evaluate.
         * @return float The log base b of x.
         */
        ENGINE_API extern float logb(const float& b, const float& x);
        /**
         * @brief Evaluates the log base 2 of x.
         * 
         * @param x The number to evaluate.
         * @return float The log base 2 of x.
         */
        ENGINE_API extern float log2(const float& x);
        /**
         * @brief Evaluates the log base 10 of x.
         * 
         * @param x The number to evaluate.
         * @return float The log base 10 of x.
         */
        ENGINE_API extern float log10(const float& x);

        #undef max
        #undef min

        /**
         * @brief Finds the maximum of the passed values.
         * 
         * @tparam T the type to evaluate
         * @param a The first number to compare.
         * @param b The second number to compare.
         * @return T The largest value provided.
         */
        template <typename T = float>
        inline T max(const T& a, const T& b) { return (a >= b) ? a : b; }
        /**
         * @brief Finds the maximum value within the passed list.
         * 
         * @tparam T the type to evaluate
         * @tparam enabled if T is a floating point type.
         * @param list The values to evaluate.
         * @return T The largest value provided.
         */
        template <typename T = float>
        inline T max(const std::initializer_list<T> list) { return std::max(list); }

        /**
         * @brief Finds the minimum of the passed values.
         * 
         * @tparam T the type to evaluate
         * @param a The first number to compare.
         * @param b The second number to compare.
         * @return T The smallest value provided.
         */
        template <typename T = float>
        inline T min(const T& a, const T& b) { return (a <= b) ? a : b; }
        /**
         * @brief Finds the minimum value within the passed list.
         * 
         * @tparam T the type to evaluate
         * @tparam enabled if T is a floating point type.
         * @param list The values to evaluate.
         * @return T The smallest value provided.
         */
        template <typename T = float>
        inline T min(const std::initializer_list<T> list) { return std::min(list); }
        /**
         * @brief Moves between two values at the specified rate.
         * 
         * @param current The current value.
         * @param target The target value.
         * @param rate The rate to move towards target.
         * @return float Current moved towards target by rate.
         */
        ENGINE_API extern float moveTowards(const float& current, const float& target, const float& rate);
        /**
         * @brief Moves between two angles at the specified rate.
         * 
         * @param current The current angle in radians.
         * @param target The target angle in radians.
         * @param rate The rate to move towards target.
         * @return float Current moved towards target by rate.
         */
        ENGINE_API extern float moveTowardsAngle(const float& current, const float& target, const float& rate);
        /**
         * @brief Returns the next power of 2 occuring after value.
         * 
         * @param value The number to evaluate.
         * @return int The next power of 2 after value.
         */
        ENGINE_API extern int nextPowerOf2(const float& value);
        /**
         * @brief Oscillates between 0 and length over time.
         * 
         * @param t The point in time.
         * @param length The length of the range to oscillate through.
         * @return float The value of the oscillation at time t.
         */
        ENGINE_API extern float pingpong(const float& t, const float& length);
        /**
         * @brief Calculates base raised to the power exp.
         * 
         * @param base The base value.
         * @param exp The exponent to apply.
         * @return float Base raised to the power exp.
         */
        ENGINE_API extern float pow(const float& base, const float& exp);
        /**
         * @brief Remaps value from a range of [min, max] to a range of [new_min, new_max]
         * 
         * @param value The original value.
         * @param min The original minimum of the range containing value.
         * @param max The original maximum of the range containing value.
         * @param new_min The new minimum of the range containing value.
         * @param new_max The new maximum of the range containing value.
         * @return float The number within the new range at the same position that value occupied in its original range.
         */
        ENGINE_API extern float remap(const float& value, const float& min, const float& max, const float& new_min, const float& new_max);
        /**
         * @brief Repeats the values 0 through length over time.
         * 
         * @param t The time value.
         * @param length The length of the repeating range.
         * @return float The value at time t.
         */
        ENGINE_API extern float repeat(const float& t, const float& length);
        /**
         * @brief Rounds value to the nearest integer.
         * 
         * @param value The value to round.
         * @return int The nearest integer to value.
         */
        ENGINE_API extern int round(const float& value);
        /**
         * @brief Returns a float representing the sign of value.
         * 
         * @param value The number to check.
         * @return float -1 or 1 depending on the sign of value.
         */
        ENGINE_API extern float sign(const float& value);
        /**
         * @brief Calculates the sine of value.
         * 
         * @param value The angle in radians to evaluate.
         * @return float The sine of value.
         */
        ENGINE_API extern float sin(const float& value);
        /**
         * @brief Calculates the hyperbolic sine of value.
         * 
         * @param value The hyperbolic angle to evaluate.
         * @return float The hyperbolic sine of value.
         */
        ENGINE_API extern float sinh(const float& value);
        /**
         * @brief Gradually moves towards target from current using a spring-damper function.
         * 
         * @param current The current value.
         * @param target The value being approached.
         * @param velocity The rate that target is being approached. This value is modified.
         * @param step The step size towards target.
         * @param spring_constant The spring constant applied.
         * @return float A new position that is closer than current to target.
         */
        ENGINE_API extern float smoothdamp(const float& current, const float& target, float* const velocity, const float& step, const float& spring_constant = 2.0f);
        /**
         * @brief Interpolates between a and b by t with smoothing at the limits.
         * 
         * @param a The value at t = 0.
         * @param b The value at t = 1.
         * @param t The position in the interpolation. Should be between 0 and 1.
         * @return float The interpolated value between a and b at time t.
         */
        ENGINE_API extern float smoothstep(const float& a, const float& b, const float& t);
        /**
         * @brief Calculates the square root of value.
         * 
         * @param value The value to find the square root of.
         * @return float The square root of value.
         */
        ENGINE_API extern float sqrt(const float& value);
        /**
         * @brief Calculates the tangent of value.
         * 
         * @param value The angle in radians to evaluate.
         * @return float The tangent of value.
         */
        ENGINE_API extern float tan(const float& value);
        /**
         * @brief Calculates the hyperbolic tangent of value.
         * 
         * @param value The hyperbolic angle to evaluate.
         * @return float The hyperbolic tangent of value.
         */
        ENGINE_API extern float tanh(const float& value);
        /**
         * @brief Converts the passed value into an angle between -180 and 180 degrees.
         *        The value is returned in radians between -pi and pi.
         * 
         * @param value The value to convert.
         * @return float The resulting angle in radians.
         */
        ENGINE_API extern float toAngle(const float& value);
        /**
         * @brief Converts the specified angle in radians to the same angle in degrees.
         * 
         * @param radians The angle in radians.
         * @return float The angle in degrees.
         */
        ENGINE_API extern float toDegrees(const float& radians);
        /**
         * @brief Converts the specified angle in degrees to the same angle in radians.
         * 
         * @param radians The angle in degrees.
         * @return float The angle in radians.
         */
        ENGINE_API extern float toRadians(const float& degrees);

        /**
         * @brief Truncates any decimal value from the passed number.
         * 
         * @param value The number to truncate.
         * @return int The number truncated to an int.
         */
        ENGINE_API extern int trunc(const float& value);
        /**
         * @brief Truncates any decimal value from the passed number.
         * 
         * @param value The number to truncate.
         * @return long int The number truncated to a long int.
         */
        ENGINE_API extern long int trunc(const double& value);

    }

}

#endif