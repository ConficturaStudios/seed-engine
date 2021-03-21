/**
 * @file OpenGLRenderbuffer.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_OPEN_GL_RENDERBUFFER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_OPEN_GL_RENDERBUFFER_H_

#include "GraphicsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API OpenGLRenderbuffer {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for OpenGLRenderbuffer objects.
             * @details Constructs a new OpenGLRenderbuffer with default initialization for all members.
             */
            OpenGLRenderbuffer();

            /**
             * @brief The copy constructor for OpenGLRenderbuffer objects.
             * @details Constructs a new OpenGLRenderbuffer by copying an existing OpenGLRenderbuffer.
             */
            OpenGLRenderbuffer(const OpenGLRenderbuffer& ref) = default;
            
            /**
             * @brief The move constructor for OpenGLRenderbuffer objects.
             * @details Constructs a new OpenGLRenderbuffer by moving the data of a OpenGLRenderbuffer into this object.
             */
            OpenGLRenderbuffer(OpenGLRenderbuffer&& ref) noexcept = default;

            /**
             * @brief The destructor for OpenGLRenderbuffer objects.
             * @details Called when an instance of OpenGLRenderbuffer is deleted.
             */
            virtual ~OpenGLRenderbuffer();

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for OpenGLRenderbuffer objects.
             * @details Reassigns the value of this object by copying the data of a OpenGLRenderbuffer into this object.
             */
            OpenGLRenderbuffer& operator=(const OpenGLRenderbuffer& rhs) = default;

            /**
             * @brief The move assignment operator for OpenGLRenderbuffer objects.
             * @details Reassigns the value of this object by moving the data of a OpenGLRenderbuffer into this object.
             */
            OpenGLRenderbuffer& operator=(OpenGLRenderbuffer&& rhs) noexcept = default;

        protected:

        private:

    };

}

#endif