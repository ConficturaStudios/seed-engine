#include "Image.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
    #include <stb_image.h>
#endif

namespace seedengine {

    Image::Image(const string& path) : Asset<unsigned char>(path) {
        format_ = ImageFormat::DEFAULT;
    }

    #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

        GLFWimage* Image::glfwImage() {
            GLFWimage* gl_image = new GLFWimage();
            gl_image->pixels = data();
            gl_image->width = width();
            gl_image->height = height();
            return gl_image;
        }

    #endif

    void Image::load() {
        int width, height, channels;
        delete data_;
        data_ = stbi_load(path_.c_str(), &width, &height, &channels, format_);

        width_ = width;
        height_ = height;
        channels_ = (format_ == 0) ? channels : format_;
    }

    void Image::unload() {
        delete data_;
        data_ = nullptr;
    }

}