#ifndef SEEDENGINE_INCLUDE_EVENT_H_
#define SEEDENGINE_INCLUDE_EVENT_H_

#include "Core.hpp"
#include "Input.hpp"

namespace seedengine {

    // The type classification assigned to an event.
    enum class EventType : unsigned int {
        // A generic event.
        EVENT         = 0,
        // A system event generated from outside of the program.
        SYSTEM        = FLAG(0),
        // An event generated by client code such as an editor or game.
        CLIENT        = FLAG(1),
        // An event generated within the engine itself.
        ENGINE        = FLAG(2),
        // An event generated by a window under the control of the engine.
        WINDOW        = FLAG(3),
        // An event generated by a hardware peripheral such as a mouse or keyboard.
        PERIPHERAL    = FLAG(4),
        // An event generated by a mouse. This is a type of peripheral event.
        MOUSE         = PERIPHERAL | (PERIPHERAL << 1),
        // An event generated by a keyboard. This is a type of peripheral event.
        KEYBOARD      = PERIPHERAL | (PERIPHERAL << 2),
        // An event generated by a controller. This is a type of peripheral event.
        CONTROLLER    = PERIPHERAL | (PERIPHERAL << 3)
    };

    // An event to be processed by the program.
    class Event {

        friend class EventDispatcher;

    public:

        // Constructs a new Event.
        Event() {}
        virtual ~Event() {}

        // Returns the type of event this is.
        // @returns: The event type.
        virtual EventType getEventType() const = 0;
        // Returns the name of this event.
        // @returns: The name of this event.
        virtual const char* getName() const = 0;
        // Returns the ID of this event.
        // @returns: The ID of this event.
        virtual const unsigned int getId() const = 0;

        // Checks if this event is of a specific type.
        // @param(EventType) type: The type to check against.
        // @returns: True if this is of the passed type.
        inline bool isType(EventType type) const {
            unsigned int uint_type = static_cast<unsigned int>(type);
            return ((static_cast<unsigned int>(getEventType()) & uint_type) == uint_type);
        }

    protected:

        // Has this event been handled?
        bool handled = false;

    };

    // An event dispatcher for handling event buffering and the distribution of events to deligates.
    class EventDispatcher {

    public:

        // Registers a function delegate to a specific Event ID to bind the actions.
        // @param(const unsigned int) event_id: The ID of the event to bind to.
        // @param(std::function<bool(Event&)>) deligate: The function to bind to the event.
        static void registerDeligate(const unsigned int, std::function<void(Event&)>);

        /**
         * @brief Pushs an event into the event queue. This is a non-blocking event.
         *
         * @tparam E The event type to force.
         * @tparam Args The variadic parameter pack used to construct the Event.
         * @tparam std::enable_if<std::is_base_of<Event, E>::value>::type Conditional
         *         compilation based on the base type of E.
         * @param args The arguments used when constructing the Event of type E.
         */
        template <
            class E,
            class... Args,
            typename = typename std::enable_if<std::is_base_of<Event, E>::value>::type
        >
        static void push(Args&&... args) {
            event_buffer.push(std::make_shared<E>(std::forward<Args>(args)...));
        }

        /**
         * @brief Removes and returns the next event in the buffer.
         * 
         * @return std::shared_ptr<Event> The next event in the buffer.
         */
        static std::shared_ptr<Event> pop();

        /**
         * @brief Forces an event to notify its bound functions without adding
         *        it to the queue. This is a blocking event.
         * 
         * @tparam E The event type to force.
         * @tparam Args The variadic parameter pack used to construct the Event.
         * @tparam std::enable_if<std::is_base_of<Event, E>::value>::type Conditional
         *         compilation based on the base type of E.
         * @param args The arguments used when constructing the Event of type E.
         */
        template <
            class E,
            class... Args,
            typename = std::enable_if<std::is_base_of<Event, E>::value>::type
        >
        static void force(Args&&... args) {
            auto event_ptr = std::make_shared<E>(std::forward<Args>(args)...);
            // Iterate through all delegates bound to this event
            for (std::function<void(Event&)> deligate : deligate_regtistry[event_ptr->getId()])
            {
                // Call the function
                deligate(*event_ptr);
            }
        }

        // Runs the deligate functions for every event in the buffer of the specified type.
        // The events are removed after execution of its deligates.
        // @param(unsigned int) type_filter: The types that will be run, skipping all others
        static void run(unsigned int);


    private:

