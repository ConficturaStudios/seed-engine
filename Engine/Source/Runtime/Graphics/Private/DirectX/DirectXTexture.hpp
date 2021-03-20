/**
 * DirectXTexture.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_DIRECT_X_TEXTURE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_DIRECT_X_TEXTURE_H_

#include "GraphicsAPI.hpp"
#include "DirectX/DirectX.hpp"
#include "Texture.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API DirectXTexture {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for DirectXTexture objects.
             * @details Constructs a new DirectXTexture with default initialization for all members.
             */
            DirectXTexture();

            /**
             * @brief The copy constructor for DirectXTexture objects.
             * @details Constructs a new DirectXTexture by copying an existing DirectXTexture.
             */
            DirectXTexture(const DirectXTexture& ref) = default;
            
            /**
             * @brief The move constructor for DirectXTexture objects.
             * @details Constructs a new DirectXTexture by moving the data of a DirectXTexture into this object.
             */
            DirectXTexture(DirectXTexture&& ref) = default;

            /**
             * @brief The destructor for DirectXTexture objects.
             * @details Called when an instance of DirectXTexture is deleted.
             */
            virtual ~DirectXTexture();

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for DirectXTexture objects.
             * @details Reassigns the value of this object by copying the data of a DirectXTexture into this object.
             */
            DirectXTexture& operator=(const DirectXTexture& rhs) = default;

            /**
             * @brief The move assignment operator for DirectXTexture objects.
             * @details Reassigns the value of this object by moving the data of a DirectXTexture into this object.
             */
            DirectXTexture& operator=(DirectXTexture&& rhs) = default;

        protected:

        private:

    };

}

#endif