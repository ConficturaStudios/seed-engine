#include "Window.hpp"

namespace seedengine {

    Window::~Window() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            glfwDestroyWindow(gl_window_);
            glfwTerminate(); //TODO: Seperate GLFW termination from window close
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
            return;
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
            return;
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
            return;
        #endif
    }

    void Window::update() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            glfwSwapBuffers(gl_window_);
            glfwPollEvents();
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
            return;
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
            return;
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
            return;
        #endif
        
        EventDispatcher::push(new WindowUpdateEvent(this));
    }

    void Window::close() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            glfwSetWindowShouldClose(gl_window_, true);
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
            return;
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
            return;
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
            return;
        #endif

        EventDispatcher::push(new WindowCloseEvent(this));
    }

    bool Window::shouldClose() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            return glfwWindowShouldClose(gl_window_);
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
            return false;
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
            return false;
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
            return false;
        #endif
        return false;
    }

    Window* Window::create(const WindowProperties& preoperties) {
        Window* window = new Window();
        ENGINE_INFO("Creating window {0}...", window->title());
        // Initialize for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            ENGINE_INFO("Creating GLFW window...");

            // Initialize GLFW
            glfwInit();
            
            glfwSetErrorCallback(glfwErrorCallback);
            
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            #if defined(__APPLE__)
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif

            int gl_monitor_count;
            GLFWmonitor** gl_monitors = glfwGetMonitors(&gl_monitor_count);
            GLFWmonitor* gl_monitor = gl_monitors[0];
            //TODO: Encapsulate monitors into a new class
            const GLFWvidmode* gl_vid_mode = glfwGetVideoMode(gl_monitor);

            glfwWindowHint(GLFW_RED_BITS, gl_vid_mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, gl_vid_mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, gl_vid_mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, gl_vid_mode->refreshRate);

            glfwWindowHint(GLFW_DECORATED, (window->properties_.borderless_) ? GLFW_FALSE : GLFW_TRUE);

            //TODO: Clean up window creation code while taking into account fullscreen and borderless options
            //TODO: Add resource sharing to the window creation
            //TODO: Add icon property option

            int win_width = (window->properties_.fullscreen_ && window->properties_.borderless_) ?
                gl_vid_mode->width : window->width();
            int win_height = (window->properties_.fullscreen_ && window->properties_.borderless_) ?
                gl_vid_mode->height : window->height();

            // Create GL Window
            GLFWwindow* gl_window = glfwCreateWindow(
                win_width, win_height, window->title().c_str(),
                (window->properties_.fullscreen_ && window->properties_.borderless_) ? gl_monitor : nullptr, nullptr);
            if (gl_window == nullptr)
            {
                ENGINE_ERROR("Failed to create GLFW window.");
                glfwTerminate();
                return nullptr;
            }

            if (window->properties_.fullscreen_ && !window->properties_.borderless_) {
                glfwMaximizeWindow(gl_window);
            }

            if (!window->properties_.fullscreen_ && window->properties_.borderless_) {
                int pos_x = (gl_vid_mode->width - window->width()) / 2;
                int pos_y = (gl_vid_mode->height - window->height()) / 2;
                glfwSetWindowMonitor(gl_window, nullptr, pos_x, pos_y, window->width(), window->height(), gl_vid_mode->refreshRate);
            }

            glfwMakeContextCurrent(gl_window);

            // Initialize GLAD
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                ENGINE_ERROR("Failed to initialize GLAD.");
                return nullptr;
            }

            glViewport(0, 0, window->width(), window->height()); //TODO: Add viewport size values to defaults.ini

            window_map_[gl_window] = window;

            // Bind function to window resize GLFW event
            glfwSetFramebufferSizeCallback(gl_window, glfwFramebufferSizeCallback);

            EventDispatcher::registerDeligate(WindowResizeEvent::EVENT_ID, [window](Event& e) {
                window->onResize(static_cast<WindowResizeEvent&>(e));
            });

            glfwSetKeyCallback(gl_window, glfwKeyCallback);
            glfwSetCursorPosCallback(gl_window, glfwCursorPositionCallback);
            glfwSetMouseButtonCallback(gl_window, glfwMouseButtonCallback);
            glfwSetScrollCallback(gl_window, glfwScrollCallback);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            window->gl_window_ = gl_window;

        // Initialize for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
            ENGINE_INFO("Creating Vulkan window...");
            ENGINE_WARN("Vulkan not yet supported. Skipping window creation.");
        // Initialize for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
            ENGINE_INFO("Creating DirectX window...");
            ENGINE_WARN("DirectX not yet supported. Skipping window creation.");
        // Initialize for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
            ENGINE_INFO("Creating Metal window...");
            ENGINE_WARN("Metal not yet supported. Skipping window creation.");
        #endif

        EventDispatcher::push(new WindowCreatedEvent(window));

        return window;
    }

    void Window::onResize(WindowResizeEvent& e) {
        this->properties_.width_ = e.x();
        this->properties_.height_ = e.y();
    }

    // OpenGL Code
    #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

        std::map<GLFWwindow*, Window*> Window::window_map_;

        void Window::glfwErrorCallback(int error, const char* description) {
            ENGINE_ERROR("GLFW ERROR ({0}): {1}", error, description);
        }

        void Window::glfwFramebufferSizeCallback(GLFWwindow* gl_window, int width, int height) {
            // Update viewport to match window size
            //TODO: Update viewport using ratio values to window
            glViewport(0, 0, width, height);
            EventDispatcher::push(new WindowResizeEvent(Window::window_map_[gl_window], width, height));
        }

        void Window::glfwKeyCallback(GLFWwindow* gl_window, int key, int scancode, int action, int mods) {
            input::ButtonState button_state;
            switch (action) {
                case GLFW_PRESS:
                    button_state = input::ButtonState::PRESSED;
                    break;
                case GLFW_RELEASE:
                    button_state = input::ButtonState::RELEASED;
                    break;
                case GLFW_REPEAT:
                    button_state = input::ButtonState::REPEAT;
                    break;
            }
            ENGINE_DEBUG("Key '{0}' was {1} ({2})!", key, action, static_cast<unsigned int>(button_state));
            EventDispatcher::push(new KeyboardEvent(key, 0, button_state, mods));
        }

        void Window::glfwCursorPositionCallback(GLFWwindow* gl_window, double xpos, double ypos) {
            EventDispatcher::push(new MouseMovedEvent((float)xpos, (float)ypos));
        }

        void Window::glfwMouseButtonCallback(GLFWwindow* gl_window, int button, int action, int mods) {
            input::ButtonState button_state;
            switch (action) {
                case GLFW_PRESS:
                    button_state = input::ButtonState::PRESSED;
                    break;
                case GLFW_RELEASE:
                    button_state = input::ButtonState::RELEASED;
                    break;
                case GLFW_REPEAT:
                    button_state = input::ButtonState::REPEAT;
                    break;
            }
            ENGINE_DEBUG("Mouse Button '{0}' was {1} ({2})!", button, action, static_cast<unsigned int>(button_state));
            EventDispatcher::push(new MouseButtonEvent(button, button_state, mods));
        }

        void Window::glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
            EventDispatcher::push(new MouseScrolledEvent((float)xoffset, (float)yoffset));
        }

    #endif
}