#ifndef SEEDENGINE_INCLUDE_MATH_H_
#define SEEDENGINE_INCLUDE_MATH_H_

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <limits>
#include <stdlib.h>
#include <chrono>

namespace seedengine {

    namespace math {

        // The smallest floating point increment.
        const float EPSILON = std::numeric_limits<float>::epsilon();
        // Infinity.
        const float INF = std::numeric_limits<float>::infinity();
        // Negative Infinity.
        const float NEG_INF = -INF;
        // Pi (3.14159...).
        const float PI = (float)M_PI;
        // Euler's Number / The base of the natural logarithm.
        const float E = (float)M_E;
        // The conversion constant for converting degrees into radians.
        const float DEG2RAD = PI / 180.0f;
        // The conversion constant for converting radians into degrees.
        const float RAD2DEG = 180.0f / PI;

        // Is this number odd?
        // @param(const T&) value: The number to check.
        // @returns: True if the number is odd.
        template <typename T = int, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
        inline bool isOdd(const T& value) {
            return value & 1;
        }
        // Is this number odd?
        // @param(const float&) value: The number to check.
        // @returns: True if the number is odd.
        template <typename T = float, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
        inline bool isOdd(const T& value) {
            return (int)value % 2 == 1;
        }

        // Returns the absolute value of the passed number.
        // @param(const T&) value: The number to retrieve the absolute value of.
        // @returns: The absolute value of value.
        template <typename T = float, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
        inline T abs(const T& value) { return std::abs(value); }
        
        // Returns the arc-cosine of value. This is the angle in radians whose cosine is value.
        // @param(const float&) value: The value to take the arc-cosine of.
        // @returns: The angle in radians whose cosine is value.
        inline float acos(const float& value) { return std::acos(value); }
        // acosh
        inline float acosh(const float& value) { return std::acosh(value); }
        // approx
        inline bool approx(const float& a, const float& b) { return a + EPSILON >= b && a - EPSILON <= b; }
        // asin
        inline float asin(const float& value) { return std::asin(value); }
        // asinh
        inline float asinh(const float& value) { return std::asinh(value); }
        // atan
        inline float atan(const float& value) { return std::atan(value); }
        // atan2
        inline float atan2(const float& y, const float& x) { return std::atan2(y, x); }
        // atanh
        inline float atanh(const float& value) { return std::atanh(value); }
        // ceil
        inline int ceil(const float& value) { return (int)std::ceil(value); }
        // clamp
        template <typename T = float, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
        inline T clamp(const T& value, const T& min, const T& max) { return (value <= min) ? min : (value >= max) ? max : value; }
        // clamp01
        template <typename T = float, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
        inline T clamp(const T& value) { return (value <= 0) ? 0 : (value >= 1) ? 1 : value; }
        // closestPowerOf2 ?
        inline int closestPowerOf2(const float& value) { return (int)pow(2, round(log2(value))); }
        // correlatedColorTempToRGB ? blackbodyColor
        // cos
        inline float cos(const float& value) { return std::cos(value); }
        // cosh
        inline float cosh(const float& value) { return std::cosh(value); }
        // deltaAngle ?
        inline float deltaAngle(const float& current, const float& target) { return atan2(sin(target - current), cos(target - current)); }
        // exp
        inline float exp(const float& value) { return std::exp(value); }
        // floor
        inline int floor(const float& value) { return (int)std::floor(value); }
        // fmod
        inline float fmod(const float& value, const float& denom) { return std::fmod(value, denom); }
        // gammaToLinearColor ?
        // invLerp
        inline float invLerp(const float& a, const float& b, const float& value) { return (b - a == 0) ? 0 : (value - a) / (b - a); }
        // isPowerOf2
        inline bool isPowerOf2(const unsigned int& value) { return (value == 0) ? false : (value & (value - 1)) == 0; }
        // lerp
        inline float lerp(const float& a, const float& b, const float& t) { return a + t * (b - a); }
        // linearToGammaColor ?
        // ln
        inline float ln(const float& x) { return std::log(x); }
        // logb
        inline float logb(const float& b, const float& x) { return ln(x) / ln(b); }
        // log2
        inline float log2(const float& x) { return std::log2(x); }
        // log10
        inline float log10(const float& x) { return std::log10(x); }
        #undef max
        #undef min
        // max
        template <typename T = float, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
        inline T max(const T& a, const T& b) { return (a >= b) ? a : b; }
        // min
        template <typename T = float, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
        inline T min(const T& a, const T& b) { return (a <= b) ? a : b; }
        // moveTowards
        inline float moveTowards(const float& current, const float& target, const float& rate) {
            return (abs(target - current) <= rate) ? target : current + ( (target - current) / abs(target - current) ) * rate;
        }
        // moveTowardsAngle ?
        inline float moveTowardsAngle(const float& current, const float& target, const float& rate) {
            return (abs(target - current) <= rate) ? target : current + ((target - current) / abs(target - current)) * rate;
        }
        // nextPowerOf2
        inline int nextPowerOf2(const float& value) { return (int)pow(2, ceil(log2(value))); }
        // pingPong ?
        inline float pingpong(const float& t, const float& length) { return length - abs(fmod(t, 2 * length) - length); }
        // pow
        inline float pow(const float& base, const float& exp) { return std::pow(exp, exp); }
        // repeat
        inline float repeat(const float& t, const float& length) { return fmod(t, length); }
        // round
        inline int round(const float& value) { return (int)std::round(value); }
        // sign
        inline float sign(const float& value) { return value / abs(value); }
        // sin
        inline float sin(const float& value) { return std::sin(value); }
        // sinh
        inline float sinh(const float& value) { return std::sinh(value); }
        // smoothDamp
        inline float smoothdamp(const float& current, const float& target, float* const velocity, const float& step, const float& spring_constant = 2.0f) {
            *velocity += ( ( (target - current) * spring_constant ) + ( (*velocity) * -2.0f * sqrt(spring_constant) ) ) * step;
            return current + (*velocity) * step;
        }
        // smoothStep
        inline float smoothstep(const float& a, const float& b, const float& t) {
            float temp = clamp((t - a) / (b - a));
            return temp * temp * (3.0f - 2.0f * temp);
        }
        // sqrt
        inline float sqrt(const float& value) { return std::sqrt(value); }
        // tan
        inline float tan(const float& value) { return std::tan(value); }
        // tanh
        inline float tanh(const float& value) { return std::tanh(value); }
        // toAngle
        inline float toAngle(const float& value) { return deltaAngle(0.0f, value); }
        // toDegrees
        inline float toDegrees(const float& radians) { return radians * RAD2DEG; }
        // toRadians
        inline float toRadians(const float& degrees) { return degrees * DEG2RAD; }

        // Truncates any decimal value from the passed number.
        // @param(const float&) value: The number to truncate.
        // @returns: The number truncated to an int.
        inline int trunc(const float& value) {
            return (int)value;
        }
        // Truncates any decimal value from the passed number.
        // @param(const double&) value: The number to truncate.
        // @returns: The number truncated to a long int.
        inline long int trunc(const double& value) {
            return (long int)value;
        }

    }

}

#endif