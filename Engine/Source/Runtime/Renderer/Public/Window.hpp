/**
 * Window.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_RENDERER_WINDOW_H_
#define SEEDENGINE_INCLUDE_RUNTIME_RENDERER_WINDOW_H_

#include "RendererAPI.hpp"
#include "Common.hpp"
#include "Vector2.hpp"
#include "Vector2Int.hpp"
#include "Image.hpp"

namespace seedengine {

    /**
     * @brief A window created to host a renderer for the engine.
     * @details A window created to host a renderer instance for the engine. The
     *          underlying type of the window will be an implementation specific
     *          Window for a graphics API such as OpenGL or DirectX.
     *          The window is responsible for providing an interface with the renderer
     *          so that the renderer does not need to be accessed directly. The underlying renderer
     *          will also be API specific.
     * 
     */
    class ENGINE_API Window {

        public:

        // Destructor

            /**
             * @brief The destructor for Window objects.
             * @details Called when an instance of Window is deleted.
             */
            virtual ~Window() = default;

        // Factory

            [[nodiscard]] static UniquePtr<Window> Create(/* const WindowProperties& properties */);

        // Functions

            virtual void update() = 0;

            [[nodiscard]] virtual bool shouldClose() const noexcept = 0;
            virtual void close() = 0;

            [[nodiscard]] virtual String title() const noexcept = 0;

            [[nodiscard]] virtual uint32 width() const noexcept = 0;
            [[nodiscard]] virtual uint32 height() const noexcept = 0;

            virtual void resize(uint32 width, uint32 height) = 0;
            virtual void resize(float width_percent, float height_percent) = 0;

            virtual bool toggleMaximize() = 0;
            [[nodiscard]] virtual bool isMaximized() const noexcept = 0;

            virtual bool toggleMinimize() = 0;
            [[nodiscard]] virtual bool isMinimized() const noexcept = 0;

            virtual void center() = 0;

            virtual void setPosition(uint32 x_pos, uint32_t y_pos) = 0;
            virtual void setPosition(const Vector2Int& pos) = 0;
            virtual void setPosition(float x_pos_percent, float y_pos_percent) = 0;
            virtual void setPosition(const Vector2& pos_percent) = 0;

            [[nodiscard]] virtual bool isVSync() const noexcept = 0;
            virtual void setVSync(bool vsync) = 0;

            //TODO: Implement CPU side images

            virtual void setIcon(SharedPtr<Image> icon) = 0;
            [[nodiscard]] virtual SharedPtr<Image> getIcon() const noexcept = 0;

        // Static Functions

            //static void TerminateAll();

        // Operators

        protected:

        private:

            //static std::vector<Window*> s_windows;

    };

    //TODO: Implement API specific windows
    //TODO: Decide on properties interface and usage
    // TODO: Decide whether or not to move Window and Renderer code to the Graphics module
    // NOTE: If maintaining distinct modules for Graphics objects and the renderer/window, rename Renderer module
    //       to Rendering.

}

#endif