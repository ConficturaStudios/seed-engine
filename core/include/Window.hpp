#ifndef SEEDENGINE_INCLUDE_WINDOW_H_
#define SEEDENGINE_INCLUDE_WINDOW_H_

#include "Core.hpp"
#include "Parser.hpp"
#include "Event.hpp"

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
                            const unsigned int width  = util::parser::ini::DEFAULTS.sections["Window"].int_data["width"],
                            const unsigned int height = util::parser::ini::DEFAULTS.sections["Window"].int_data["height"],
                            const bool fullscreen     = util::parser::ini::DEFAULTS.sections["Window"].bool_data["fullscreen"],
                            const bool borderless     = util::parser::ini::DEFAULTS.sections["Window"].bool_data["borderless"],
                            const bool vsync          = util::parser::ini::DEFAULTS.sections["Window"].bool_data["vsync"])
            : title_(title), width_(width), height_(height), borderless_(borderless), fullscreen_(fullscreen), vsync_(vsync) {}


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

    };

    // A window to be displayed on a desktop system.
    class Window {

    public:
        // Window destructor.
        virtual ~Window() {}

        // Updates what is shown on the window.
        void update();
        // Closes this window.
        void close();

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

        // Creates a new window.
        // @param(const WindowProperties&) properties: The properties to assign to this window. Defaults to the default WindowProperty object.
        // @returns: A pointer to a new Window.
        static Window* create(const WindowProperties& preoperties = WindowProperties());

    private:

        // The properties of this window.
        WindowProperties properties_;

    };

}

#endif