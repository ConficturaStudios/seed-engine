#include "Window.hpp"

namespace seedengine {

    void Window::update() {
        EventDispatcher::force(new WindowUpdateEvent(this));
    }

    void Window::close() {
        EventDispatcher::force(new WindowCloseEvent(this));
    }

    Window* Window::create(const WindowProperties& preoperties) {
        Window* window = new Window();
        EventDispatcher::push(new WindowCreatedEvent(window));
        return window;
    }

}