        // The event buffer queue.
        static std::queue<std::shared_ptr<Event>> event_buffer;
        // A mapped registry of all events and their bound functions.
        static std::map<const unsigned int, std::vector<std::function<void(Event&)>>> deligate_regtistry;

    };

    // Event Subclasses

    // An event triggered by the system.
    class SystemEvent : public Event {

    public:

        // Constructs a new System Event.
        SystemEvent() : Event() {}

        // Returns the type of event this is.
        // @returns: The event type.
        EventType getEventType() const { return EventType::SYSTEM; }
        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "System Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::SYSTEM) << 4);

    protected:

    };

    // An event triggered by the client application.
    class ClientEvent : public Event {

    public:

        // Constructs a new Client Event.
        ClientEvent() : Event() {}

        // Returns the type of event this is.
        // @returns: The event type.
        EventType getEventType() const { return EventType::CLIENT; }
        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Client Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::CLIENT) << 4);

    protected:

    };

    // An event triggered by the engine itself.
    class EngineEvent : public Event {

    public:

        // Constructs a new Engine Event.
        EngineEvent() : Event() {}

        // Returns the type of event this is.
        // @returns: The event type.
        EventType getEventType() const { return EventType::ENGINE; }

    protected:

    };

    // An event triggered by an engine logic tick.
    class EngineTickEvent : public EngineEvent {

    public:

        // Constructs a new Engine Tick Event.
        // @param(float) delta_time: The delta time of the application
        EngineTickEvent(float delta_time)
            : EngineEvent(), delta_time_(delta_time) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Engine Tick Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns the delta time during this event.
        // @returns: The delta time when this event occured.
        inline float deltaTime() const { return delta_time_; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::ENGINE) << 4);

    protected:

        // The delta time when this event occured.
        float delta_time_;

    };

    // An event triggered during the render of a frame.
    class EngineRenderEvent : public EngineEvent {

    public:

        // Constructs a new Engine Render Event.
        EngineRenderEvent()
            : EngineEvent() {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Engine Render Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::ENGINE) << 4) | 1;

    protected:

    };

    // An event triggered before rendering a frame.
    class EnginePreRenderEvent : public EngineEvent {

    public:

        // Constructs a new Engine Pre-Render Event.
        EnginePreRenderEvent()
            : EngineEvent() {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Engine Pre-Render Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::ENGINE) << 4) | 2;

    protected:

    };

    // An event triggered after rendering a frame.
    class EnginePostRenderEvent : public EngineEvent {

    public:

        // Constructs a new Engine Post-Render Event.
        EnginePostRenderEvent()
            : EngineEvent() {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Engine Post-Render Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::ENGINE) << 4) | 3;

    protected:

    };

    // An event triggered after loading game data.
    class EngineGameLoadEvent : public EngineEvent {

    public:

        // Constructs a new Engine Game Load Event.
        EngineGameLoadEvent()
            : EngineEvent() {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Engine Game Load Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::ENGINE) << 4) | 4;

    protected:

    };

    class Window;

    // An event triggered by the application window.
    class WindowEvent : public Event {

        friend class Window;

    public:

        // Constructs a new Window Event.
        // @param(Window*) window: A pointer to the affected window.
        WindowEvent(Window* window)
            : Event(), window_(window) {}

        // Returns the type of event this is.
        // @returns: The event type.
        EventType getEventType() const { return EventType::WINDOW; }

        // Returns a pointer to the affected window.
        // @returns: A pointer to the affected window.
        inline Window* window() const { return window_; }

    protected:

        // The affected window
        Window* window_;

    };

    // An event triggered when a window is created.
    class WindowCreatedEvent : public WindowEvent {

    public:

        // Constructs a new Window Created Event.
        // @param(Window*) window: The ID of the affected window.
        WindowCreatedEvent(Window* window)
            : WindowEvent(window) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Window Created Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4);

    protected:

    };

    // An event triggered when a window is resized.
    class WindowResizeEvent : public WindowEvent {

    public:

        // Constructs a new Window Resized Event.
        // @param(Window*) window: The ID of the affected window.
        // @param(unsigned int) width: The new width of the window.
        // @param(nunsigned int) height: The new height of the window.
        WindowResizeEvent(Window* window, unsigned int width, unsigned int height)
            : WindowEvent(window), width_(width), height_(height) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Window Resize Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns the new width.
        // @returns: The new width.
        inline unsigned int width() const { return width_; }
        // Returns the new height.
        // @returns: The new height.
        inline unsigned int height() const { return height_; }

        // The ID number of this event theightpe.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 1;

    protected:

        // The new width.
        unsigned int width_;
        // The new height.
        unsigned int height_;

    };

    // An event triggered when a window is moved.
    class WindowPositionEvent : public WindowEvent {

    public:

        // Constructs a new Window Position Event.
        // @param(Window*) window: The ID of the affected window.
        // @param(unsigned int) x: The new x position of the window.
        // @param(unsigned int) y: The new y position of the window.
        WindowPositionEvent(Window* window, unsigned int x, unsigned int y)
            : WindowEvent(window), x_(x), y_(y) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Window Position Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns the new x position.
        // @returns: The new x position.
        inline unsigned int x() const { return x_; }
        // Returns the new y position.
        // @returns: The new y position.
        inline unsigned int y() const { return y_; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 2;

    protected:

        // The new x position.
        unsigned int x_;
        // The new y position.
        unsigned int y_;

    };

    // An event triggered when a window is closed.
    class WindowCloseEvent : public WindowEvent {

    public:

        // Constructs a new Window Closed Event.
        // @param(Window*) window: The ID of the affected window.
        WindowCloseEvent(Window* window)
            : WindowEvent(window) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Window Close Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 3;

    protected:

    };

    // An event triggered when a window is refreshed.
    class WindowRefreshEvent : public WindowEvent {

    public:

        // Constructs a new Window Refreshd Event.
        // @param(Window*) window: The ID of the affected window.
        WindowRefreshEvent(Window* window)
            : WindowEvent(window) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Window Refresh Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 4;

    protected:

    };

    // An event triggered when a window changes focus.
    class WindowFocusEvent : public WindowEvent {

    public:

        // Constructs a new Window Focus Event.
        // @param(Window*) window: The ID of the affected window.
        // @param(bool) has_focus: True if the window has gained focus.
        WindowFocusEvent(Window* window, bool has_focus)
            : WindowEvent(window), has_focus_(has_focus) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Window Focus Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns true if the window has focus.
        // @returns: True if the window has focus.
        inline bool hasFocus() const { return has_focus_; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 5;

    protected:

        // True if the window has focus.
        bool has_focus_;

    };

    // An event triggered when a window is minimized.
    class WindowMinimizeEvent : public WindowEvent {

    public:

        // Constructs a new Window Minimize Event.
        // @param(Window*) window: The ID of the affected window.
        // @param(bool) minimized: True if the window has been minimized.
        WindowMinimizeEvent(Window* window, bool minimized)
            : WindowEvent(window), minimized_(minimized) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Window Minimze Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns true if the window has been minimized.
        // @returns: True if the window has been minimized.
        inline bool minimized() const { return minimized_; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 6;

    protected:

        // True if the window has been minimized.
        bool minimized_;

    };

    // An event triggered when a window is maximized.
    class WindowMaximizeEvent : public WindowEvent {

    public:

        // Constructs a new Window Maximize Event.
        // @param(Window*) window: The ID of the affected window.
        // @param(bool) maximized: True if the window has been maximized.
        WindowMaximizeEvent(Window* window, bool maximized)
            : WindowEvent(window), maximized_(maximized) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Window Maximize Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns true if the window has been maximized.
        // @returns: True if the window has been maximized.
        inline bool maximized() const { return maximized_; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 7;

    protected:

        // True if the window has been maximized.
        bool maximized_;

    };

    // An event triggered when a window is updated.
    class WindowUpdateEvent : public WindowEvent {

    public:

        // Constructs a new Window Update Event.
        // @param(Window*) window: The ID of the affected window.
        WindowUpdateEvent(Window* window)
            : WindowEvent(window) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Window Update Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 8;

    protected:

    };

    // An event triggered when a window has its content scaled.
    class WindowConentScaleEvent : public WindowEvent {

    public:

        // Constructs a new Window Content Scale Event.
        // @param(Window*) window: The ID of the affected window.
        // @param(float) x_scale: The new x content scale of the window.
        // @param(float) y_scale: The new y content scale of the window.
        WindowConentScaleEvent(Window* window, float x_scale, float y_scale)
            : WindowEvent(window), x_scale_(x_scale), y_scale_(y_scale) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Window Content Scale Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns the new x content scale.
        // @returns: The new x content scale.
        inline float x_scale() const { return x_scale_; }
        // Returns the new y content scale.
        // @returns: The new y content scale.
        inline float y_scale() const { return y_scale_; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::WINDOW) << 4) | 9;

    protected:

        // The new x content scale.
        float x_scale_;
        // The new y content scale.
        float y_scale_;

    };

    // An event triggered by peripheral hardware.
    class PeripheralEvent : public Event {

    public:

        // Constructs a new Peripheral Hardware Event.
        PeripheralEvent() : Event() {}

        // Returns the type of event this is.
        // @returns: The event type.
        EventType getEventType() const { return EventType::PERIPHERAL; }

    protected:

    };

    // An event triggered by mouse input.
    class MouseEvent : public PeripheralEvent {

    public:

        // Constructs a new Mouse Event.
        // @param(float) x: The new x position of the mouse.
        // @param(float) y: The new y position of the mouse.
        MouseEvent(float x, float y)
            : PeripheralEvent(), x_(x), y_(y) {
            cur_x_ = x;
            cur_y_ = y;
        }

        // Returns the type of event this is.
        // @returns: The event type.
        EventType getEventType() const { return EventType::MOUSE; }

        // Returns the new x position of the mouse.
        // @returns: The new x position of the mouse.
        inline float x() const { return x_; }
        // Returns the new y position of the mouse.
        // @returns: The new y position of the mouse.
        inline float y() const { return y_; }

    protected:

        // The new x position of the mouse.
        float x_;
        // The new y position of the mouse.
        float y_;
        // The current x position of the mouse.
        static float cur_x_;
        // The current y position of the mouse.
        static float cur_y_;

    };

    // An event triggered by mouse movement.
    class MouseMovedEvent : public MouseEvent {

    public:

        // Constructs a new Mouse Moved Event.
        // @param(float) x: The new x position of the mouse.
        // @param(float) y: The new y position of the mouse.
        MouseMovedEvent(float x, float y)
            : MouseEvent(x, y) {
            dx_ = x - cur_x_;
            dy_ = y - cur_y_;
        }

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Mouse Moved Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns the change in the x position of the mouse.
        // @returns: The change in the x position of the mouse.
        inline float dx() const { return dx_; }
        // Returns the change in the y position of the mouse.
        // @returns: The change in the y position of the mouse.
        inline float dy() const { return dy_; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::MOUSE) << 4);

    private:

        // The change in the x position of the mouse.
        float dx_;
        // The change in the y position of the mouse.
        float dy_;

    };

    // An event triggered by a mouse button.
    class MouseButtonEvent : public MouseEvent {

    public:

        // Constructs a new Mouse Button Event.
        // @param(unsigned int) button_id: The ID of the button affected.
        // @param(input::ButtonState) state: The state of the affected button.
        // @param(unsigned int) mods: Applied modifier flags.
        MouseButtonEvent(unsigned int button_id, input::ButtonState state, unsigned int mods)
            : MouseEvent(cur_x_, cur_y_), button_id_(button_id), state_(state), mods_(mods) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Mouse Button Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns the ID of the button affected.
        // @returns: The ID of the button affected.
        inline unsigned int buttonId() const { return button_id_; }
        // Returns the state of the affected button.
        // @returns: The state of the affected button.
        inline input::ButtonState state() const { return state_; }
        // Returns the applied modifiers.
        // @returns: The applied modifiers.
        inline unsigned int mods() const { return mods_; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::MOUSE) << 4) | 1;

    private:

        // The ID of the button affected.
        unsigned int button_id_;
        // The state of the affected button.
        input::ButtonState state_;
        // Any shift, ctrl, alt, super modifier flags applied to the key.
        unsigned int mods_;

    };

    // An event triggered by mouse movement.
    class MouseScrolledEvent : public MouseEvent {

    public:

        // Constructs a new Mouse Scrolled Event.
        // @param(float) x_offset: The amount to scroll in the x direction.
        // @param(float) y_offset: The amount to scroll in the y direction.
        MouseScrolledEvent(float x_offset, float y_offset)
            : MouseEvent(cur_x_, cur_y_), x_offset_(x_offset), y_offset_(y_offset) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Mouse Moved Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns the amount to scroll in the x direction.
        // @returns: The amount to scroll in the x direction.
        inline float x_offset() const { return x_offset_; }
        // Returns the amount to scroll in the y direction.
        // @returns: The amount to scroll in the y direction.
        inline float y_offset() const { return y_offset_; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::MOUSE) << 4) | 2;

    private:

        // The amount to scroll in the x direction.
        float x_offset_;
        // The amount to scroll in the y direction.
        float y_offset_;

    };

    // An event triggered by a keyboard action.
    class KeyboardEvent : public PeripheralEvent {

    public:

        // Constructs a new Keyboard Event.
        // @param(unsinged int) keycode: The keycode of the affected key.
        // @param(unsinged int) repeat: The repeat count.
        // @param(input::ButtonState) state: The state of the affected key.
        // @param(unsigned int) mods: Applied modifier flags.
        KeyboardEvent(unsigned int keycode, unsigned int repeat, input::ButtonState state, unsigned int mods)
            : PeripheralEvent(), keycode_(keycode), repeat_(repeat), state_(state), mods_(mods) {}


        // Returns the type of event this is.
        // @returns: The event type.
        EventType getEventType() const { return EventType::KEYBOARD; }
        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Keyboard Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns the keycode of the affected key.
        // @returns: The keycode of the affected key.
        inline unsigned int keycode() const { return keycode_; }
        // Returns the repeat count.
        // @returns: The repeat count.
        inline unsigned int repeat() const { return repeat_; }
        // Returns the state of the affected key.
        // @returns: The state of the affected key.
        inline input::ButtonState state() const { return state_; }
        // Returns the applied modifiers.
        // @returns: The applied modifiers.
        inline unsigned int mods() const { return mods_; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::KEYBOARD) << 4);

    private:

        // The keycode of the affected key.
        unsigned int keycode_;
        // The repeat count.
        unsigned int repeat_;
        // The state of the affected key.
        input::ButtonState state_;
        // Any shift, ctrl, alt, super modifier flags applied to the key.
        unsigned int mods_;

    };

    // An event triggered by a controller action.
    class ControllerEvent : public PeripheralEvent {

    public:

        // Constructs a new Controller Event.
        // @param(unsinged int) controller_id: The ID of the affected controller.
        ControllerEvent(unsigned int controller_id)
            : PeripheralEvent(), controller_id_(controller_id) {}


        // Returns the type of event this is.
        // @returns: The event type.
        EventType getEventType() const { return EventType::CONTROLLER; }

        // Returns the ID of the affected controller.
        // @returns: The ID of the affected controller.
        inline unsigned int controllerId() const { return controller_id_; }

    protected:

        // The ID of the affected controller.
        unsigned int controller_id_;

    };

    // An event triggered by a controller button action.
    class ControllerButtonEvent : public ControllerEvent {

    public:

        // Constructs a new Controller Button Event.
        // @param(unsinged int) controller_id: The ID of the affected controller.
        // @param(unsinged int) button_id: The ID of the affected button.
        // @param(input::ButtonState) state: The state of the affected button.
        ControllerButtonEvent(unsigned int controller_id, unsigned int button_id, input::ButtonState state)
            : ControllerEvent(controller_id), button_id_(button_id), state_(state) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Controller Button Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns the ID of the button affected.
        // @returns: The ID of the button affected.
        inline unsigned int buttonId() const { return button_id_; }
        // Returns the state of the affected button.
        // @returns: The state of the affected button.
        inline input::ButtonState state() const { return state_; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::CONTROLLER) << 4);

    private:

        // The ID of the button affected.
        unsigned int button_id_;
        // The state of the affected button.
        input::ButtonState state_;

    };

    // An event triggered by a controller axis change, such as moving a joystick.
    class ControllerAxisEvent : public ControllerEvent {

    public:

        // Constructs a new Controller Axis Event.
        // @param(unsinged int) controller_id: The ID of the affected controller.
        // @param(unsinged int) axis_id: The ID of the affected axis.
        // @param(float) x: The x input of the axis.
        // @param(float) y: The y input of the axis.
        ControllerAxisEvent(unsigned int controller_id, unsigned int axis_id, float x, float y)
            : ControllerEvent(controller_id), axis_id_(axis_id), x_(x), y_(y) {}

        // Returns the name of this event.
        // @returns: The name of this event.
        const char* getName() const { return "Controller Axis Event"; }
        // Returns the ID of this event.
        // @returns: The ID of this event.
        const unsigned int getId() const { return EVENT_ID; }

        // Returns the ID of the affected axis.
        // @returns: The ID of the affected axis.
        inline unsigned int axisId() const { return axis_id_; }
        // Returns the x input of the axis.
        // @returns: The x input of the axis.
        inline float x() const { return x_; }
        // Returns the y input of the axis.
        // @returns: The y input of the axis.
        inline float y() const { return y_; }

        // The ID number of this event type.
        static const unsigned int EVENT_ID = (static_cast<unsigned int>(EventType::CONTROLLER) << 4) | 1;

    private:

        // The ID of the affected axis.
        unsigned int axis_id_;
        // The x input of the axis.
        float x_;
        // The y input of the axis.
        float y_;

    };
}

#endif