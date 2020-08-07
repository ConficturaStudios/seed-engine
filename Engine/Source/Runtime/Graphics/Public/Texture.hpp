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

    enum class TextureTilingMode : uint8_t {
        WRAPPED = 1,
        CLAMPED = 2
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

    //TODO: Implement Texture2D
    //TODO: Implement Texture2DArray
    //TODO: Implement TextureCube
    //TODO: Implement TextureVolume
    //TODO: Implement RenderTarget (?) (decide how to relate to frame buffer vs texture)
    //TODO: Implement MediaTexture (?) (used for media texture/video display)

}

#endif