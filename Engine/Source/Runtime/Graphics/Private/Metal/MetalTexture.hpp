/**
 * MetalTexture.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_METAL_TEXTURE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_METAL_TEXTURE_H_

#include "GraphicsAPI.hpp"
#include "Metal/Metal.hpp"
#include "Texture.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API MetalTexture {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for MetalTexture objects.
             * @details Constructs a new MetalTexture with default initialization for all members.
             */
            MetalTexture();

            /**
             * @brief The copy constructor for MetalTexture objects.
             * @details Constructs a new MetalTexture by copying an existing MetalTexture.
             */
            MetalTexture(const MetalTexture& ref) = default;
            
            /**
             * @brief The move constructor for MetalTexture objects.
             * @details Constructs a new MetalTexture by moving the data of a MetalTexture into this object.
             */
            MetalTexture(MetalTexture&& ref) = default;

            /**
             * @brief The destructor for MetalTexture objects.
             * @details Called when an instance of MetalTexture is deleted.
             */
            virtual ~MetalTexture();

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for MetalTexture objects.
             * @details Reassigns the value of this object by copying the data of a MetalTexture into this object.
             */
            MetalTexture& operator=(const MetalTexture& rhs) = default;

            /**
             * @brief The move assignment operator for MetalTexture objects.
             * @details Reassigns the value of this object by moving the data of a MetalTexture into this object.
             */
            MetalTexture& operator=(MetalTexture&& rhs) = default;

        protected:

        private:

    };

}

#endif