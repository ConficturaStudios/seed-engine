#ifndef SEEDENGINE_INCLUDE_WINDOW_H_
#define SEEDENGINE_INCLUDE_WINDOW_H_

#include "Core.hpp"
#include "Parser.hpp"
#include "Event.hpp"
#include "Image.hpp"

namespace seedengine {
    
    // A class to encapsulate all window properties.
    class WindowProperties {
        
        friend class Window;

    public:
        // Constructs a WindowProperties object. All parameters default to the value found in defaults.ini.
        // @param(const std::string&) title: The title of the window.
        // @param(const unsigned int) width: The width of the window.
        // @param(const unsigned int) height: The height of the window.
        // @param(const bool) fullscreen: Is the window borderless?
        // @param(const bool) borderless: Is the window fullscreen?
        // @param(const bool) vsync: Is VSync enabled for the window?
        WindowProperties(   const std::string& title  = util::parser::ini::DEFAULTS.sections["Window"].string_data["title"],
                            const unsigned int width  = util::parser::ini::DEFAULTS.sections["Window"].int_data["windowed_width"],
                            const unsigned int height = util::parser::ini::DEFAULTS.sections["Window"].int_data["windowed_height"],
                            const bool fullscreen     = util::parser::ini::DEFAULTS.sections["Window"].bool_data["fullscreen"],
                            const bool borderless     = util::parser::ini::DEFAULTS.sections["Window"].bool_data["borderless"],
                            const bool vsync          = util::parser::ini::DEFAULTS.sections["Window"].bool_data["vsync"],
                            Image* icon               = nullptr)
            : title_(title), width_(width), height_(height), borderless_(borderless), fullscreen_(fullscreen), vsync_(vsync), icon_(icon) {}


    private:
        // The title of the window.
        std::string title_;
        // The width of the window.
        unsigned int width_;
        // The height of the window.
        unsigned int height_;
        // Is the window borderless?
        bool borderless_;
        // Is the window fullscreen?
        bool fullscreen_;
        // Is VSync enabled for the window?
        bool vsync_;
        // A pointer to the image used as this windows icon. Set to nullptr to use default.
        Image* icon_;

    };

    // A window to be displayed on a desktop system.
    class Window {

    public:
        // Window destructor.
        virtual ~Window();

        // Updates what is shown on the window.
        void update();
        // Closes this window.
        void close();

        // Resizes this window.
        // @param(unsigned int) width: The new width of the window in pixels.
        // @param(unsigned int) height: The new height of the window in pixels.
        void resize(unsigned int, unsigned int);
        // Resizes this window.
        // @param(float) width: The new width of the window as a percentage of screen size.
        // @param(float) height: The new height of the window as a percentage of screen size.
        void resize(float, float);

        // Toggles the maximized status on this window.
        // @returns: True if the window is maximized.
        bool toggleMaximize();
        // Returns true if the window is maximized.
        // @returns: True if the window is maximized.
        bool isMaximized();

        // Toggles the minimized status on this window.
        // @returns: True if the window is minimized.
        bool toggleMinimize();
        // Returns true if the window is minimized.
        // @returns: True if the window is minimized.
        bool isMinimized();

        // Centers the window on the screen.
        void center();

        // Sets the position of the window on the screen.
        // @param(unsigned int) xpos: The new x position of the window in pixels.
        // @param(unsigned int) ypos: The new y position of the window in pixels.
        void setPosition(unsigned int, unsigned int);
        // Sets the position of the window on the screen.
        // @param(float) xpos: The new x position of the window as a percentage of screen size (0.0 - 1.0).
        // @param(float) ypos: The new y position of the window as a percentage of screen size (0.0 - 1.0).
        void setPosition(float, float);

        // Should this window close?
        // @returns: True if the window should close.
        bool shouldClose();

        // Returns the title of this window.
        // @returns: The title of this window.
        inline std::string title() { return properties_.title_; }

        // Returns the width of this window.
        // @returns: The width of this window.
        inline unsigned int width() { return properties_.width_; }
        // Returns the height of this window.
        // @returns: The height of this window.
        inline unsigned int height() { return properties_.height_; }

        // Returns true if VSync is enabled.
        // @returns: True if VSync is enabled.
        inline bool isVSync() { return properties_.vsync_; }
        // Sets the VSync property of this window.
        // @param(bool) vsync: Enables VSync if true.
        inline void setVSync(bool vsync) { properties_.vsync_ = vsync; }

