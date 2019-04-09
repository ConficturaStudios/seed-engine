#ifndef SEEDENGINE_INCLUDE_WINDOW_H_
#define SEEDENGINE_INCLUDE_WINDOW_H_

#include "Core.hpp"
#include "Parser.hpp"

namespace seedengine {
    
    class WindowProperties {
        
        friend class Window;

    public:

        WindowProperties(const std::string& title,
                            const unsigned int width,
                            const unsigned int height)
            : title_(title), width_(width), height_(height) {}

        static WindowProperties defaultProperties() const {
            return WindowProperties(
                util::parser::ini::DEFAULTS.sections["Window"].string_data["title"],
                util::parser::ini::DEFAULTS.sections["Window"].int_data["width"],
                util::parser::ini::DEFAULTS.sections["Window"].int_data["height"]
            );
        }

    private:

        std::string title_;
        unsigned int width_;
        unsigned int height_;

    }

    class Window {

    public:

    private:

        unsigned int id_;
        WindowProperties properties_;

    }

}

#endif