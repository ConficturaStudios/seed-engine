/**
 * Rotator.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_MATH_ROTATOR_H_
#define SEEDENGINE_INCLUDE_RUNTIME_MATH_ROTATOR_H_

#include "MathAPI.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "StandardFunctions.hpp"

namespace seedengine {

    class Quaternion;

    /**
     * @brief A euler angle based rotator.
     * @details A euler angle based rotator with x, y, and z rotation defined with the right hand rule.
     * 
     * @see Quaternion
     */
    struct ENGINE_API Rotator {

        public:

        // Properties

            union {
                /** An accessable buffer of the rotation values. */
                float buffer[3];
                struct {
                    /** Rotation about the x axis in degrees. */
                    float x;
                    /** Rotation about the y axis in degrees. */
                    float y;
                    /** Rotation about the z axis in degrees. */
                    float z;
                };
            };

        // Comparison Operators

            bool operator==(const Rotator& rhs) const;

            bool operator!=(const Rotator& rhs) const;

        // Cast Operators
        
            operator Quaternion() const;

            operator std::string() const;

        // IO Operators

            friend ENGINE_API std::ostream& operator<<(std::ostream& os, const Rotator& rhs);

    };

    // Global IO operators

    ENGINE_API std::ostream& operator<<(std::ostream& os, const Rotator& rhs);

}

#endif