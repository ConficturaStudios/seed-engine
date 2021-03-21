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
#include "Image.hpp"
#include "Vector2Int.hpp"
#include "Collections.hpp"
#include "Renderer.hpp"

namespace seedengine {

    /**
     * The properties kept by a Window instance.
     */
    struct WindowProperties {
        /** The title of the Window. */
        String title = "New Window";
        /** The width of the Window. */
        uint32 width = 1080;
        /** The height of the Window. */
        uint32 height = 720;
        /** The x position of the Window. */
        uint32 x = 0;
        /** The y position of the Window. */
        uint32 y = 0;
        /** Is the Window borderless? */
        bool borderless = false;
        /** Is the Window fullscreen? */
        bool fullscreen = false;
        /** Is the Window maximized? */
        bool maximized = false;
        /** Is the Window minimized? */
        bool minimized = false;
        /** Does the Window have vsync? */
        bool vsync = false;
        /** The icon for the window. Nullptr uses default. */
        SharedPtr<Image> icon = nullptr;
    };

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

            // Functions

            /**
             * Updates the buffer of this window.
             */
            void update();

            /**
             * Checks if this Window should close.
             * @return True if this Window should close.
             */
            [[nodiscard]] virtual bool shouldClose() const = 0;
            /**
             * Closes this Window, destroying itself.
             */
            void close();

            /**
             * Gets the title of this Window.
             * @return The title of this Window.
             */
            [[nodiscard]] String title() const noexcept;

            /**
             * Sets the title of this Window.
             * @param title The new Window title.
             */
            void setTitle(String title);

            /**
             * Gets the width in pixels of this Window.
             * @return The width in pixels of this Window.
             */
            [[nodiscard]] uint32 width() const noexcept;
            /**
             * Gets the height in pixels of this Window.
             * @return The height in pixels of this Window.
             */
            [[nodiscard]] uint32 height() const noexcept;

            /**
             * Resizes this window to the specified pixel dimensions.
             * @param width The new width.
             * @param height The new height.
             */
            void resize(uint32 width, uint32 height);
            /**
             * Resizes this window to a new size based on screen percentage.
             * @param widthPercent The percentage of the current screen to fill horizontally.
             * @param heightPercent The percentage of the screen to fill vertically.
             */
            void resize(float widthPercent, float heightPercent);

            /**
             * Toggles fullscreen mode on this Window.
             * @return True if the Window is now fullscreen.
             */
            bool toggleMaximize();
            /**
             * Checks if this Window is in a maximized state.
             * @return True if this Window is maximized.
             */
            [[nodiscard]] bool isMaximized() const noexcept;

            /**
             * Toggles minimize mode on this Window.
             * @return True if the screen is minimized.
             */
            bool toggleMinimize();
            /**
             * Checks if this Window is in a minimized state.
             * @return True if this Window is minimized.
             */
            [[nodiscard]] bool isMinimized() const noexcept;

            /**
             * Toggles borderless mode for this Window.
             * @return True if this Window is currently borderless.
             */
            bool toggleBorderless();
            /**
             * Checks if this Window is in borderless mode.
             * @return True if this Window is borderless.
             */
            [[nodiscard]] bool isBorderless() const noexcept;

            /**
             * Centers this Window on the screen.
             */
            void center();

            /**
             * Gets the pixel position of this Window on screen.
             * @return The position of this Window on screen.
             */
            [[nodiscard]] Vector2Int getPosition() const noexcept;

            /**
             * Sets the screen position in pixels.
             * @param x The new x position of this Window.
             * @param y The new y position of this Window.
             */
            void setPosition(uint32 x, uint32_t y);
            /**
             * Sets the screen position of this Window as a percentage of the screen size.
             * @param xPercent The percentage of the screen to place this Window at horizontally.
             * @param yPercent The percentage of the screen to place this Window at vertically.
             */
            void setPosition(float xPercent, float yPercent);

            /**
             * Is VSync enabled for this Window?
             * @return True if VSync is enabled.
             */
            [[nodiscard]] bool isVSync() const noexcept;
            /**
             * Sets the VSync option.
             * @param vsync The new value for the VSync setting.
             */
            void setVSync(bool vsync);

            //TODO: Implement CPU side images

            /**
             * Sets the image used as the icon for this Window.
             * @param icon The new image to use as an icon.
             */
            void setIcon(SharedPtr<Image> icon);
            /**
             * Gets the image used as an icon for this Window.
             * @return The image used as an icon for this Window.
             */
            [[nodiscard]] SharedPtr<Image> getIcon() const noexcept;

        // Static Functions

            // Factory

            /**
             * Creates and returns a new Window based on the active graphics API.
             * @param properties The properties used when generating the new window.
             * @return A new window instance.
             */
            [[nodiscard]] static UniquePtr<Window> Create(const WindowProperties& properties = WindowProperties());

            /**
             * Gets a list of all Window instances.
             * @return A list of all window instances.
             */
            [[nodiscard]] static const List<Window*>& GetAllWindows();

            /**
             * Closes all open Window instances.
             */
            static void CloseAll();

        protected:

            /**
             * The default constructor for the Window interface.
             * @param properties The initial properties of the new window.
             * @param renderer The renderer hosted by this window.
             */
            Window(const WindowProperties& properties, Renderer* renderer);

            /** The properties of this Window. */
            WindowProperties m_properties;

        protected: // Event functions

            /**
             * Called when update() is called. Implementation specific.
             */
            virtual void onUpdate() = 0;
            /**
             * Called when close() is called. Implementation specific.
             */
            virtual void onClose() = 0;
            /**
             * Called when setTitle() is called. Implementation specific.
             * @param title The new Window title.
             */
            virtual void onSetTitle(String title) = 0;
            /**
             * Called when resize() is called. Implementation specific.
             * @param width The new Window width.
             * @param height The new Window height.
             */
            virtual void onResize(uint32 width, uint32 height) = 0;
            /**
             * Called when toggleMaximize() is called. Implementation specific.
             * @param maximize The new maximized state.
             */
            virtual void onToggleMaximize(bool maximize) = 0;
            /**
             * Called when toggleMinimize() is called. Implementation specific.
             * @param minimize The new minimized state.
             */
            virtual void onToggleMinimize(bool minimize) = 0;
            /**
             * Called when toggleBorderless() is called. Implementation specific.
             * @param borderless The new borderless state.
             */
            virtual void onToggleBorderless(bool borderless) = 0;
            /**
             * Called when setPosition() is called. Implementation specific.
             * @param x The new x position.
             * @param y The new y position.
             */
            virtual void onSetPosition(uint32 x, uint32_t y) = 0;
            /**
             * Called when setVSync() is called. Implementation specific.
             * @param vsync The new vsync state.
             */
            virtual void onSetVSync(bool vsync) = 0;
            /**
             * Called when setIcon() is called. Implementation specific.
             * @param icon The new Window icon.
             */
            virtual void onSetIcon(SharedPtr<Image> icon) = 0;

        private:

            /** The collection of all active windows. */
            static List<Window*>* s_windows;

    };

    // TODO: Implement API specific windows
    // TODO: Decide on properties interface and usage
    // TODO: Decide whether or not to move Window and Renderer code to the Graphics module
    // NOTE: If maintaining distinct modules for Graphics objects and the renderer/window, rename Renderer module
    //       to Rendering.
    // TODO: Create a Display class to handle display/screen information (monitor number, width, height, resolution, etc.)

}

#endif