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
#include "Renderer.hpp"

namespace seedengine {

    /**
     * @brief A renderer implementation built around OpenGL.
     */
    class ENGINE_API OpenGLRenderer : public Renderer {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for OpenGLRenderer objects.
             * @details Constructs a new OpenGLRenderer with default initialization for all members.
             */
            OpenGLRenderer();

            /**
             * @brief The destructor for OpenGLRenderer objects.
             * @details Called when an instance of OpenGLRenderer is deleted.
             */
            virtual ~OpenGLRenderer();

        // Functions

            void startup() override;

            void shutdown() override;

        protected:

        private:

    };

}

#endif