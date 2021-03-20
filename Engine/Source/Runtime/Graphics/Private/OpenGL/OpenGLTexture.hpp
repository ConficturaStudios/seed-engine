/**
 * OpenGLTexture.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_OPEN_GL_TEXTURE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_OPEN_GL_TEXTURE_H_

#include "GraphicsAPI.hpp"
#include "OpenGL/OpenGL.hpp"
#include "Texture.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class OpenGLTexture {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for OpenGLTexture objects.
             * @details Constructs a new OpenGLTexture with default initialization for all members.
             */
            OpenGLTexture();

            /**
             * @brief The copy constructor for OpenGLTexture objects.
             * @details Constructs a new OpenGLTexture by copying an existing OpenGLTexture.
             */
            OpenGLTexture(const OpenGLTexture& ref) = default;
            
            /**
             * @brief The move constructor for OpenGLTexture objects.
             * @details Constructs a new OpenGLTexture by moving the data of a OpenGLTexture into this object.
             */
            OpenGLTexture(OpenGLTexture&& ref) = default;

            /**
             * @brief The destructor for OpenGLTexture objects.
             * @details Called when an instance of OpenGLTexture is deleted.
             */
            virtual ~OpenGLTexture();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for OpenGLTexture objects.
             * @details Reassigns the value of this object by copying the data of a OpenGLTexture into this object.
             */
            OpenGLTexture& operator=(const OpenGLTexture& ref) = default;

            /**
             * @brief The move assignment operator for OpenGLTexture objects.
             * @details Reassigns the value of this object by moving the data of a OpenGLTexture into this object.
             */
            OpenGLTexture& operator=(OpenGLTexture&& ref) = default;

        protected:

        private:

    };

}

#endif