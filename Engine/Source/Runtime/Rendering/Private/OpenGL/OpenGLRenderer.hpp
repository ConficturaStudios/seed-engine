/**
 * @file OpenGLRenderer.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_RENDERING_OPEN_GL_RENDERER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_RENDERING_OPEN_GL_RENDERER_H_

#include "RenderingAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API OpenGLRenderer {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for OpenGLRenderer objects.
             * @details Constructs a new OpenGLRenderer with default initialization for all members.
             */
            OpenGLRenderer();

            /**
             * @brief The copy constructor for OpenGLRenderer objects.
             * @details Constructs a new OpenGLRenderer by copying an existing OpenGLRenderer.
             */
            OpenGLRenderer(const OpenGLRenderer& ref) = default;
            
            /**
             * @brief The move constructor for OpenGLRenderer objects.
             * @details Constructs a new OpenGLRenderer by moving the data of a OpenGLRenderer into this object.
             */
            OpenGLRenderer(OpenGLRenderer&& ref) noexcept = default;

            /**
             * @brief The destructor for OpenGLRenderer objects.
             * @details Called when an instance of OpenGLRenderer is deleted.
             */
            virtual ~OpenGLRenderer();

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for OpenGLRenderer objects.
             * @details Reassigns the value of this object by copying the data of a OpenGLRenderer into this object.
             */
            OpenGLRenderer& operator=(const OpenGLRenderer& rhs) = default;

            /**
             * @brief The move assignment operator for OpenGLRenderer objects.
             * @details Reassigns the value of this object by moving the data of a OpenGLRenderer into this object.
             */
            OpenGLRenderer& operator=(OpenGLRenderer&& rhs) noexcept = default;

        protected:

        private:

    };

}

#endif