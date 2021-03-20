/**
 * @file Window.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_RENDERING_WINDOW_H_
#define SEEDENGINE_INCLUDE_RUNTIME_RENDERING_WINDOW_H_

#include "RenderingAPI.hpp"
#include "Common.hpp"
#include "Vector2.hpp"
#include "Vector2Int.hpp"
#include "Image.hpp"
#include "Collections.hpp"

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

            /**
             * Creates and returns a new Window based on the active graphics API.
             * @return A new window instance.
             */
            [[nodiscard]] static UniquePtr<Window> Create(/* const WindowProperties& properties */);

            // Functions

            /**
             * Updates the buffer of this window.
             */
            virtual void update() = 0;

            /**
             * Checks if this Window should close.
             * @return True if this Window should close.
             */
            [[nodiscard]] virtual bool shouldClose() const noexcept = 0;
            /**
             * Closes this Window, destroying itself.
             */
            virtual void close() = 0;

            /**
             * Gets the title of this Window.
             * @return The title of this Window.
             */
            [[nodiscard]] virtual String title() const noexcept = 0;

            /**
             * Gets the width in pixels of this Window.
             * @return The width in pixels of this Window.
             */
            [[nodiscard]] virtual uint32 width() const noexcept = 0;
            /**
             * Gets the height in pixels of this Window.
             * @return The height in pixels of this Window.
             */
            [[nodiscard]] virtual uint32 height() const noexcept = 0;

            /**
             * Resizes this window to the specified pixel dimensions.
             * @param width The new width.
             * @param height The new height.
             */
            virtual void resize(uint32 width, uint32 height) = 0;
            /**
             * Resizes this window to a new size based on screen percentage.
             * @param widthPercent The percentage of the current screen to fill horizontally.
             * @param heightPercent The percentage of the screen to fill vertically.
             */
            virtual void resize(float widthPercent, float heightPercent) = 0;

            /**
             * Toggles fullscreen mode on this Window.
             * @return True if the Window is now fullscreen.
             */
            virtual bool toggleMaximize() = 0;
            /**
             * Checks if this Window is in a maximized state.
             * @return True if this Window is maximized.
             */
            [[nodiscard]] virtual bool isMaximized() const noexcept = 0;

            /**
             * Toggles minimize mode on this Window.
             * @return True if the screen is minimized.
             */
            virtual bool toggleMinimize() = 0;
            /**
             * Checks if this Window is in a minimized state.
             * @return True if this Window is minimized.
             */
            [[nodiscard]] virtual bool isMinimized() const noexcept = 0;

            /**
             * Toggles borderless mode for this Window.
             * @return True if this Window is currently borderless.
             */
            virtual bool toggleBorderless() = 0;
            /**
             * Checks if this Window is in borderless mode.
             * @return True if this Window is borderless.
             */
            [[nodiscard]] virtual bool isBorderless() const noexcept = 0;

            /**
             * Centers this Window on the screen.
             */
            virtual void center() = 0;

            /**
             * Sets the screen position in pixels.
             * @param x The new x position of this Window.
             * @param y The new y position of this Window.
             */
            virtual void setPosition(uint32 x, uint32_t y) = 0;
            /**
             * Sets the screen position of this Window as a percentage of the screen size.
             * @param xPercent The percentage of the screen to place this Window at horizontally.
             * @param yPercent The percentage of the screen to place this Window at vertically.
             */
            virtual void setPosition(float xPercent, float yPercent) = 0;

            /**
             * Is VSync enabled for this Window?
             * @return True if VSync is enabled.
             */
            [[nodiscard]] virtual bool isVSync() const noexcept = 0;
            /**
             * Sets the VSync option.
             * @param vsync The new value for the VSync setting.
             */
            virtual void setVSync(bool vsync) = 0;

            //TODO: Implement CPU side images

            /**
             * Sets the image used as the icon for this Window.
             * @param icon The new image to use as an icon.
             */
            virtual void setIcon(SharedPtr<Image> icon) = 0;
            /**
             * Gets the image used as an icon for this Window.
             * @return The image used as an icon for this Window.
             */
            [[nodiscard]] virtual SharedPtr<Image> getIcon() const noexcept = 0;

            // Static Functions

            //static void TerminateAll();

        protected:

            /**
             * The default constructor for the Window interface.
             */
            Window() = default;

        private:

            //static List<Window*> s_windows;

    };

    // TODO: Implement API specific windows
    // TODO: Decide on properties interface and usage
    // TODO: Decide whether or not to move Window and Renderer code to the Graphics module
    // NOTE: If maintaining distinct modules for Graphics objects and the renderer/window, rename Renderer module
    //       to Rendering.
    // TODO: Create a Display class to handle display/screen information (monitor number, width, height, resolution, etc.)

}

#endif