#include "Window.hpp"

namespace seedengine {

    void Window::update() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            glClear(GL_COLOR_BUFFER_BIT);
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
        
        EventDispatcher::force(new WindowUpdateEvent(this));
    }

    void Window::close() {
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

        EventDispatcher::force(new WindowCloseEvent(this));
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
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            #if defined(__APPLE__)
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif

            // Create GL Window
            GLFWwindow* gl_window = glfwCreateWindow(window->width(), window->height(), window->title().c_str(), NULL, NULL);
            if (gl_window == NULL)
            {
                ENGINE_ERROR("Failed to create GLFW window.");
                glfwTerminate();
                return nullptr;
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

        void Window::glfwFramebufferSizeCallback(GLFWwindow* gl_window, int width, int height) {
            // Update viewport to match window size
            //TODO: Update viewport using ratio values to window
            glViewport(0, 0, width, height);
            EventDispatcher::force(new WindowResizeEvent(Window::window_map_[gl_window], width, height));
        }

    #endif
}