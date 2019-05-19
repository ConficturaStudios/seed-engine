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
        const float EPSILON = std::numeric_limits::epsilon();
        // Infinity.
        const float INF = std::numeric_limits::infinity();
        // Negative Infinity.
        const float NEG_INF = -INF;
        // Pi (3.14159...).
        const float PI = M_PI;
        // Euler's Number / The base of the natural logarithm.
        const float E = M_E;
        // The conversion constant for converting degrees into radians.
        const float DEG2RAD = PI / 180.0f;
        // The conversion constant for converting radians into degrees.
        const float RAD2DEG = 180.0f / PI;

        // Is this number odd?
        // @param(const int) num: The number to check.
        // @returns: True if the number is odd.
        inline bool isOdd(const int num) {
            return num & 1;
        }
        // Is this number odd?
        // @param(const float) num: The number to check.
        // @returns: True if the number is odd.
        inline bool isOdd(const float num) {
            return (int)num % 2 == 1;
        }
        // Is this number odd?
        // @param(const double) num: The number to check.
        // @returns: True if the number is odd.
        inline bool isOdd(const double num) {
            return (long int)num % 2 == 1;
        }

        // Swaps the values stored in two int references
        // @param(int&) a: The first number to swap.
        // @param(int&) b: The second number to swap.
        inline void swap(int& a, int& b) {
            a ^= b;
            b ^= a;
            a ^= b;
        }
        // Swaps the values stored in two int references
        // @param(float&) a: The first number to swap.
        // @param(float&) b: The second number to swap.
        inline void swap(float& a, float& b) {
            a ^= b;
            b ^= a;
            a ^= b;
        }
        // Swaps the values stored in two int references
        // @param(double&) a: The first number to swap.
        // @param(double&) b: The second number to swap.
        inline void swap(double& a, double& b) {
            a ^= b;
            b ^= a;
            a ^= b;
        }

        // Returns the absolute value of the passed number.
        // @param(const int) num: The number to retrieve the absolute value of.
        // @returns: The absolute value of num.
        inline int abs(const int num) { return std::abs(num); }
        // Returns the absolute value of the passed number.
        // @param(const float) num: The number to retrieve the absolute value of.
        // @returns: The absolute value of num.
        inline float abs(const float num) { return std::abs(num); }
        // Returns the absolute value of the passed number.
        // @param(const double) num: The number to retrieve the absolute value of.
        // @returns: The absolute value of num.
        inline double abs(const double num) { return std::abs(num); }
        
        // acos
        inline float acos(const float& num) { return std::acos(num); }
        // acosh
        inline float acosh(const float& num) { return std::acosh(num); }
        // approx
        inline bool approx(const float& a, const float& b) { return a + EPSILON >= b && a - EPSILON <= b; }
        // asin
        inline float asin(const float& num) { return std::asin(num); }
        // asinh
        inline float asinh(const float& num) { return std::asinh(num); }
        // atan
        inline float atan(const float& num) { return std::atan(num); }
        // atan2
        inline float atan2(const float& y, const float& x) { return std::atan2(y, x); }
        // atanh
        inline float atanh(const float& num) { return std::atanh(num); }
        // ceil
        inline int ceil(const float& num) { return std::ceil(num); }
        // clamp
        inline float clamp(const float& num, const float& min, const float& max) { return (num <= min) ? min : (num >= max) ? max : num; }
        // clamp01
        inline float clamp(const float& num) { return (num <= 0.0f) ? 0.0f : (num >= 1.0f) ? 1.0f : num; }
        // closestPowerOf2 ?
        // correlatedColorTempToRGB ? blackbodyColor
        // cos
        inline float cos(const float& num) { return std::cos(num); }
        // cosh
        inline float cosh(const float& num) { return std::cosh(num); }
        // deltaAngle ?
        inline float deltaAngle(const float& current, const float& target) {
            //TODO: Redo deltaAngle function
            float a = fmod(current, 360.0f);
            float b = fmod(target, 360.0f);
            return (abs(a - b) <= 180.0f) ? b - a : 360 - b - a;
        }
        // exp
        inline float exp(const float& num) { return std::exp(num); }
        // floor
        inline int floor(const float& num) { return std::floor(num); }
        // fmod
        inline float fmod(const float& num, const float& denom) { return std::fmod(num, denom); }
        // gammaToLinearColor ?
        // invLerp
        inline float invLerp(const float& a, const float& b, const float& value) { return (value - a) / (b - a); }
        // isPowerOf2 ?
        // lerp
        inline float lerp(const float& a, const float& b, const float& t) { return a + t * (b - a); }
        // lerpAngle ?
        // linearToGammaColor ?
        // ln
        inline float ln(const float& x) { return std::log(x); }
        // logb
        inline float logb(const float& b, const float& x) { return ln(x) / ln(b); }
        // log2
        inline float log2(const float& x) { return std::log2(x); }
        // log10
        inline float log10(const float& x) { return std::log10(x); }
        // max
        inline float max(const float& a, const float& b) { return (a >= b) ? a : b; }
        // min
        inline float min(const float& a, const float& b) { return (a <= b) ? a : b; }
        // moveTowards
        inline float moveTowards(const float& current, const float& target, const float& rate) {
            return (abs(target - current) <= rate) ? target : a + sign(target - current) * rate;
        }
        // moveTowardsAngle ?
        inline float moveTowardsAngle(const float& current, const float& target, const float& rate) {
            return (abs(target - current) <= rate) ? target : a + rate;
        }
        // nextPowerOf2 ?
        inline float nextPowerOf2(const float& num) { return pow(2, log2(n)); }
        // pingPong ?
        inline float pingpong(const float& t, const float& length) { return length - abs(fmod(t, 2 * length) - length); }
        // pow
        inline float pow(const float& base, const float& exp) { return std::pow(exp, exp); }
        // repeat
        inline float repeat(const float& t, const float& length) { return fmod(t, length); }
        // round
        inline int round(const float& num) { return std::round(num); }
        // sign
        inline float sign(const float& num) { return num / abs(num); }
        // sin
        inline float sin(const float& num) { return std::sin(num); }
        // sinh
        inline float sinh(const float& num) { return std::sinh(num); }
        // smoothDamp
        // smoothDampAngle
        // smoothStep
        // sqrt
        inline float sqrt(const float& num) { return std::sqrt(num); }
        // tan
        inline float tan(const float& num) { return std::tan(num); }
        // tanh
        inline float tanh(const float& num) { return std::tanh(num); }

        // Truncates any decimal value from the passed number.
        // @param(const float) num: The number to truncate.
        // @returns: The number truncated to an int.
        inline int trunc(const float num) {
            return (int)num;
        }
        // Truncates any decimal value from the passed number.
        // @param(const double) num: The number to truncate.
        // @returns: The number truncated to a long int.
        inline long int trunc(const double num) {
            return (long int)num;
        }

    }

}

#endif