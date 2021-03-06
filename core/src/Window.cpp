#include "Window.hpp"

namespace seedengine {

    Window* Window::original_window_ = nullptr;

    Window::~Window() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            glfwDestroyWindow(gl_window_);
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
        
        EventDispatcher::push<WindowUpdateEvent>(this);
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
    }

    void Window::resize(unsigned int width, unsigned int height) {
        
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            int gl_monitor_count;
            GLFWmonitor** gl_monitors = glfwGetMonitors(&gl_monitor_count);
            GLFWmonitor* gl_monitor = gl_monitors[0];

            const GLFWvidmode* gl_vid_mode = glfwGetVideoMode(gl_monitor);

            glfwSetWindowSize(gl_window_,
                (gl_vid_mode->width < (int)width) ? gl_vid_mode->width : width,
                (gl_vid_mode->height < (int)height) ? gl_vid_mode->height : height);
        
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

    void Window::resize(float width, float height) {
        if (width > 1.0f || width < 0.0f) {
            ENGINE_ERROR("Window {0} width change out of bounds.", title());
            return;
        }
        if (height > 1.0f || height < 0.0f) {
            ENGINE_ERROR("Window {0} height change out of bounds.", title());
            return;
        }

        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            int gl_monitor_count;
            GLFWmonitor** gl_monitors = glfwGetMonitors(&gl_monitor_count);
            GLFWmonitor* gl_monitor = gl_monitors[0];

            const GLFWvidmode* gl_vid_mode = glfwGetVideoMode(gl_monitor);

            glfwSetWindowSize(gl_window_,
                (int)(gl_vid_mode->width * width), (int)(gl_vid_mode->height * height));
        
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

    bool Window::toggleMaximize() {
        bool maximized = isMaximized();

        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            int gl_monitor_count;
            GLFWmonitor** gl_monitors = glfwGetMonitors(&gl_monitor_count);
            GLFWmonitor* gl_monitor = gl_monitors[0];

            const GLFWvidmode* gl_vid_mode = glfwGetVideoMode(gl_monitor);

            if (maximized) glfwRestoreWindow(gl_window_);
            else glfwMaximizeWindow(gl_window_);

        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
        
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
        
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
        
        #endif

        return isMaximized();
    }

    bool Window::isMaximized() const {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            return glfwGetWindowAttrib(gl_window_, GLFW_MAXIMIZED);
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
    }

    bool Window::toggleMinimize() {
        bool minimized = isMinimized();
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            if (minimized) glfwRestoreWindow(gl_window_);
            else glfwIconifyWindow(gl_window_);
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
        
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
        
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
        
        #endif

        return isMinimized();
    }

    bool Window::isMinimized() const {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            return glfwGetWindowAttrib(gl_window_, GLFW_ICONIFIED);
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
    }

    void Window::center() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            int gl_monitor_count;
            GLFWmonitor** gl_monitors = glfwGetMonitors(&gl_monitor_count);
            GLFWmonitor* gl_monitor = gl_monitors[0];

            const GLFWvidmode* gl_vid_mode = glfwGetVideoMode(gl_monitor);

            int pos_x = (gl_vid_mode->width - width()) / 2;
            int pos_y = (gl_vid_mode->height - height()) / 2;

            glfwSetWindowPos(gl_window_, pos_x, pos_y);

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

    void Window::setPosition(unsigned int xpos, unsigned int ypos) {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            int gl_monitor_count;
            GLFWmonitor** gl_monitors = glfwGetMonitors(&gl_monitor_count);
            GLFWmonitor* gl_monitor = gl_monitors[0];

            const GLFWvidmode* gl_vid_mode = glfwGetVideoMode(gl_monitor);

            int pos_x = (gl_vid_mode->width <= (int)xpos) ? gl_vid_mode->width - 1 : xpos;
            int pos_y = (gl_vid_mode->height <= (int)ypos) ? gl_vid_mode->height - 1 : ypos;

            glfwSetWindowPos(gl_window_, pos_x, pos_y);
        
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

    void Window::setPosition(float xpos, float ypos) {
        if (xpos > 1.0f || xpos < 0.0f) {
            ENGINE_ERROR("Window {0} x position change out of bounds.", title());
            return;
        }
        if (ypos > 1.0f || ypos < 0.0f) {
            ENGINE_ERROR("Window {0} y position change out of bounds.", title());
            return;
        }

        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            int gl_monitor_count;
            GLFWmonitor** gl_monitors = glfwGetMonitors(&gl_monitor_count);
            GLFWmonitor* gl_monitor = gl_monitors[0];

            const GLFWvidmode* gl_vid_mode = glfwGetVideoMode(gl_monitor);

            int pos_x = (int)(gl_vid_mode->width * xpos);
            int pos_y = (int)(gl_vid_mode->height * ypos);

            glfwSetWindowPos(gl_window_, pos_x, pos_y);
        
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

    bool Window::shouldClose() const {
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

    void Window::setIcon(std::shared_ptr<Image> icon) {
        properties_.icon_ = icon;
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            if (icon == nullptr) glfwSetWindowIcon(gl_window_, 0, nullptr);
            else glfwSetWindowIcon(gl_window_, 1, icon->glfwImage());
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

    Window* Window::create(const WindowProperties& properties) {
        Window* window = new Window(properties);
        ENGINE_INFO("Creating window {0}...", window->title());

        bool init = false;
        if (original_window_ == nullptr) {
            original_window_ = window;
            init = true;
        }

        // Initialize for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            ENGINE_INFO("Creating GLFW window...");

            if (init) {
                // Initialize GLFW
                glfwInit();
                // Set error callback, binds to the standard output
                glfwSetErrorCallback(glfwErrorCallback);
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            #if defined(__APPLE__)
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif

            int gl_monitor_count;
            //TODO: Encapsulate monitors into a new class
            GLFWmonitor** gl_monitors = glfwGetMonitors(&gl_monitor_count);
            GLFWmonitor* gl_monitor = gl_monitors[0];
            const GLFWvidmode* gl_vid_mode = glfwGetVideoMode(gl_monitor);

            glfwWindowHint(GLFW_RED_BITS, gl_vid_mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, gl_vid_mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, gl_vid_mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, gl_vid_mode->refreshRate);

            glfwWindowHint(GLFW_DECORATED, (window->properties_.borderless_) ? GLFW_FALSE : GLFW_TRUE);

            //TODO: Clean up window creation code while taking into account fullscreen and borderless options

            int win_width = (window->properties_.fullscreen_ && window->properties_.borderless_) ?
                gl_vid_mode->width : window->width();
            int win_height = (window->properties_.fullscreen_ && window->properties_.borderless_) ?
                gl_vid_mode->height : window->height();

            // Create GL Window
            GLFWwindow* gl_window = glfwCreateWindow(
                win_width, win_height, window->title().c_str(),
                (window->properties_.fullscreen_ && window->properties_.borderless_) ? gl_monitor : nullptr,
                (init) ? nullptr : original_window_->gl_window_);
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
            
            std::shared_ptr<Image> p_icon = window->properties_.icon_;

            if (p_icon == nullptr) glfwSetWindowIcon(gl_window, 0, nullptr);
            else glfwSetWindowIcon(gl_window, 1, p_icon->glfwImage());

            glfwMakeContextCurrent(gl_window);

            // Initialize GLAD
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                ENGINE_ERROR("Failed to initialize GLAD.");
                return nullptr;
            }

            int w, h;
            glfwGetFramebufferSize(gl_window, &w, &h); // Make viewport match window size
            glViewport(0, 0, w, h); //TODO: Add viewport size values to defaults.ini

            window_map_[gl_window] = window;

            // Bind window callbacks
            glfwSetWindowSizeCallback(gl_window, glfwWindowSizeCallback);
            glfwSetWindowPosCallback(gl_window, glfwWindowPosCallback);
            glfwSetWindowCloseCallback(gl_window, glfwWindowCloseCallback);
            glfwSetWindowRefreshCallback(gl_window, glfwWindowRefreshCallback);
            glfwSetWindowFocusCallback(gl_window, glfwWindowFocusCallback);
            glfwSetWindowIconifyCallback(gl_window, glfwWindowIconifyCallback);
            glfwSetWindowMaximizeCallback(gl_window, glfwWindowMaximizeCallback);
            glfwSetFramebufferSizeCallback(gl_window, glfwFramebufferSizeCallback);
            glfwSetWindowContentScaleCallback(gl_window, glfwWindowContentScaleCallback);

            EventDispatcher::registerDeligate(WindowResizeEvent::EVENT_ID, [window](Event& e) {
                window->onResize(static_cast<WindowResizeEvent&>(e));
            });

            EventDispatcher::registerDeligate(WindowMaximizeEvent::EVENT_ID, [window](Event& e) {
                window->onMaximize(static_cast<WindowMaximizeEvent&>(e));
            });

            glfwSetKeyCallback(gl_window, glfwKeyCallback);
            glfwSetCursorPosCallback(gl_window, glfwCursorPositionCallback);
            glfwSetMouseButtonCallback(gl_window, glfwMouseButtonCallback);
            glfwSetScrollCallback(gl_window, glfwScrollCallback);

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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

        EventDispatcher::push<WindowCreatedEvent>(window);

        return window;
    }

    void Window::terminateAll() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            glfwTerminate();
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

    void Window::onResize(WindowResizeEvent& e) {
        this->properties_.width_ = e.width();
        this->properties_.height_ = e.width();
    }

    void Window::onMaximize(WindowMaximizeEvent& e) {
        this->properties_.fullscreen_ = e.maximized();
    }

    // OpenGL Code
    #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

        std::map<GLFWwindow*, Window*> Window::window_map_;

        void Window::glfwErrorCallback(int error, const char* description) {
            ENGINE_ERROR("GLFW ERROR ({0}): {1}", error, description);
        }


        void Window::glfwWindowSizeCallback(GLFWwindow* gl_window, int width, int height) {
            EventDispatcher::push<WindowResizeEvent>(Window::window_map_[gl_window], width, height);
        }

        void Window::glfwWindowPosCallback(GLFWwindow* gl_window, int xpos, int ypos) {
            EventDispatcher::push<WindowPositionEvent>(Window::window_map_[gl_window], xpos, ypos);
        }

        void Window::glfwWindowCloseCallback(GLFWwindow* gl_window) {
            EventDispatcher::push<WindowCloseEvent>(Window::window_map_[gl_window]);
        }

        void Window::glfwWindowRefreshCallback(GLFWwindow* gl_window) {
            EventDispatcher::push<WindowRefreshEvent>(Window::window_map_[gl_window]);
        }

        void Window::glfwWindowFocusCallback(GLFWwindow* gl_window, int focused) {
            EventDispatcher::push<WindowFocusEvent>(Window::window_map_[gl_window], focused);
        }

        void Window::glfwWindowIconifyCallback(GLFWwindow* gl_window, int iconified) {
            EventDispatcher::push<WindowMinimizeEvent>(Window::window_map_[gl_window], iconified);
        }

        void Window::glfwWindowMaximizeCallback(GLFWwindow* gl_window, int maximized) {
            EventDispatcher::push<WindowMaximizeEvent>(Window::window_map_[gl_window], maximized);
        }

        void Window::glfwFramebufferSizeCallback(GLFWwindow* gl_window, int width, int height) {
            // Update viewport to match window size
            //TODO: Update viewport using ratio values to window
            glViewport(0, 0, width, height);
            EventDispatcher::push<WindowResizeEvent>(Window::window_map_[gl_window], width, height);
        }

        void Window::glfwWindowContentScaleCallback(GLFWwindow* gl_window, float xscale, float yscale) {
            EventDispatcher::push<WindowConentScaleEvent>(Window::window_map_[gl_window], xscale, yscale);
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
                default:
                    return;
            }
            ENGINE_DEBUG("Key '{0}' was {1} ({2})!", key, action, static_cast<unsigned int>(button_state));
            EventDispatcher::push<KeyboardEvent>(key, 0, button_state, mods);
        }

        void Window::glfwCursorPositionCallback(GLFWwindow* gl_window, double xpos, double ypos) {
            int w, h;
            glfwGetFramebufferSize(gl_window, &w, &h);
            EventDispatcher::push<MouseMovedEvent>((float)xpos / w, (float)ypos / h);
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
                default:
                    return;
            }
            MouseButtonEvent* e = new MouseButtonEvent(button, button_state, mods);
            ENGINE_DEBUG("Mouse Button '{0}' was {1} ({2}) at <{3}, {4}>!", button, action, static_cast<unsigned int>(button_state), e->x(), e->y());
            EventDispatcher::push<MouseButtonEvent>(button, button_state, mods);
        }

        void Window::glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
            EventDispatcher::push<MouseScrolledEvent>((float)xoffset, (float)yoffset);
        }

    #endif
}