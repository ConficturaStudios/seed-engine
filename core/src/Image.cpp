#include "Image.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
    #include <stb_image.h>
#endif

namespace seedengine {

    Image::Image(const std::string& path, ImageFormat format)
        : path_(path) {
        int width, height, channels;
        data_ = stbi_load(path.c_str(), &width, &height, &channels, format);

        width_ = width;
        height_ = height;
        channels_ = channels;
        format_ = format;
    }

    #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

        GLFWimage Image::glfwImage() {
            GLFWimage gl_image;
            gl_image.pixels = data();
            gl_image.width = width();
            gl_image.height = height();
            return gl_image;
        }

    #endif

    std::map<std::string, std::shared_ptr<Image>> ImageLibrary::atlas_;

    std::shared_ptr<Image> ImageLibrary::request(const std::string& path) {
        return atlas_[path];
    }

    std::shared_ptr<Image> ImageLibrary::load(const std::string& path, ImageFormat format) {
        std::shared_ptr<Image> newImg(new Image(path, format));
        atlas_[path] = newImg;
        return newImg;
    }

    void ImageLibrary::unload(const std::string& path) {
        atlas_.erase(path);
    }

    void ImageLibrary::unloadAll() {
        atlas_.clear();
    }

    void ImageLibrary::unloadUnused(unsigned int threshold) {
        for (auto const& x : atlas_) {
            if (x.second.use_count() < (int)threshold) atlas_.erase(x.first);
        }
    }

}