        // Sets the icon of this window.
        // @param(Image*) icon: The new icon image.
        void setIcon(Image*);
        // Gets the icon of this window.
        // @returns: The icon of this image.
        inline Image* getIcon() { return properties_.icon_; }

        // Creates a new window.
        // @param(const WindowProperties&) properties: The properties to assign to this window. Defaults to the default WindowProperty object.
        // @returns: A pointer to a new Window.
        static Window* create(const WindowProperties& preoperties = WindowProperties());

        // Terminates all open windows.
        static void terminateAll();

        // Event binding for when the window is resized.
        // @param(WindowResizeEvent&) e: A reference to the window resized event being called.
        void onResize(WindowResizeEvent&);

        // Event binding for when the window is maximized.
        // @param(WindowMaximizeEvent&) e: A reference to the window maximized event being called.
        void onMaximize(WindowMaximizeEvent&);

    private:

        // The properties of this window.
        WindowProperties properties_;

        static Window* original_window_;

        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

            // A pointer to a GLFW window.
            GLFWwindow* gl_window_;

            // A map used to reference the seedengine::Window tied to a specific GLFWwindow.
            static std::map<GLFWwindow*, Window*> window_map_;

            // A callback function to bind to GLFW for error handling.
            // @param(int) error: The error code.
            // @param(const char*) description: A description of the error.
            static void glfwErrorCallback(int, const char*);


            // A callback function to bind to GLFW for the window resized event.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            // @param(int) width: The new window width.
            // @param(int) height: The new window height.
            static void glfwWindowSizeCallback(GLFWwindow*, int, int);

            // A callback function to bind to GLFW for the window moved event.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            // @param(int) xpos: The new window x position.
            // @param(int) ypos: The new window y position.
            static void glfwWindowPosCallback(GLFWwindow*, int, int);

            // A callback function to bind to GLFW for the window closed event.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            static void glfwWindowCloseCallback(GLFWwindow*);

            // A callback function to bind to GLFW for the window refreshed event.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            static void glfwWindowRefreshCallback(GLFWwindow*);

            // A callback function to bind to GLFW for the window focus event.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            // @param(int) focused: True if the window was given input focus, or false if it lost it.
            static void glfwWindowFocusCallback(GLFWwindow*, int);

            // A callback function to bind to GLFW for the window iconify/minimized event.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            // @param(int) iconified: True if the window was iconified, or false if it was restored.
            static void glfwWindowIconifyCallback(GLFWwindow*, int);

            // A callback function to bind to GLFW for the window maximized event.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            // @param(int) maximized: True if the window was maximized, or false if it was restored.
            static void glfwWindowMaximizeCallback(GLFWwindow*, int);

            // A callback function to bind to GLFW for the framebuffer resized event.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            // @param(int) width: The new window width.
            // @param(int) height: The new window height.
            static void glfwFramebufferSizeCallback(GLFWwindow*, int, int);

            // A callback function to bind to GLFW for the content scaled event.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            // @param(float) xscale: The new window content x scale.
            // @param(float) yscale: The new window content y scale.
            static void glfwWindowContentScaleCallback(GLFWwindow*, float, float);

            // A callback function to bind to GLFW for key events.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            // @param(int) key: The key affected.
            // @param(int) scancode: A platform specific scancode.
            // @param(int) action: The type of key action.
            // @param(int) mods: A modifier flag for shift, ctrl, alt, and super.
            static void glfwKeyCallback(GLFWwindow*, int, int, int, int);

            // A callback function to bind to GLFW for mouse position events.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            // @param(double) xpos: The x position of the cursor.
            // @param(double) ypos: The y position of the cursor.
            static void glfwCursorPositionCallback(GLFWwindow*, double, double);

            // A callback function to bind to GLFW for mouse button events.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            // @param(int) button: The button pressed.
            // @param(int) action: The type of key action.
            // @param(int) mods: A modifier flag for shift, ctrl, alt, and super.
            static void glfwMouseButtonCallback(GLFWwindow*, int, int, int);

            // A callback function to bind to GLFW for mouse scroll events.
            // @param(GLFWwindow*) gl_window: The window to bind to.
            // @param(double) xoffset: The x offset of the scroll.
            // @param(double) yoffset: The y offset of the scroll.
            static void glfwScrollCallback(GLFWwindow*, double, double);

        #endif

    };

}

#endif