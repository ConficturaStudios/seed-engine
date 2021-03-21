/**
 * @file OpenGLFramebuffer.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_OPEN_GL_FRAMEBUFFER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_OPEN_GL_FRAMEBUFFER_H_

#include "GraphicsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API OpenGLFramebuffer {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for OpenGLFramebuffer objects.
             * @details Constructs a new OpenGLFramebuffer with default initialization for all members.
             */
            OpenGLFramebuffer();

            /**
             * @brief The copy constructor for OpenGLFramebuffer objects.
             * @details Constructs a new OpenGLFramebuffer by copying an existing OpenGLFramebuffer.
             */
            OpenGLFramebuffer(const OpenGLFramebuffer& ref) = default;
            
            /**
             * @brief The move constructor for OpenGLFramebuffer objects.
             * @details Constructs a new OpenGLFramebuffer by moving the data of a OpenGLFramebuffer into this object.
             */
            OpenGLFramebuffer(OpenGLFramebuffer&& ref) noexcept = default;

            /**
             * @brief The destructor for OpenGLFramebuffer objects.
             * @details Called when an instance of OpenGLFramebuffer is deleted.
             */
            virtual ~OpenGLFramebuffer();

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for OpenGLFramebuffer objects.
             * @details Reassigns the value of this object by copying the data of a OpenGLFramebuffer into this object.
             */
            OpenGLFramebuffer& operator=(const OpenGLFramebuffer& rhs) = default;

            /**
             * @brief The move assignment operator for OpenGLFramebuffer objects.
             * @details Reassigns the value of this object by moving the data of a OpenGLFramebuffer into this object.
             */
            OpenGLFramebuffer& operator=(OpenGLFramebuffer&& rhs) noexcept = default;

        protected:

        private:

    };

}

#endif