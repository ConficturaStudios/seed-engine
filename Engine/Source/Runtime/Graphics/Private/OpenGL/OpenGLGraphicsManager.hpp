/**
 * @file OpenGLGraphicsManager.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_OPEN_GL_GRAPHICS_MANAGER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_OPEN_GL_GRAPHICS_MANAGER_H_

#include "GraphicsAPI.hpp"
#include "GraphicsManager.hpp"

namespace seedengine {

    /**
     * @brief The graphics manager implementation used for OpenGL enabled applications.
     */
    class OpenGLGraphicsManager final : public GraphicsManager {

        public:

        // Constructors and destructor

            /**
             * @brief Initializes the OpenGL Graphics Manager.
             * @details Handles initialization for OpenGL using GLFW. When this object is
             *          destroyed, OpenGL will be shut down again.
             */
            OpenGLGraphicsManager();

            /**
             * @brief The destructor for OpenGL Graphics Managers.
             * @details Called when an instance of OpenGLGraphicsManager is deleted. This
             *          destructor will shut down all OpenGL processes.
             */
            ~OpenGLGraphicsManager() final;

    };

}

#endif