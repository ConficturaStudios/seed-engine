/**
 * VulkanShader.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_VULKAN_SHADER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_VULKAN_SHADER_H_

#include "GraphicsAPI.hpp"
#include "Vulkan/Vulkan.hpp"
#include "Shader.hpp"

namespace seedengine {

    #if ENGINE_GRAPHICS_VULKAN

    /**
     * @brief
     * @details
     * 
     */
    class VulkanShader : public Shader {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for VulkanShader objects.
             * @details Constructs a new VulkanShader with default initialization for all members.
             */
            VulkanShader();

            /**
             * @brief The copy constructor for VulkanShader objects.
             * @details Constructs a new VulkanShader by copying an existing VulkanShader.
             */
            VulkanShader(const VulkanShader& ref) = default;
            
            /**
             * @brief The move constructor for VulkanShader objects.
             * @details Constructs a new VulkanShader by moving the data of a VulkanShader into this object.
             */
            VulkanShader(VulkanShader&& ref) = default;

            /**
             * @brief The destructor for VulkanShader objects.
             * @details Called when an instance of VulkanShader is deleted.
             */
            virtual ~VulkanShader();

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for VulkanShader objects.
             * @details Reassigns the value of this object by copying the data of a VulkanShader into this object.
             */
            VulkanShader& operator=(const VulkanShader& rhs) = default;

            /**
             * @brief The move assignment operator for VulkanShader objects.
             * @details Reassigns the value of this object by moving the data of a VulkanShader into this object.
             */
            VulkanShader& operator=(VulkanShader&& rhs) = default;

        protected:

        private:

    };

    #else

    class VulkanShader : public Shader { };

    #endif

}

#endif