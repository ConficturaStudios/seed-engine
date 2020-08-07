/**
 * ISerializable.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_I_SERIALIZABLE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_I_SERIALIZABLE_H_

#include "CommonAPI.hpp"
#include <iostream>

namespace seedengine {

    /**
     * @brief An interface for objects that can be serialized into and deserialized from a byte stream.
     * @details An interface for objects that can be serialized into and deserialized from a byte stream.
     * 
     */
    class ENGINE_API ISerializable {

        public:

        // Functions

            /**
             * @brief Serializes this object into a stream.
             * 
             * @param target The output stream to write to.
             */
            virtual void serialize(std::ostream& target) const = 0;

            /**
             * @brief Deserializes the target from a stream.
             * 
             * @param source The source of the data to load in.
             */
            virtual void deserialize(std::istream& source) = 0;

        // Global IO operators

            friend std::ostream& operator<<(std::ostream& lhs, const ISerializable& rhs);

            friend std::istream& operator>>(std::istream& lhs, ISerializable& rhs);

    };

    std::ostream& operator<<(std::ostream& lhs, const ISerializable& rhs);

    std::istream& operator>>(std::istream& lhs, ISerializable& rhs);

}

#endif