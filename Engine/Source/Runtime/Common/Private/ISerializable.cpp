/**
 * ISerializable.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "CommonAPI.hpp"
#include "ISerializable.hpp"

namespace seedengine {

    std::ostream& operator<<(std::ostream& lhs, const ISerializable& rhs) {
        rhs.serialize(lhs);
        return lhs;
    }

    std::istream& operator>>(std::istream& lhs, ISerializable& rhs) {
        rhs.deserialize(lhs);
        return lhs;
    }

}