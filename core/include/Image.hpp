#ifndef SEEDENGINE_INCLUDE_IMAGE_H_
#define SEEDENGINE_INLCUDE_IMAGE_H_

#include "Core.hpp"

namespace seedengine {

    enum ImageFormat : unsigned int {
        DEPTH = 1,
        RGB   = 3,
        RGBA  = 4
    };

    class Image {

    public:

        // Constructs a new image from data in a file.
        // @param(const std::string&) path: The path to the image to be loaded
        // @param(unsigned int) channels: The format of this image.
        Image(const std::string&, unsigned int);

        // Constructs a new image from provided data.
        // @param(unsigned char*) data: The data to be used in the image.
        // @param(unsigned int) width: The width of the new image.
        // @param(unsigned int) height: The height of the new image.
        // @param(unsigned int) bytes_per_pixel: The number of bytes allocated per channel per pixel.
        // @param(unsigned int) channels: The number of channels in the image.
        Image(unsigned char* data, unsigned int width, unsigned int height,
                unsigned int bytes_per_pixel, unsigned int channels)
            : path_(""), data_(data), width_(width), height_(height), bytes_per_pixel_(bytes_per_pixel),
                channels_(channels) {}

        // Gets the path to this image. Returns an empty string if no path exits.
        // @returns: The path to this image.
        inline std::string path() { return path_; }
        // Gets the data of this image. Returns nullptr if not data exists or loading the image failed.
        // @returns: The data of this image.
        inline unsigned char* data() { return data_; }
        // Gets the width of this image.
        // @returns: The width of this image.
        inline unsigned int width() { return width_; }
        // Gets the height of this image.
        // @returns: The height of this image.
        inline unsigned int height() { return height_; }
        // Gets the number of bytes in each color channel of this image.
        // @returns: The number of bytes in each color channel of this image.
        inline unsigned int bytes_per_pixel() { return bytes_per_pixel_; }
        // Gets the number of channels per pixel of this image.
        // @returns: The number of channels per pixel of this image.
        inline unsigned int channels() { return channels_; }

        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

            // Returns this image object as a glfw image.
            // @returns: A GLFWimage with the data of this image.
            GLFWimage glfwImage();

        #endif

    private:

        std::string path_;
        unsigned char* data_;
        unsigned int width_;
        unsigned int height_;
        unsigned int bytes_per_pixel_;
        unsigned int channels_;

    };

}

#endif