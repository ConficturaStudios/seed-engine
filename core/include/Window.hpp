#ifndef SEEDENGINE_INCLUDE_WINDOW_H_
#define SEEDENGINE_INCLUDE_WINDOW_H_

#include "Core.hpp"
#include "Parser.hpp"
#include "Event.hpp"
#include "Image.hpp"

namespace seedengine {
    
    /**
     * @brief A class to encapsulate all window properties.
     * @details
     */
    class WindowProperties {
        
        friend class Window;

    public:
        /**
         * @brief Constructs a WindowProperties object. All parameters default to the
         *        value found in defaults.ini.
         * 
         * @param title The title of the window.
         * @param width The width of the window.
         * @param height The height of the window.
         * @param fullscreen Is the window borderless?
         * @param borderless Is the window fullscreen?
         * @param vsync Is VSync enabled for the window?
         * @param icon The icon image to display on the window.
         */
        WindowProperties(const string title = util::DEFAULTS.getString("Window", "title"),
                const unsigned int width  = util::DEFAULTS.getInt("Window", "windowed_width"),
                const unsigned int height = util::DEFAULTS.getInt("Window", "windowed_height"),
                const bool fullscreen     = util::DEFAULTS.getBool("Window", "fullscreen"),
                const bool borderless     = util::DEFAULTS.getBool("Window", "borderless"),
                const bool vsync          = util::DEFAULTS.getBool("Window", "vsync"),
                Image* icon = nullptr) : title_(title), width_(width), height_(height),
                    borderless_(borderless), fullscreen_(fullscreen), vsync_(vsync), icon_(icon) {}


    private:
        /** The title of the window. */
        string title_;
        /** The width of the window. */
        unsigned int width_;
        /** The height of the window. */
        unsigned int height_;
        /** Is the window borderless? */
        bool borderless_;
        /** Is the window fullscreen? */
        bool fullscreen_;
        /** Is VSync enabled for the window? */
        bool vsync_;
        /** A pointer to the image used as this windows icon. Set to nullptr to use default. */
        std::shared_ptr<Image> icon_;

    };

    /**
     * @brief A window to be displayed on a desktop system.
     * @details
     */
    class Window {

    public:
        /** Window destructor. */
        virtual ~Window();

        /** Updates the window to the latest render frame. */
        void update();
        /** Closes this window. */
        void close();

        /**
         * @brief Resizes this window.
         * 
         * @param width The new width of the window in pixels.
         * @param height The new height of the window in pixels.
         */
        void resize(unsigned int width, unsigned int height);
        /**
         * @brief Resizes this window.
         * 
         * @param width The new width of the window as a percentage of screen size.
         * @param width The new height of the window as a percentage of screen size.
         */
        void resize(float width, float width);

        /**
         * @brief Toggles the maximized status on this window.
         * 
         * @return true If the window is maximized.
         * @return false If the window is not maximized.
         */
        bool toggleMaximize();
        /**
         * @brief Returns true if the window is maximized.
         * 
         * @return true If the window is maximized.
         * @return false If the window is not maximized.
         */
        inline bool isMaximized() const;

        /**
         * @brief Toggles the minimized status on this window.
         * 
         * @return true If the window is minimized.
         * @return false If the window is not minimized.
         */
        bool toggleMinimize();
        /**
         * @brief Returns true if the window is minimized.
         * 
         * @return true If the window is minimized.
         * @return false If the window is not minimized.
         */
        inline bool isMinimized() const;

        /** Centers this window on the screen. */
        void center();

        /**
         * @brief Sets the position of the window on the screen.
         * 
         * @param xpos The new x position of the window in pixels.
         * @param ypos The new y position of the window in pixels.
         */
        void setPosition(unsigned int xpos, unsigned int ypos);
        /**
         * @brief Sets the position of the window on the screen.
         * 
         * @param xpos The new x position of the window as a percentage of screen size (0.0 - 1.0).
         * @param ypos The new y position of the window as a percentage of screen size (0.0 - 1.0).
         */
        void setPosition(float xpos, float ypos);

        /**
         * @brief Should this window close?
         * 
         * @return true If the window should close.
         * @return false If the window should remain open.
         */
        bool shouldClose() const;

        /**
         * @brief Returns the title of this window.
         * 
         * @return string The title of this window.
         */
        inline string title() const { return properties_.title_; }

        /**
         * @brief Returns the width of this window.
         * 
         * @return unsigned int The width of this window.
         */
        inline unsigned int width() const { return properties_.width_; }
        /**
         * @brief Returns the height of this window.
         * 
         * @return unsigned int The height of this window.
         */
        inline unsigned int height() const { return properties_.height_; }

        /**
         * @brief Returns true if VSync is enabled.
         * 
         * @return true If VSync is enabled.
         * @return false If VSync is disabled.
         */
        inline bool isVSync() const { return properties_.vsync_; }
        /**
         * @brief Sets the VSync property of this window.
         * 
         * @param vsync Enables VSync if true.
         */
        inline void setVSync(bool vsync) { properties_.vsync_ = vsync; }

        /**
         * @brief Sets the icon of this window.
         * 
         * @param icon The new icon image.
         */
        void setIcon(std::shared_ptr<Image> icon);
        /**
         * @brief Gets the icon of this window.
         * 
         * @return std::shared_ptr<Image> The icon of this window.
         */
        inline std::shared_ptr<Image> getIcon() const { return properties_.icon_; }

