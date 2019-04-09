#ifndef SEEDENGINE_INCLUDE_WINDOW_H_
#define SEEDENGINE_INCLUDE_WINDOW_H_

#include "Core.hpp"

namespace seedengine {
    
    class WindowProperties {
        
        friend class Window;

    public:

        WindowProperties(std::string title,
                            unsigned int id,
                            unsigned int width,
                            unsigned int height)
            : title_(title), id_(id), width_(width), height_(height) {}

    private:

        std::string title_;
        unsigned int id_;
        unsigned int width_;
        unsigned int hieght_;

    }

    class Window {

    }

}

#endif