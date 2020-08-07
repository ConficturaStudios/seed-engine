/**
 * Image.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_IMAGE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_IMAGE_H_

#include "GraphicsAPI.hpp"
#include "Color.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Image {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Image objects.
             * @details Constructs a new Image with default initialization for all members.
             */
            Image();

            /**
             * @brief The constructor for Image objects with a specific color format.
             * @details Constructs a new Image with the specified color format.
             */
            Image(const ColorFormat& format);

            /**
             * @brief The copy constructor for Image objects.
             * @details Constructs a new Image by copying an existing Image.
             */
            Image(const Image& ref) = default;
            
            /**
             * @brief The move constructor for Image objects.
             * @details Constructs a new Image by moving the data of a Image into this object.
             */
            Image(Image&& ref) = default;

            /**
             * @brief The destructor for Image objects.
             * @details Called when an instance of Image is deleted.
             */
            virtual ~Image();

        // Functions

            void setFormat(const ColorFormat& format);

            void load(const String& filepath);
            void load(const String& filepath, const ColorFormat& format);

            void unload();

        // Getter Functions

            [[nodiscard]] uint32_t width() const;
            [[nodiscard]] uint32_t height() const;

            [[nodiscard]] ColorFormat getFormat() const;

        // Operators

            /**
             * @brief The copy assignment operator for Image objects.
             * @details Reassigns the value of this object by copying the data of a Image into this object.
             */
            Image& operator=(const Image& ref) = default;

            /**
             * @brief The move assignment operator for Image objects.
             * @details Reassigns the value of this object by moving the data of a Image into this object.
             */
            Image& operator=(Image&& ref) = default;

        protected:

        private:

            uint32_t m_width;

            uint32_t m_height;

            ColorFormat m_format;

            uint8_t* buffer;

    };

}

#endif