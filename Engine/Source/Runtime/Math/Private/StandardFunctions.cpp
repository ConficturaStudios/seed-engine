/**
 * StandardFunctions.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "StandardFunctions.hpp"

namespace seedengine {

    namespace math {

        //ENGINE_API const float EPSILON = std::numeric_limits<float>::epsilon();
        //ENGINE_API const float INF = std::numeric_limits<float>::infinity();
        //ENGINE_API const float NEG_INF = -INF;
        //ENGINE_API const float PI = (float)M_PI;
        //ENGINE_API const float E = (float)M_E;
        //ENGINE_API const float DEG2RAD = PI / 180.0f;
        //ENGINE_API const float RAD2DEG = 180.0f / PI;
        
        ENGINE_API float acos(const float& value) { return std::acos(value); }
        ENGINE_API float acosh(const float& value) { return std::acosh(value); }
        ENGINE_API bool approx(const float& a, const float& b) { return a + EPSILON >= b && a - EPSILON <= b; }
        ENGINE_API float asin(const float& value) { return std::asin(value); }
        ENGINE_API float asinh(const float& value) { return std::asinh(value); }
        ENGINE_API float atan(const float& value) { return std::atan(value); }
        ENGINE_API float atan2(const float& y, const float& x) { return std::atan2(y, x); }
        ENGINE_API float atanh(const float& value) { return std::atanh(value); }
        ENGINE_API int ceil(const float& value) { return (int)std::ceil(value); }

        ENGINE_API float clamp(const float& value) { return (value <= 0) ? 0 : (value >= 1) ? 1 : value; }
        
        ENGINE_API int closestPowerOf2(const float& value) { return (int)pow(2.0f, (float)round(log2(value))); }
        
        // correlatedColorTempToRGB ? blackbodyColor
        
        ENGINE_API float cos(const float& value) { return std::cos(value); }
        ENGINE_API float cosh(const float& value) { return std::cosh(value); }
        ENGINE_API float deltaAngle(const float& current, const float& target) { return atan2(sin(target - current), cos(target - current)); }
        ENGINE_API float exp(const float& value) { return std::exp(value); }
        ENGINE_API int floor(const float& value) { return (int)std::floor(value); }
        ENGINE_API float fmod(const float& value, const float& denom) { return std::fmod(value, denom); }
        ENGINE_API float invLerp(const float& a, const float& b, const float& value) { return (b - a == 0) ? 0 : (value - a) / (b - a); }
        ENGINE_API bool isPowerOf2(const unsigned int& value) { return (value == 0) ? false : (value & (value - 1)) == 0; }
        
        // linearToGammaColor ?

        ENGINE_API float ln(const float& x) { return std::log(x); }
        ENGINE_API float logb(const float& b, const float& x) { return ln(x) / ln(b); }
        ENGINE_API float log2(const float& x) { return std::log2(x); }
        ENGINE_API float log10(const float& x) { return std::log10(x); }

        ENGINE_API float moveTowards(const float& current, const float& target, const float& rate) {
            return (abs(target - current) <= rate) ? target : current + ( (target - current) / abs(target - current) ) * rate;
        }
        ENGINE_API float moveTowardsAngle(const float& current, const float& target, const float& rate) {
            return (abs(target - current) <= rate) ? target : current + ((target - current) / abs(target - current)) * rate;
        }
        ENGINE_API int nextPowerOf2(const float& value) { return (int)pow(2.0f, (float)ceil(log2(value))); }
        ENGINE_API float pingpong(const float& t, const float& length) { return length - abs(fmod(t, 2 * length) - length); }
        ENGINE_API float pow(const float& base, const float& exp) { return std::pow(base, exp); }
        ENGINE_API float remap(const float& value, const float& min, const float& max, const float& new_min, const float& new_max) {
            return new_min + (invLerp(min, max, value) * (new_max - new_min));
        }
        ENGINE_API float repeat(const float& t, const float& length) { return fmod(t, length); }
        ENGINE_API int round(const float& value) { return (int)std::round(value); }
        ENGINE_API float sign(const float& value) { return value / abs(value); }
        ENGINE_API float sin(const float& value) { return std::sin(value); }
        ENGINE_API float sinh(const float& value) { return std::sinh(value); }
        ENGINE_API float smoothdamp(const float& current, const float& target, float* const velocity, const float& step, const float& spring_constant) {
            *velocity += ( ( (target - current) * spring_constant ) + ( (*velocity) * -2.0f * sqrt(spring_constant) ) ) * step;
            return current + (*velocity) * step;
        }
        ENGINE_API float smoothstep(const float& a, const float& b, const float& t) {
            float temp = clamp((t - a) / (b - a));
            return temp * temp * (3.0f - 2.0f * temp);
        }
        ENGINE_API float sqrt(const float& value) { return std::sqrt(value); }
        ENGINE_API float tan(const float& value) { return std::tan(value); }
        ENGINE_API float tanh(const float& value) { return std::tanh(value); }
        ENGINE_API float toAngle(const float& value) { return deltaAngle(0.0f, value); }
        ENGINE_API float toDegrees(const float& radians) { return radians * RAD2DEG; }
        ENGINE_API float toRadians(const float& degrees) { return degrees * DEG2RAD; }

        ENGINE_API int trunc(const float& value) {
            return (int)value;
        }
        ENGINE_API long int trunc(const double& value) {
            return (long int)value;
        }

    }

}