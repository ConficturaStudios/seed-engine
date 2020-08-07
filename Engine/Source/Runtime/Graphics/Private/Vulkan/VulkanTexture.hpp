/**
 * VulkanTexture.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_VULKAN_TEXTURE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_VULKAN_TEXTURE_H_

#include "GraphicsAPI.hpp"
#include "Vulkan.hpp"
#include "Texture.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API VulkanTexture {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for VulkanTexture objects.
             * @details Constructs a new VulkanTexture with default initialization for all members.
             */
            VulkanTexture();

            /**
             * @brief The copy constructor for VulkanTexture objects.
             * @details Constructs a new VulkanTexture by copying an existing VulkanTexture.
             */
            VulkanTexture(const VulkanTexture& ref) = default;
            
            /**
             * @brief The move constructor for VulkanTexture objects.
             * @details Constructs a new VulkanTexture by moving the data of a VulkanTexture into this object.
             */
            VulkanTexture(VulkanTexture&& ref) = default;

            /**
             * @brief The destructor for VulkanTexture objects.
             * @details Called when an instance of VulkanTexture is deleted.
             */
            virtual ~VulkanTexture();

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for VulkanTexture objects.
             * @details Reassigns the value of this object by copying the data of a VulkanTexture into this object.
             */
            VulkanTexture& operator=(const VulkanTexture& rhs) = default;

            /**
             * @brief The move assignment operator for VulkanTexture objects.
             * @details Reassigns the value of this object by moving the data of a VulkanTexture into this object.
             */
            VulkanTexture& operator=(VulkanTexture&& rhs) = default;

        protected:

        private:

    };

}

#endif