        /**
         * @brief Creates a new window.
         * 
         * @param properties The properties to assign to this window. Defaults
         *                   to the default WindowProperty object.
         * @return Window* A pointer to a new Window.
         */
        static Window* create(const WindowProperties& properties = WindowProperties());

        /** Terminates all open windows. */
        static void terminateAll();

        /**
         * @brief Event binding for when the window is resized.
         * 
         * @param e A reference to the window resized event being called.
         */
        void onResize(WindowResizeEvent& e);

        /**
         * @brief Event binding for when the window is maximized.
         * 
         * @param e A reference to the window maximized event being called.
         */
        void onMaximize(WindowMaximizeEvent& e);

    private:

        Window(const WindowProperties& properties) : properties_(properties) {}

        /** The properties of this window. */
        WindowProperties properties_;
        /** The original window created. */
        static Window* original_window_;

        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

            /** A pointer to a GLFW window. */
            GLFWwindow* gl_window_;

            /** A map used to reference the seedengine::Window tied to a specific GLFWwindow. */
            static std::map<GLFWwindow*, Window*> window_map_;

            /**
             * @brief A callback function to bind to GLFW for error handling.
             * 
             * @param error The error code.
             * @param description A description of the error.
             */
            static void glfwErrorCallback(int error, const char* description);


            /**
             * @brief A callback function to bind to GLFW for the window resized event.
             * 
             * @param gl_window The window to bind to.
             * @param width The new window width.
             * @param height The new window height.
             */
            static void glfwWindowSizeCallback(GLFWwindow* gl_window, int width, int height);

            /**
             * @brief A callback function to bind to GLFW for the window moved event.
             * 
             * @param gl_window The window to bind to.
             * @param xpos The new window x position.
             * @param ypos The new window y position.
             */
            static void glfwWindowPosCallback(GLFWwindow* gl_window, int xpos, int ypos);

            /**
             * @brief A callback function to bind to GLFW for the window closed event.
             * 
             * @param gl_window The window to bind to.
             */
            static void glfwWindowCloseCallback(GLFWwindow* gl_window);

            /**
             * @brief A callback function to bind to GLFW for the window refreshed event.
             * 
             * @param gl_window The window to bind to.
             */
            static void glfwWindowRefreshCallback(GLFWwindow* gl_window);

            /**
             * @brief A callback function to bind to GLFW for the window focus event.
             * 
             * @param gl_window The window to bind to.
             * @param focused True if the window was given input focus, or false if it lost it.
             */
            static void glfwWindowFocusCallback(GLFWwindow* gl_window, int focused);

            /**
             * @brief A callback function to bind to GLFW for the window iconify/minimized event.
             * 
             * @param gl_window The window to bind to.
             * @param iconified True if the window was iconified, or false if it was restored.
             */
            static void glfwWindowIconifyCallback(GLFWwindow* gl_window, int iconified);

            /**
             * @brief A callback function to bind to GLFW for the window maximized event.
             * 
             * @param gl_window The window to bind to.
             * @param maximized True if the window was maximized, or false if it was restored.
             */
            static void glfwWindowMaximizeCallback(GLFWwindow* gl_window, int maximized);

            /**
             * @brief A callback function to bind to GLFW for the framebuffer resized event.
             * 
             * @param gl_window The window to bind to.
             * @param width The new window width.
             * @param height The new window height.
             */
            static void glfwFramebufferSizeCallback(GLFWwindow* gl_window, int width, int height);

            /**
             * @brief A callback function to bind to GLFW for the content scaled event.
             * 
             * @param gl_window The window to bind to.
             * @param xscale The new window content x scale.
             * @param yscale The new window content y scale.
             */
            static void glfwWindowContentScaleCallback(GLFWwindow* gl_window, float xscale,
                float yscale);

            /**
             * @brief A callback function to bind to GLFW for key events.
             * 
             * @param gl_window The window to bind to.
             * @param key The key affected.
             * @param scancode A platform specific scancode.
             * @param action The type of key action.
             * @param mods A modifier flag for shift, ctrl, alt, and super.
             */
            static void glfwKeyCallback(GLFWwindow* gl_window, int key, int scancode,
                int action, int mods);

            /**
             * @brief A callback function to bind to GLFW for mouse position events.
             * 
             * @param gl_window The window to bind to.
             * @param xpos The x position of the cursor.
             * @param ypos The y position of the cursor.
             */
            static void glfwCursorPositionCallback(GLFWwindow* gl_window, double xpos, double ypos);

            /**
             * @brief A callback function to bind to GLFW for mouse button events.
             * 
             * @param gl_window The window to bind to.
             * @param button The button pressed.
             * @param action The type of key action.
             * @param mods A modifier flag for shift, ctrl, alt, and super.
             */
            static void glfwMouseButtonCallback(GLFWwindow* gl_window gl_window,
                int button, int action, int mods);

            /**
             * @brief A callback function to bind to GLFW for mouse scroll events.
             * 
             * @param gl_window The window to bind to.
             * @param xoffset The x offset of the scroll.
             * @param yoffset The y offset of the scroll.
             */
            static void glfwScrollCallback(GLFWwindow* gl_window, double xoffset, double yoffset);

        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN


        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX


        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL

        
        #endif

    };

}

#endif