/**
 * @file OpenGLWindow.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_RENDERING_OPEN_GL_WINDOW_H_
#define SEEDENGINE_INCLUDE_RUNTIME_RENDERING_OPEN_GL_WINDOW_H_

#include "RenderingAPI.hpp"
#include "Window.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API OpenGLWindow : public Window {

        public:

            OpenGLWindow();
            ~OpenGLWindow();

    };

}

#endif