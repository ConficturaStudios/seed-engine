#ifndef SEEDENGINE_INCLUDE_IMAGE_H_
#define SEEDENGINE_INCLUDE_IMAGE_H_

#include "Core.hpp"
#include "Asset.hpp"

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

    //TODO: Protect image from thread competition
    //TODO: Create procedural image class for generating image files on the disk.

    // An image asset.
    class Image : public Asset<unsigned char> {

        ENGINE_ASSET_BODY()

        friend class ImageLibrary;

    public:

        // Gets the width of this image.
        // @returns: The width of this image.
        inline unsigned int width() const { return width_; }
        // Gets the height of this image.
        // @returns: The height of this image.
        inline unsigned int height() const { return height_; }
        // Gets the number of color channels this image has.
        // @returns: The number of color channels this image has.
        inline unsigned int channels() const { return channels_; }
        // Gets the format this image will follow on load.
        // @returns: The format this image will follow on load.
        inline ImageFormat format() const { return format_; }
        // Sets the format this image will follow on load.
        // @param(ImageFormat) format: The format this image will follow on load.
        inline void setFormat(ImageFormat format) { format_ = format; }

        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

            // Returns this image object as a glfw image.
            // @returns: A pointer to a GLFWimage with the data of this image.
            GLFWimage* glfwImage();

        #endif

    protected:

        // Constructs a new image from data in a file.
        // @param(const string&) path: The path to the image to be loaded.
        Image(const string&);

        // Loads this image into memory.
        void load();
        // Unloads this image from memory.
        void unload();

        // The width of this image.
        unsigned int width_;
        // The height of this image.
        unsigned int height_;
        // The number of color channels this image has by default.
        unsigned int channels_;
        // The format forced on this image.
        ImageFormat format_;

    };

    // A library of image assets.
    /*class ImageLibrary : public AssetLibrary<Image> {

    public:

        // Constructs a new image library.
        ImageLibrary() : AssetLibrary<Image>() {}

    private:

    };*/

}

#endif