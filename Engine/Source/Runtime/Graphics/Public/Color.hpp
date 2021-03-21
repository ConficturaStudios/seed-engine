/**
 * Color.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_COLOR_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_COLOR_H_

#include "GraphicsAPI.hpp"

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "String.hpp"
#include "CommonTraits.hpp"
#include "CommonSTL.hpp"

namespace seedengine {

    /**
     * @brief The data format used by color objects.
     * 
     */
    struct ENGINE_API ColorFormat final {
        /** The number of channels used by this color format. */
        uint8_t channels;
        /** The size of each color channel in bytes. */
        uint8_t channel_size;
    };


    template <typename, std::size_t> class Color;

    // TODO: Redo color classes

    template <typename T, std::size_t N, typename ColorType>
    class ENGINE_API ColorBase {

            static_assert(is_numeric<T>::value, "Colors may only have numeric channel types.");

        protected:

            ColorBase() = default;

        public:

            // Internal Types

            using ChannelType = T;

            // Constants

            static constexpr const std::size_t Channels = N;
            static constexpr const std::size_t ChannelSize = sizeof(ChannelType);
            static constexpr const std::size_t Size = Channels * ChannelSize;

            static constexpr const ColorFormat Format = { Channels, ChannelSize };

            // Operators

            [[nodiscard]] virtual       ChannelType& operator[](std::size_t i)       = 0;
            [[nodiscard]] virtual const ChannelType& operator[](std::size_t i) const = 0;

            [[nodiscard]] ColorType operator+(const ColorType& rhs) const {
                ColorType result;
                for (std::size_t i = 0; i < Channels; i++) {
                    result[i] = this->operator[](i) + rhs[i];
                }
                return result;
            }
            
            [[nodiscard]] ColorType operator-(const ColorType& rhs) const {
                ColorType result;
                for (std::size_t i = 0; i < Channels; i++) {
                    result[i] = this->operator[](i) - rhs[i];
                }
                return result;
            }
            
            [[nodiscard]] ColorType operator*(const ColorType& rhs) const {
                ColorType result;
                for (std::size_t i = 0; i < Channels; i++) {
                    result[i] = this->operator[](i) * rhs[i];
                }
                return result;
            }
            
            [[nodiscard]] ColorType operator/(const ColorType& rhs) const {
                ColorType result;
                for (std::size_t i = 0; i < Channels; i++) {
                    result[i] = this->operator[](i) / rhs[i];
                }
                return result;
            }

            // Friend Operators

            template <typename, std::size_t, typename>
            friend std::ostream& operator<<(std::ostream& lhs, const ColorBase<T, N, ColorType>& rhs);
            template <typename, std::size_t, typename>
            friend std::istream& operator>>(std::istream& lhs,       ColorBase<T, N, ColorType>& rhs);

            // Static Functions

            // Functions
        
            [[nodiscard]] ColorType invert() const {
                ColorType result;
                for (std::size_t i = 0; i < Channels; i++) {
                    if constexpr (std::is_integral<ChannelType>::value) result[i] = std::numeric_limits<ChannelType>::max() - this->operator[](i);
                    else if (std::is_floating_point<ChannelType>::value) result[i] = 1 - this->operator[](i);
                    else result[i] = this->operator[](i);
                }
                return result;
            }

            static ColorType fromLinearColor(const ColorBase<float, N, Color<float, N>>& color) {
                ColorType result;
                if constexpr (std::is_integral<ChannelType>::value) {
                    ChannelType max = std::numeric_limits<ChannelType>::max();
                    for (std::size_t i = 0; i < N; i++) result[i] = (ChannelType)(max * color[i]);
                }
                else if (std::is_floating_point<ChannelType>::value) {
                    for (std::size_t i = 0; i < N; i++) result[i] = (ChannelType)(color[i]);
                }
                return result;
            }

            /*void emplace(const ChannelType* data) {

            }

            void swap(ColorBase<T, N>& other) {

            }

            void copy(const ColorBase<T, N>& source) {

            }*/

    };

    template <typename ChannelType, std::size_t Channels>
    class ENGINE_API Color final : public ColorBase<ChannelType, Channels, Color<ChannelType, Channels>> {

        public:

            Color() : ColorBase() {
                for (std::size_t i = 0; i < Channels; i++) data[i] = 0;
            }

            Color(ChannelType value) : ColorBase() {
                for (std::size_t i = 0; i < Channels; i++) data[i] = value;
            }

            ChannelType data[Channels];

            [[nodiscard]] ChannelType& operator[](std::size_t i) override {
                return data[i];
            }

            [[nodiscard]] const ChannelType& operator[](std::size_t i) const override {
                return data[i];
            }

    };

    template <typename ChannelType>
    class ENGINE_API Color<ChannelType, 1> final : public ColorBase<ChannelType, 1, Color<ChannelType, 1>> {

        public:

            Color() : ColorBase() {
                for (std::size_t i = 0; i < Channels; i++) data[i] = 0;
            }

            Color(ChannelType value) : ColorBase() {
                r = value;
            }

            union {
                ChannelType data[1];
                ChannelType r;
            };

            [[nodiscard]] ChannelType& operator[](std::size_t i) override {
                return data[i];
            }

            [[nodiscard]] const ChannelType& operator[](std::size_t i) const override {
                return data[i];
            }
    };

    template <typename ChannelType>
    class ENGINE_API Color<ChannelType, 2> final : public ColorBase<ChannelType, 2, Color<ChannelType, 2>> {

        public:

            Color() : ColorBase() {
                for (std::size_t i = 0; i < Channels; i++) data[i] = 0;
            }

            Color(ChannelType value) : ColorBase() {
                for (std::size_t i = 0; i < Channels; i++) data[i] = value;
            }

            Color(ChannelType r, ChannelType g) : ColorBase() {
                this->r = r;
                this->g = g;
            }

            union {
                ChannelType data[2];
                struct {
                    ChannelType r;
                    ChannelType g;
                };
            };

            [[nodiscard]] ChannelType& operator[](std::size_t i) override {
                return data[i];
            }

            [[nodiscard]] const ChannelType& operator[](std::size_t i) const override {
                return data[i];
            }
    };

    template <typename ChannelType>
    class ENGINE_API Color<ChannelType, 3> final : public ColorBase<ChannelType, 3, Color<ChannelType, 3>> {

        public:

            constexpr Color() : ColorBase() {
                for (std::size_t i = 0; i < Channels; i++) data[i] = 0;
            }

            constexpr Color(ChannelType value) : ColorBase() {
                for (std::size_t i = 0; i < Channels; i++) data[i] = value;
            }

            constexpr Color(ChannelType r, ChannelType g, ChannelType b) : ColorBase() {
                this->r = r;
                this->g = g;
                this->b = b;
            }

            union {
                ChannelType data[3];
                struct {
                    ChannelType r;
                    ChannelType g;
                    ChannelType b;
                };
            };

            [[nodiscard]] ChannelType& operator[](std::size_t i) override {
                return data[i];
            }

            [[nodiscard]] const ChannelType& operator[](std::size_t i) const override {
                return data[i];
            }
            
        // Static Constants
            
            /** The color black. */
            static const Color black;
            /** The color blue. */
            static const Color blue;
            /** The color cyan. */
            static const Color cyan;
            /** The color dark blue. */
            static const Color dark_blue;
            /** The color dark cyan. */
            static const Color dark_cyan;
            /** The color dark green. */
            static const Color dark_green;
            /** The color dark grey. */
            static const Color dark_grey;
            /** The color dark magenta. */
            static const Color dark_magenta;
            /** The color dark red. */
            static const Color dark_red;
            /** The color dark yellow. */
            static const Color dark_yellow;
            /** The color green. */
            static const Color green;
            /** The color grey. */
            static const Color grey;
            /** The color light blue. */
            static const Color light_blue;
            /** The color light cyan. */
            static const Color light_cyan;
            /** The color light green. */
            static const Color light_green;
            /** The color light grey. */
            static const Color light_grey;
            /** The color light magenta. */
            static const Color light_magenta;
            /** The color light red. */
            static const Color light_red;
            /** The color light yellow. */
            static const Color light_yellow;
            /** The color magenta. */
            static const Color magenta;
            /** The color red. */
            static const Color red;
            /** The color white. */
            static const Color white;
            /** The color yellow. */
            static const Color yellow;

    };

    template <typename ChannelType>
    class ENGINE_API Color<ChannelType, 4> final : public ColorBase<ChannelType, 4, Color<ChannelType, 4>> {

        public:

            constexpr Color() : ColorBase() {
                for (std::size_t i = 0; i < Channels; i++) data[i] = 0;
            }

            constexpr Color(ChannelType value) : ColorBase() {
                for (std::size_t i = 0; i < Channels; i++) data[i] = value;
            }

            constexpr Color(ChannelType r, ChannelType g, ChannelType b) : ColorBase() {
                this->r = r;
                this->g = g;
                this->b = b;
                this->a = 1;
            }

            constexpr Color(ChannelType r, ChannelType g, ChannelType b, ChannelType a) : ColorBase() {
                this->r = r;
                this->g = g;
                this->b = b;

                if constexpr (std::is_integral<ChannelType>::value)
                    this->a = std::numeric_limits<ChannelType>::max();
                else if (std::is_floating_point<ChannelType>::value)
                    this->a = 1;
                else
                    this->a = ChannelType();
            }

            union {
                ChannelType data[4];
                struct {
                    ChannelType r;
                    ChannelType g;
                    ChannelType b;
                    ChannelType a;
                };
            };

            [[nodiscard]] ChannelType& operator[](std::size_t i) override {
                return data[i];
            }

            [[nodiscard]] const ChannelType& operator[](std::size_t i) const override {
                return data[i];
            }

        // Static Constants
            
            /** The color black. */
            static const Color black;
            /** The color blue. */
            static const Color blue;
            /** The color black with no alpha. */
            static const Color clear;
            /** The color cyan. */
            static const Color cyan;
            /** The color dark blue. */
            static const Color dark_blue;
            /** The color dark cyan. */
            static const Color dark_cyan;
            /** The color dark green. */
            static const Color dark_green;
            /** The color dark grey. */
            static const Color dark_grey;
            /** The color dark magenta. */
            static const Color dark_magenta;
            /** The color dark red. */
            static const Color dark_red;
            /** The color dark yellow. */
            static const Color dark_yellow;
            /** The color green. */
            static const Color green;
            /** The color grey. */
            static const Color grey;
            /** The color light blue. */
            static const Color light_blue;
            /** The color light cyan. */
            static const Color light_cyan;
            /** The color light green. */
            static const Color light_green;
            /** The color light grey. */
            static const Color light_grey;
            /** The color light magenta. */
            static const Color light_magenta;
            /** The color light red. */
            static const Color light_red;
            /** The color light yellow. */
            static const Color light_yellow;
            /** The color magenta. */
            static const Color magenta;
            /** The color red. */
            static const Color red;
            /** The color white. */
            static const Color white;
            /** The color yellow. */
            static const Color yellow;
    };


    using LinearColorR    = Color<float, 1>;
    using LinearColorRG   = Color<float, 2>;
    using LinearColorRGB  = Color<float, 3>;
    using LinearColorRGBA = Color<float, 4>;

    /**
     * @brief A 24 bit RGB Color.
     * @details A color with 3 8 bit channels, R, G, and B.
     * 
     * @see LinearColor
     */
    using ColorR8     = Color<uint8_t, 1>;
    /**
     * @brief A 24 bit RGB Color.
     * @details A color with 3 8 bit channels, R, G, and B.
     * 
     * @see LinearColor
     */
    using ColorRG8    = Color<uint8_t, 2>;
    /**
     * @brief A 24 bit RGB Color.
     * @details A color with 3 8 bit channels, R, G, and B.
     * 
     * @see LinearColor
     */
    using ColorRGB8   = Color<uint8_t, 3>;
    /**
     * @brief A 32 bit RGB Color.
     * @details A color with 4 8 bit channels, R, G, B, and A.
     * 
     * @see LinearColor
     */
    using ColorRGBA8  = Color<uint8_t, 4>;

    using ColorR16    = Color<uint16_t, 1>;
    using ColorRG16   = Color<uint16_t, 2>;
    using ColorRGB16  = Color<uint16_t, 3>;
    using ColorRGBA16 = Color<uint16_t, 4>;

    using ColorR32    = Color<uint32_t, 1>;
    using ColorRG32   = Color<uint32_t, 2>;
    using ColorRGB32  = Color<uint32_t, 3>;
    using ColorRGBA32 = Color<uint32_t, 4>;

    //using LinearColor = LinearColorRGBA;

    /**
     * @brief A 24 bit RGB Color.
     * @details A color with 3 8 bit channels, R, G, and B.
     * 
     * @see LinearColor
     */
    class ENGINE_API Color24 final {

        public:

            union {
                uint8_t data[3];
                struct {
                    uint8_t r;
                    uint8_t g;
                    uint8_t b;
                };
            };

            static constexpr const ColorFormat Format = { 3U, sizeof(uint8_t) };

    };

    /**
     * @brief A 32 bit RGBA Color.
     * @details A color with 4 8 bit channels, R, G, B, and A.
     * 
     * @see LinearColor
     */
    class ENGINE_API Color32 final {

        public:

            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;

    };

    /**
     * @brief A 64 bit RGBA Color.
     * @details A color with 4 16 bit channels, R, G, B, and A.
     * 
     * @see LinearColor
     */
    class ENGINE_API Color64 final {

        public:

            uint16_t r;
            uint16_t g;
            uint16_t b;
            uint16_t a;

    };
    
    /**
     * @brief A floating point color.
     * @details An RGBA color with each value stored in a 0 to 1 floating point range.
     * 
     * @see Color32
     */
    class ENGINE_API LinearColor final {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for LinearColor objects.
             * @details Constructs a new LinearColor with default initialization for all members.
             */
            LinearColor();

            /**
             * @brief The copy constructor for LinearColor objects.
             * @details Constructs a new LinearColor by copying an existing LinearColor.
             */
            LinearColor(const LinearColor& ref) = default;
            
            /**
             * @brief The move constructor for LinearColor objects.
             * @details Constructs a new LinearColor by moving the data of a LinearColor into this object.
             */
            LinearColor(LinearColor&& ref) = default;

            /**
             * @brief Construct a new LinearColor object
             * 
             * @param vec A vector to use for the RGB channels of this color, clamped to a 0 to 1 range.
             */
            LinearColor(Vector3 vec);

            /**
             * @brief Construct a new LinearColor object
             * 
             * @param vec A vector to use for the RGBA channels of this color, clamped to a 0 to 1 range.
             */
            LinearColor(Vector4 vec);

            /**
             * @brief Construct a new LinearColor object
             * 
             * @param r The red channel value to use in this Color.
             * @param g The green channel value to use in this Color.
             * @param b The blue channel value to use in this Color.
             * @param a The alpha channel value to use in this Color.
             */
            LinearColor(float r, float g, float b, float a = 1);

        // Properties

            /** The red channel of this color. */
            float r;
            /** The green channel of this color. */
            float g;
            /** The blue channel of this color. */
            float b;
            /** The alpha channel of this color. */
            float a;

        // Static Constants
            
            /** The color black. */
            static const LinearColor black;
            /** The color blue. */
            static const LinearColor blue;
            /** The color black with no alpha. */
            static const LinearColor clear;
            /** The color cyan. */
            static const LinearColor cyan;
            /** The color dark blue. */
            static const LinearColor dark_blue;
            /** The color dark cyan. */
            static const LinearColor dark_cyan;
            /** The color dark green. */
            static const LinearColor dark_green;
            /** The color dark grey. */
            static const LinearColor dark_grey;
            /** The color dark magenta. */
            static const LinearColor dark_magenta;
            /** The color dark red. */
            static const LinearColor dark_red;
            /** The color dark yellow. */
            static const LinearColor dark_yellow;
            /** The color green. */
            static const LinearColor green;
            /** The color grey. */
            static const LinearColor grey;
            /** The color light blue. */
            static const LinearColor light_blue;
            /** The color light cyan. */
            static const LinearColor light_cyan;
            /** The color light green. */
            static const LinearColor light_green;
            /** The color light grey. */
            static const LinearColor light_grey;
            /** The color light magenta. */
            static const LinearColor light_magenta;
            /** The color light red. */
            static const LinearColor light_red;
            /** The color light yellow. */
            static const LinearColor light_yellow;
            /** The color magenta. */
            static const LinearColor magenta;
            /** The color red. */
            static const LinearColor red;
            /** The color white. */
            static const LinearColor white;
            /** The color yellow. */
            static const LinearColor yellow;

        // Arithmatic Operators

            LinearColor operator+(const LinearColor& c) const;
            LinearColor operator-(const LinearColor& c) const;
            LinearColor operator*(const LinearColor& c) const;
            LinearColor operator/(const LinearColor& c) const;

            LinearColor operator*(const float& f) const;
            friend LinearColor operator*(const float& f, const LinearColor& c);
            LinearColor operator/(const float& f) const;

        // IO Operators

            friend std::ostream& operator<<(std::ostream& os, const LinearColor& c);

        // Cast Operators

            operator String() const;

            operator Vector3() const;
            operator Vector4() const;

        // Assignment Operators

            /**
             * @brief The copy assignment operator for Color objects.
             * @details Reassigns the value of this object by copying the data of a Color into this object.
             */
            LinearColor& operator=(const LinearColor& ref) = default;

            /**
             * @brief The move assignment operator for Color objects.
             * @details Reassigns the value of this object by moving the data of a Color into this object.
             */
            LinearColor& operator=(LinearColor&& ref) = default;

        protected:

        private:

    };

    LinearColor operator*(const float& f, const LinearColor& c);

    std::ostream& operator<<(std::ostream& os, const LinearColor& obj);

}

#endif