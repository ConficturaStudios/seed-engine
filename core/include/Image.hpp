#ifndef SEEDENGINE_INCLUDE_IMAGE_H_
#define SEEDENGINE_INLCUDE_IMAGE_H_

#include "Core.hpp"

namespace seedengine {

    // The channel format of an image.
    enum ImageFormat : unsigned int {
        // The image uses the default format in the image.
        DEFAULT = 0,
        // The image is depth only.
        DEPTH = 1,
        // The image contains only rgb channels.
        RGB   = 3,
        // The image contains all rgba channels.
        RGBA  = 4
    };

    //TODO: Create an unloaded image option to conserve memory, load on demand
    //TODO: Protect image from thread competition
    //TODO: Make an image only constructable from the ImageLibrary class
    //TODO: Create procedural image class for generating image files on the disk.

    // An image loaded into memory.
    class Image {

        friend class ImageLibrary;

    public:

        // Gets the path to this image. Returns an empty string if no path exits.
        // @returns: The path to this image.
        inline std::string path() { return path_; }
        // Gets the data of this image.
        // @returns: The data of this image.
        inline unsigned char* data() { return data_; }
        // Gets the width of this image.
        // @returns: The width of this image.
        inline unsigned int width() { return width_; }
        // Gets the height of this image.
        // @returns: The height of this image.
        inline unsigned int height() { return height_; }
        // Gets the number of color channels this image has by default.
        // @returns: The number of color channels this image has by default.
        inline unsigned int channels() { return channels_; }
        // Gets the format forced on this image.
        // @returns: The format forced on this image.
        inline ImageFormat format() { return format_; }

        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

            // Returns this image object as a glfw image.
            // @returns: A GLFWimage with the data of this image.
            GLFWimage glfwImage();

        #endif

    protected:

        // Constructs a new image from data in a file.
        // @param(const std::string&) path: The path to the image to be loaded.
        // @param(ImageFormat) format: Forces the format of the image.
        Image(const std::string&, ImageFormat = ImageFormat::DEFAULT);

        // Constructs a new image from provided data.
        // @param(unsigned char*) data: The data to be used in the image.
        // @param(unsigned int) width: The width of the new image.
        // @param(unsigned int) height: The height of the new image.
        // @param(ImageFormat) format: The format of the image.
        Image(  unsigned char* data, unsigned int width, unsigned int height,
                ImageFormat format = ImageFormat::RGBA)
            : path_(""), data_(data), width_(width), height_(height), channels_(format),
                format_(format) {}

        // The path to this image.
        std::string path_;
        // The data of this image.
        unsigned char* data_;
        // The width of this image.
        unsigned int width_;
        // The height of this image.
        unsigned int height_;
        // The number of color channels this image has by default.
        unsigned int channels_;
        // The format forced on this image.
        ImageFormat format_;

    };

    //TODO: Create a similar reference tracking library for other asset types.
    //TODO: Create base asset class that can be used to create a generic asset library.

    // A library of images in memory.
    class ImageLibrary {

    public:
    
        // Requests an image from the library by path.
        // @param(const std::string&) path: The path to the image.
        // @returns: A pointer to the requested image.
        static std::shared_ptr<Image> request(const std::string&);

        // Loads an image from the disk into memory.
        // @param(const std::string&) path: The path to the file.
        // @param(ImageFormat) format: The format of the image.
        // @returns: A pointer to the loaded image.
        static std::shared_ptr<Image> load(const std::string&, ImageFormat = ImageFormat::DEFAULT);

        // Unloads an image from memory.
        // @param(const std::string&) path: The path of the image to unload.
        static inline void unload(const std::string&);

        // Unloads all images from the library.
        static inline void unloadAll();

        // Unloads all images from the library with fewer references than the threshold.
        // @param(unsinged int) threshold: The minimum number of references required to not unload.
        static inline void unloadUnused(unsigned int = 2);

    private:

        // A map of all images in memory to their path reference.
        static std::map<std::string, std::shared_ptr<Image>> atlas_;

    };

}

#endif