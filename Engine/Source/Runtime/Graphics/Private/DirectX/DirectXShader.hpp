/**
 * DirectXShader.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_DIRECT_X_SHADER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_DIRECT_X_SHADER_H_

#include "GraphicsAPI.hpp"
#include "DirectX/DirectX.hpp"
#include "Shader.hpp"

namespace seedengine {

    #if ENGINE_GRAPHICS_DIRECTX

    /**
     * @brief
     * @details
     * 
     */
    class DirectXShader : public Shader {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for DirectXShader objects.
             * @details Constructs a new DirectXShader with default initialization for all members.
             */
            DirectXShader();

            /**
             * @brief The copy constructor for DirectXShader objects.
             * @details Constructs a new DirectXShader by copying an existing DirectXShader.
             */
            DirectXShader(const DirectXShader& ref) = default;
            
            /**
             * @brief The move constructor for DirectXShader objects.
             * @details Constructs a new DirectXShader by moving the data of a DirectXShader into this object.
             */
            DirectXShader(DirectXShader&& ref) = default;

            /**
             * @brief The destructor for DirectXShader objects.
             * @details Called when an instance of DirectXShader is deleted.
             */
            virtual ~DirectXShader();

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for DirectXShader objects.
             * @details Reassigns the value of this object by copying the data of a DirectXShader into this object.
             */
            DirectXShader& operator=(const DirectXShader& rhs) = default;

            /**
             * @brief The move assignment operator for DirectXShader objects.
             * @details Reassigns the value of this object by moving the data of a DirectXShader into this object.
             */
            DirectXShader& operator=(DirectXShader&& rhs) = default;

        protected:

        private:

    };

    #else

    class DirectXShader : public Shader { };

    #endif

}

#endif