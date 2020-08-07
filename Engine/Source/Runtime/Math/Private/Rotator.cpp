/**
 * Rotator.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Rotator.hpp"
#include "Quaternion.hpp"

namespace seedengine {

    // Comparison Operators

    bool Rotator::operator==(const Rotator& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool Rotator::operator!=(const Rotator& rhs) const {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }

    // Cast Operators

    Rotator::operator Quaternion() const {
        float x_r = math::toRadians(x);
        float y_r = math::toRadians(y);
        float z_r = math::toRadians(z);
        float cz = math::cos(z_r * 0.5f);
        float sz = math::sin(z_r * 0.5f);
        float cy = math::cos(y_r * 0.5f);
        float sy = math::sin(y_r * 0.5f);
        float cx = math::cos(x_r * 0.5f);
        float sx = math::sin(x_r * 0.5f);

        return Quaternion(
            cx * cy * cz + sx * sy * sz,
            sx * cy * cz - cx * sy * sz,
            cx * sy * cz + sx * cy * sz,
            cx * cy * sz - sx * sy * cz
        );
    }

    Rotator::operator std::string() const {
        std::stringstream ss("");
        ss << "(";
        for (int i = 0; i < 3; i++) {
            ss << this->buffer[i];
            if (i < 2) ss << ", ";
        }
        ss << ") deg";
        return ss.str();
    }

    // Global IO operators

    ENGINE_API std::ostream& operator<<(std::ostream& os, const Rotator& rhs) {
        os << (std::string)rhs;
        return os;
    }

}