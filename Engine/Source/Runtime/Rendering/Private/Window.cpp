/**
 * @file Window.cpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Window.hpp"
#include "OpenGL/OpenGLWindow.hpp"

#include <cassert>

namespace seedengine {

    List<Window*>* Window::s_windows = new LinkedList<Window*>();

    Window::Window(const WindowProperties& properties, Renderer* renderer) {
        m_properties = properties;

    }

    UniquePtr<Window> Window::Create(const WindowProperties& properties) {
        Window* window;
        switch (GraphicsManager::GetFramework()) {
            #if ENGINE_GRAPHICS_OPENGL
                case EGraphicsFramework::OPEN_GL: window = new OpenGLWindow(properties); break;
            #endif
            #if ENGINE_GRAPHICS_DIRECTX
                case EGraphicsFramework::DIRECT_X: window = new DirectXWindow(properties); break;
            #endif
            #if ENGINE_GRAPHICS_METAL
                case EGraphicsFramework::METAL: window = new MetalWindow(properties); break;
            #endif
            #if ENGINE_GRAPHICS_VULKAN
                case EGraphicsFramework::VULKAN: window = new VulkanWindow(properties); break;
            #endif
            // Unknown or unsupported value
            default: window = nullptr; break;
        }
        // Check if window was created successfully
        if (!window) {
            // TODO: Add per-module logging
            // TODO: Replace direct assert calls with custom SE_ASSERT(condition, msg) macros
            assert(false);
        }
        s_windows->addLast(window);
        return UniquePtr<Window>(window);
    }

    const List<Window*>& Window::GetAllWindows() {
        return *s_windows;
    }

    void Window::CloseAll() {
        for (Window* window : *s_windows) {
            window->close();
        }
        s_windows->clear();
    }


    void Window::update() {
        onUpdate();
    }

    void Window::close() {
        onClose();
    }

    String Window::title() const noexcept {
        return m_properties.title;
    }

    void Window::setTitle(String title) {
        m_properties.title = title;
        onSetTitle(title);
    }

    uint32 Window::width() const noexcept {
        return m_properties.width;
    }

    uint32 Window::height() const noexcept {
        return m_properties.height;
    }

    void Window::resize(uint32 width, uint32 height) {
        m_properties.width = width;
        m_properties.height = height;
        // TODO: Constrain this input with a config specified min
        onResize(width, height);
    }

    void Window::resize(float widthPercent, float heightPercent) {
        // TODO: Implement using Display properties
    }

    bool Window::toggleMaximize() {
        m_properties.maximized = !m_properties.maximized;
        onToggleMaximize(m_properties.maximized);
        return m_properties.maximized;
    }

    bool Window::isMaximized() const noexcept {
        return m_properties.maximized;
    }

    bool Window::toggleMinimize() {
        m_properties.minimized = !m_properties.minimized;
        onToggleMinimize(m_properties.minimized);
        return m_properties.minimized;
    }

    bool Window::isMinimized() const noexcept {
        return m_properties.minimized;
    }

    bool Window::toggleBorderless() {
        m_properties.borderless = !m_properties.borderless;
        onToggleBorderless(m_properties.borderless);
        return m_properties.borderless;
    }

    bool Window::isBorderless() const noexcept {
        return m_properties.borderless;
    }

    void Window::center() {
        // TODO: Implement using Display properties
    }

    Vector2Int Window::getPosition() const noexcept {
        // TODO: Handle position standardization between APIs (make standard reference point like top left corner)
        return Vector2Int(m_properties.x, m_properties.y);
    }

    void Window::setPosition(uint32 x, uint32_t y) {
        m_properties.x = x;
        m_properties.y = y;
        // TODO: Handle API agnostic positioning
        // TODO: Restrict position based on Display properties
        // TODO: Add a moveToMonitor method
        onSetPosition(x, y);
    }

    void Window::setPosition(float xPercent, float yPercent) {
        // TODO: Implement using Display properties
    }

    bool Window::isVSync() const noexcept {
        return m_properties.vsync;
    }

    void Window::setVSync(bool vsync) {
        m_properties.vsync = vsync;
        onSetVSync(vsync);
    }

    void Window::setIcon(SharedPtr<Image> icon) {
        m_properties.icon = icon;
        onSetIcon(icon);
    }

    SharedPtr<Image> Window::getIcon() const noexcept {
        return m_properties.icon;
    }
}