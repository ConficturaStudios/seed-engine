/**
 * @file OpenGLWindow.cpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "OpenGL/OpenGLWindow.hpp"
#include "OpenGLRenderer.hpp"
#include "Common.hpp"

namespace seedengine {

    OpenGLWindow::OpenGLWindow(const WindowProperties& properties) : Window(properties, new OpenGLRenderer()) {
        // TODO: Handle OpenGL window creation code here
        // NOTE: GLFW and GLAD initialization should be handled in renderer

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef ENGINE_PLATFORM_APPLE
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

        // TODO: Move glMonitor data to a Display and OpenGLDisplay class

        // Get display data and initial values

        int glMonitorCount;
        GLFWmonitor** glMonitors = glfwGetMonitors(&glMonitorCount);
        GLFWmonitor* glMonitor = glMonitors[0];
        const GLFWvidmode* glVidMode = glfwGetVideoMode(glMonitor);

        glfwWindowHint(GLFW_RED_BITS, glVidMode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, glVidMode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, glVidMode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, glVidMode->refreshRate);

        glfwWindowHint(GLFW_DECORATED, m_properties.borderless);

        uint32 width = (m_properties.fullscreen && m_properties.borderless) ? glVidMode->width : m_properties.width;
        uint32 height = (m_properties.fullscreen && m_properties.borderless) ? glVidMode->height : m_properties.height;

        // Create window

        // TODO: update c_str() call if String class changes to custom class instead of alias
        m_glWindow = glfwCreateWindow(width, height, m_properties.title.c_str(), glMonitor, nullptr);

        if (!m_glWindow) {
            // Window creation failed
            // TODO: LOG ERROR: Failed to create OpenGL Window, aborting
            glfwTerminate();
            // TODO: Abort with exit code
        }

        glfwMakeContextCurrent(m_glWindow); // NOTE: This should be called before modifying/updating any specific window

        // Create viewport (runtime only) and framebuffer

        int frameWidth, frameHeight;
        glfwGetFramebufferSize(m_glWindow, &frameWidth, &frameHeight);
        // TODO: use frameWidth and frameHeight to create the framebuffer target for this window
        // Create the viewport
        glViewport(0, 0, frameWidth, frameHeight); // TODO: move this functionality to a Viewport class for the editor

        // Set callbacks

        glfwSetKeyCallback(m_glWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
            // TODO: Dispatch KeyboardEvent here
        });

        // Set clear information

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: Dispatch WindowCreatedEvent here
    }

    OpenGLWindow::~OpenGLWindow() {
        
    }

    bool OpenGLWindow::shouldClose() const {
        return glfwWindowShouldClose(m_glWindow);
    }

    void OpenGLWindow::onUpdate() {

    }

    void OpenGLWindow::onClose() {

    }

    void OpenGLWindow::onSetTitle(String title) {

    }

    void OpenGLWindow::onResize(uint32 width, uint32 height) {

    }

    void OpenGLWindow::onToggleMaximize(bool maximize) {

    }

    void OpenGLWindow::onToggleMinimize(bool minimize) {

    }

    void OpenGLWindow::onToggleBorderless(bool borderless) {

    }

    void OpenGLWindow::onSetPosition(uint32 x, uint32_t y) {

    }

    void OpenGLWindow::onSetVSync(bool vsync) {

    }

    void OpenGLWindow::onSetIcon(SharedPtr<Image> icon) {

    }

}