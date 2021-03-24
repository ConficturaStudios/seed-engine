/**
 * Texture.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_TEXTURE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_TEXTURE_H_

#include "GraphicsAPI.hpp"

namespace seedengine {

    /**
     * The tiling mode used to display a specific texture.
     */
    enum class ETextureTilingMode : uint8 {
        /** The texture will wrap for out of bound UV coordinates. */
        WRAPPED = 1,
        /** The texture will clamp at the edges for out of bound UV coordinates. */
        CLAMPED = 2
    };

    enum class ETextureFilterMode : uint8 {
        NEAREST = 1,
        LINEAR = 2
    };

    enum class ETextureFormat : uint8 {
            // TODO: Associate with ColorFormat object
        LR,
        LRG,
        LRGB,
        LBGR,
        /** Linear RGBA texture format. */
        LRGBA,
        LBGRA,
        R,
        RG,
        RGB,
        BGR,
        RGBA,
        BGRA,
        STENCIL,
        DEPTH_ONLY,
        DEPTH_STENCIL
    };

    struct TextureProperties {
        uint32 width;
        uint32 height;
        ETextureTilingMode tilingMode;
        ETextureFilterMode filterMode;
    };

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Texture {

        public:

        // Destructor

            /**
             * @brief The destructor for Texture objects.
             * @details Called when an instance of Texture is deleted.
             */
            virtual ~Texture() = default;

        // Functions

            [[nodiscard]] virtual uint32_t getWidth() const noexcept = 0;
            [[nodiscard]] virtual uint32_t getHeight() const noexcept = 0;

            //TODO: Standardize ID retrieval between APIs and components (texture, shader, etc.)
            [[nodiscard]] virtual uint32_t getTextureID() const noexcept = 0;

            //TODO: Change type used for passing data
            virtual void setData(void* data, std::size_t size) = 0;

            virtual void bind  (uint8_t slot) const = 0;
            virtual void unbind(uint8_t slot) const = 0;

        // Comparison Operators

            [[nodiscard]] virtual bool operator==(const Texture& rhs) const noexcept = 0;

        // Cast Operators

            [[nodiscard]] virtual operator bool() const noexcept = 0;

        protected:

        private:

    };

    //TODO: Implement Texture1D
    //TODO: Implement Texture1DArray
    //TODO: Implement Texture2D
    //TODO: Implement Texture2DArray
    //TODO: Implement TextureCube
    //TODO: Implement Texture3D
    //TODO: Implement Texture3DArray

    //TODO: Implement Sprites, Sprite sheets, Tile maps, etc (2D module)
}

#endif