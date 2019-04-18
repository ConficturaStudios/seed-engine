#include "Image.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
    #include <stb_image.h>
#endif

namespace seedengine {

    Image::Image(const std::string& path, unsigned int channels)
        : path_(path) {
        int width, height, bpp;
        data_ = stbi_load(path.c_str(), &width, &height, &bpp, channels);

        width_ = width;
        height_ = height;
        bytes_per_pixel_ = bpp;
        channels_ = channels;
    }

}