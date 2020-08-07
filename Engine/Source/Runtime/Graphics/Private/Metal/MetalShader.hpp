/**
 * MetalShader.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_METAL_SHADER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_METAL_SHADER_H_

#include "GraphicsAPI.hpp"
#include "Metal.hpp"
#include "Shader.hpp"

namespace seedengine {

    #if ENGINE_GRAPHICS_METAL

    /**
     * @brief
     * @details
     * 
     */
    class MetalShader : public Shader {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for MetalShader objects.
             * @details Constructs a new MetalShader with default initialization for all members.
             */
            MetalShader();

            /**
             * @brief The copy constructor for MetalShader objects.
             * @details Constructs a new MetalShader by copying an existing MetalShader.
             */
            MetalShader(const MetalShader& ref) = default;
            
            /**
             * @brief The move constructor for MetalShader objects.
             * @details Constructs a new MetalShader by moving the data of a MetalShader into this object.
             */
            MetalShader(MetalShader&& ref) = default;

            /**
             * @brief The destructor for MetalShader objects.
             * @details Called when an instance of MetalShader is deleted.
             */
            virtual ~MetalShader();

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for MetalShader objects.
             * @details Reassigns the value of this object by copying the data of a MetalShader into this object.
             */
            MetalShader& operator=(const MetalShader& rhs) = default;

            /**
             * @brief The move assignment operator for MetalShader objects.
             * @details Reassigns the value of this object by moving the data of a MetalShader into this object.
             */
            MetalShader& operator=(MetalShader&& rhs) = default;

        protected:

        private:

    };

    #else

    class MetalShader : public Shader { };

    #endif

}

#endif