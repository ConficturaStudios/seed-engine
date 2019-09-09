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

        /** The red channel of this color. */
        float r;
        /** The green channel of this color. */
        float g;
        /** The blue channel of this color. */
        float b;
        /** The alpha channel of this color. */
        float a;
        
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

}

#endif