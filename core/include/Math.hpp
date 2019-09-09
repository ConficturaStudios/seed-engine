#ifndef SEEDENGINE_INCLUDE_MATH_H_
#define SEEDENGINE_INCLUDE_MATH_H_

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
        inline float acos(const float& value) { return std::acos(value); }
        /**
         * @brief Returns the nonnegative area hyperbolic cosine of value.
         * 
         * @param value The value to take the area hyperbolic cosine of.
         * @return float The nonnegative area hyperbolic cosine of value.
         */
        inline float acosh(const float& value) { return std::acosh(value); }
        /**
         * @brief Checks if the two values a and b are approximately equal.
         * 
         * @param a The value to check.
         * @param b The value to check against.
         * @return true If a is approximately equal to b.
         * @return false If a is not approximately equal to b.
         */
        inline bool approx(const float& a, const float& b) { return a + EPSILON >= b && a - EPSILON <= b; }
        /**
         * @brief Returns the arc-sine of value.
         * 
         * @param value The value to take the arc-sine of.
         * @return float The angle in radians whose sine is value.
         */
        inline float asin(const float& value) { return std::asin(value); }
        /**
         * @brief Returns the area hyperbolic sine of value.
         * 
         * @param value The value to take the area hyperbolic sine of.
         * @return float The area hyperbolic sine of value.
         */
        inline float asinh(const float& value) { return std::asinh(value); }
        /**
         * @brief Returns the arc-tangent of value.
         * 
         * @param value The value to take the arc-tangent of.
         * @return float The angle in radians whose tangent is value.
         */
        inline float atan(const float& value) { return std::atan(value); }
        /**
         * @brief Returns the arc-tangent of y / x.
         * 
         * @param y The numerator of the ratio to evaluate.
         * @param x The denominator of the ratio to evaluate.
         * @return float The angle in radians whose tangent is y / x.
         */
        inline float atan2(const float& y, const float& x) { return std::atan2(y, x); }
        /**
         * @brief Returns the area hyperbolic tangent of value.
         * 
         * @param value The value to take the area hyperbolic tangent of.
         * @return float The area hyperbolic tangent of value.
         */
        inline float atanh(const float& value) { return std::atanh(value); }
        /**
         * @brief Rounds value upwards to an integer value.
         * 
         * @param value The value to round.
         * @return int The smallest integer not less than value.
         */
        inline int ceil(const float& value) { return (int)std::ceil(value); }

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
        inline float clamp(const float& value) { return (value <= 0) ? 0 : (value >= 1) ? 1 : value; }
        
        /**
         * @brief Returns the number that is a power of 2 closest to value.
         * 
         * @param value The number to evaluate.
         * @return int The closest power of 2 to value.
         */
        inline int closestPowerOf2(const float& value) { return (int)pow(2, round(log2(value))); }
        
        // correlatedColorTempToRGB ? blackbodyColor
        
        /**
         * @brief Calculates the cosine of value.
         * 
         * @param value The angle in radians to evaluate.
         * @return float The cosine of value.
         */
        inline float cos(const float& value) { return std::cos(value); }
        /**
         * @brief Calculates the hyperbolic cosine of value.
         * 
         * @param value The hyperbolic angle to evaluate.
         * @return float The hyperbolic cosine of value.
         */
        inline float cosh(const float& value) { return std::cosh(value); }
        /**
         * @brief Returns the shortest difference between two angles.
         * 
         * @param current The current angle in radians.
         * @param target The target angle in radians.
         * @return float The smallest angle between current and target in radians.
         */
        inline float deltaAngle(const float& current, const float& target) { return atan2(sin(target - current), cos(target - current)); }
        /**
         * @brief Returns e raised to the power of value.
         * 
         * @param value The exponent to apply.
         * @return float Eulers number raised to value.
         */
        inline float exp(const float& value) { return std::exp(value); }
        /**
         * @brief Rounds value downwards.
         * 
         * @param value The number to floor.
         * @return int The largest integer less than value.
         */
        inline int floor(const float& value) { return (int)std::floor(value); }
        /**
         * @brief Returns the remainder of value / denom.
         * 
         * @param value The numerator of the division.
         * @param denom The denominator of the division.
         * @return float The ramainder of value / denom.
         */
        inline float fmod(const float& value, const float& denom) { return std::fmod(value, denom); }
        
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
        inline float invLerp(const float& a, const float& b, const float& value) { return (b - a == 0) ? 0 : (value - a) / (b - a); }
        /**
         * @brief Returns true if value is a power of 2.
         * 
         * @param value The number to evaluate.
         * @return true If value is a power of 2.
         * @return false If value is not a power of 2.
         */
        inline bool isPowerOf2(const unsigned int& value) { return (value == 0) ? false : (value & (value - 1)) == 0; }
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
        inline float ln(const float& x) { return std::log(x); }
        /**
         * @brief Evaluates the log with base b of x.
         * 
         * @param b The base of the logarithm.
         * @param x The number to evaluate.
         * @return float The log base b of x.
         */
        inline float logb(const float& b, const float& x) { return ln(x) / ln(b); }
        /**
         * @brief Evaluates the log base 2 of x.
         * 
         * @param x The number to evaluate.
         * @return float The log base 2 of x.
         */
        inline float log2(const float& x) { return std::log2(x); }
        /**
         * @brief Evaluates the log base 10 of x.
         * 
         * @param x The number to evaluate.
         * @return float The log base 10 of x.
         */
        inline float log10(const float& x) { return std::log10(x); }

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
        inline float moveTowards(const float& current, const float& target, const float& rate) {
            return (abs(target - current) <= rate) ? target : current + ( (target - current) / abs(target - current) ) * rate;
        }
        /**
         * @brief Moves between two angles at the specified rate.
         * 
         * @param current The current angle in radians.
         * @param target The target angle in radians.
         * @param rate The rate to move towards target.
         * @return float Current moved towards target by rate.
         */
        inline float moveTowardsAngle(const float& current, const float& target, const float& rate) {
            return (abs(target - current) <= rate) ? target : current + ((target - current) / abs(target - current)) * rate;
        }
        /**
         * @brief Returns the next power of 2 occuring after value.
         * 
         * @param value The number to evaluate.
         * @return int The next power of 2 after value.
         */
        inline int nextPowerOf2(const float& value) { return (int)pow(2, ceil(log2(value))); }
        /**
         * @brief Oscillates between 0 and length over time.
         * 
         * @param t The point in time.
         * @param length The length of the range to oscillate through.
         * @return float The value of the oscillation at time t.
         */
        inline float pingpong(const float& t, const float& length) { return length - abs(fmod(t, 2 * length) - length); }
        /**
         * @brief Calculates base raised to the power exp.
         * 
         * @param base The base value.
         * @param exp The exponent to apply.
         * @return float Base raised to the power exp.
         */
        inline float pow(const float& base, const float& exp) { return std::pow(base, exp); }
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
        inline float remap(const float& value, const float& min, const float& max, const float& new_min, const float& new_max) {
            return new_min + (invLerp(min, max, value) * (new_max - new_min));
        }
        /**
         * @brief Repeats the values 0 through length over time.
         * 
         * @param t The time value.
         * @param length The length of the repeating range.
         * @return float The value at time t.
         */
        inline float repeat(const float& t, const float& length) { return fmod(t, length); }
        /**
         * @brief Rounds value to the nearest integer.
         * 
         * @param value The value to round.
         * @return int The nearest integer to value.
         */
        inline int round(const float& value) { return (int)std::round(value); }
        /**
         * @brief Returns a float representing the sign of value.
         * 
         * @param value The number to check.
         * @return float -1 or 1 depending on the sign of value.
         */
        inline float sign(const float& value) { return value / abs(value); }
        /**
         * @brief Calculates the sine of value.
         * 
         * @param value The angle in radians to evaluate.
         * @return float The sine of value.
         */
        inline float sin(const float& value) { return std::sin(value); }
        /**
         * @brief Calculates the hyperbolic sine of value.
         * 
         * @param value The hyperbolic angle to evaluate.
         * @return float The hyperbolic sine of value.
         */
        inline float sinh(const float& value) { return std::sinh(value); }
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
        inline float smoothdamp(const float& current, const float& target, float* const velocity, const float& step, const float& spring_constant = 2.0f) {
            *velocity += ( ( (target - current) * spring_constant ) + ( (*velocity) * -2.0f * sqrt(spring_constant) ) ) * step;
            return current + (*velocity) * step;
        }
        /**
         * @brief Interpolates between a and b by t with smoothing at the limits.
         * 
         * @param a The value at t = 0.
         * @param b The value at t = 1.
         * @param t The position in the interpolation. Should be between 0 and 1.
         * @return float The interpolated value between a and b at time t.
         */
        inline float smoothstep(const float& a, const float& b, const float& t) {
            float temp = clamp((t - a) / (b - a));
            return temp * temp * (3.0f - 2.0f * temp);
        }
        /**
         * @brief Calculates the square root of value.
         * 
         * @param value The value to find the square root of.
         * @return float The square root of value.
         */
        inline float sqrt(const float& value) { return std::sqrt(value); }
        /**
         * @brief Calculates the tangent of value.
         * 
         * @param value The angle in radians to evaluate.
         * @return float The tangent of value.
         */
        inline float tan(const float& value) { return std::tan(value); }
        /**
         * @brief Calculates the hyperbolic tangent of value.
         * 
         * @param value The hyperbolic angle to evaluate.
         * @return float The hyperbolic tangent of value.
         */
        inline float tanh(const float& value) { return std::tanh(value); }
        /**
         * @brief Converts the passed value into an angle between -180 and 180 degrees.
         *        The value is returned in radians between -pi and pi.
         * 
         * @param value The value to convert.
         * @return float The resulting angle in radians.
         */
        inline float toAngle(const float& value) { return deltaAngle(0.0f, value); }
        /**
         * @brief Converts the specified angle in radians to the same angle in degrees.
         * 
         * @param radians The angle in radians.
         * @return float The angle in degrees.
         */
        inline float toDegrees(const float& radians) { return radians * RAD2DEG; }
        /**
         * @brief Converts the specified angle in degrees to the same angle in radians.
         * 
         * @param radians The angle in degrees.
         * @return float The angle in radians.
         */
        inline float toRadians(const float& degrees) { return degrees * DEG2RAD; }

        /**
         * @brief Truncates any decimal value from the passed number.
         * 
         * @param value The number to truncate.
         * @return int The number truncated to an int.
         */
        inline int trunc(const float& value) {
            return (int)value;
        }
        /**
         * @brief Truncates any decimal value from the passed number.
         * 
         * @param value The number to truncate.
         * @return long int The number truncated to a long int.
         */
        inline long int trunc(const double& value) {
            return (long int)value;
        }

    }

}

#endif