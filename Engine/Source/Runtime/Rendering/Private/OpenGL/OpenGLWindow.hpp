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

            void onUpdate() override;

            void onClose() override;

            void onSetTitle(String title) override;

            void onResize(uint32 width, uint32 height) override;

            void onToggleMaximize(bool maximize) override;

            void onToggleMinimize(bool minimize) override;

            void onToggleBorderless(bool borderless) override;

            void onSetPosition(uint32 x, uint32_t y) override;

            void onSetVSync(bool vsync) override;

            void onSetIcon(SharedPtr<Image> icon) override;

    };

}

#endif