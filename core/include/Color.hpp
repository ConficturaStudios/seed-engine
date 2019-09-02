#ifndef SEEDENGINE_INCLUDE_COLOR_H_
#define SEEDENGINE_INCLUDE_COLOR_H_

#include <string>
#include "Property.hpp"
#include "Vector.hpp"

using std::string;

namespace seedengine {

    /**
     * @brief A floating point color.
     * @details An RGBA color with each value stored in a 0 to 1 floating point range.
     */
    class Color {

    public:

        /**
         * @brief Construct a new Color object
         * 
         * @param vec A vector to use for the RGB channels of this color, clamped to a 0 to 1 range.
         */
        Color(Vector3 vec);

        /**
         * @brief Construct a new Color object
         * 
         * @param vec A vector to use for the RGBA channels of this color, clamped to a 0 to 1 range.
         */
        Color(Vector4 vec);

        /**
         * @brief Construct a new Color object
         * 
         * @param r The red channel value to use in this Color.
         * @param g The green channel value to use in this Color.
         * @param b The blue channel value to use in this Color.
         * @param a The alpha channel value to use in this Color.
         */
        Color(float r = 0, float g = 0, float b = 0, float a = 1);

        /**
         * @brief The red channel of this color.
         */
        float r;
        /**
         * @brief The green channel of this color.
         */
        float g;
        /**
         * @brief The blue channel of this color.
         */
        float b;
        /**
         * @brief The alpha channel of this color.
         */
        float a;
        
        static const Color black;
        static const Color blue;
        static const Color clear;
        static const Color cyan;
        static const Color dark_blue;
        static const Color dark_cyan;
        static const Color dark_green;
        static const Color dark_grey;
        static const Color dark_magenta;
        static const Color dark_red;
        static const Color dark_yellow;
        static const Color green;
        static const Color grey;
        static const Color light_blue;
        static const Color light_cyan;
        static const Color light_green;
        static const Color light_grey;
        static const Color light_magenta;
        static const Color light_red;
        static const Color light_yellow;
        static const Color magenta;
        static const Color red;
        static const Color white;
        static const Color yellow;

        Color operator+(const Color& c) const;
        Color operator-(const Color& c) const;
        Color operator*(const Color& c) const;
        Color operator/(const Color& c) const;

        Color operator*(const float& f) const;
        friend Color operator*(const float& f, const Color& c);
        Color operator/(const float& f) const;

        friend std::ostream& operator<<(std::ostream& os, const Color& c);

        operator string() const;

        operator Vector3() const;
        operator Vector4() const;

    protected:

    private:

    };

    Color operator*(const float& f, const Color& c);

    std::ostream& operator<<(std::ostream& os, const Color& obj);

    namespace math {

        // lerp
        inline Color lerp(const Color& a, const Color& b, const float& t) { return a + t * (b - a); }

    }

}

#endif