/**
 * LinearColor.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Color.hpp"

namespace seedengine {

    template class ENGINE_API Color<float, 1>;
    template class ENGINE_API Color<float, 2>;
    template class ENGINE_API Color<float, 3>;
    template class ENGINE_API Color<float, 4>;

    template class ENGINE_API Color<uint8_t, 1>;
    template class ENGINE_API Color<uint8_t, 2>;
    template class ENGINE_API Color<uint8_t, 3>;
    template class ENGINE_API Color<uint8_t, 4>;

    template class ENGINE_API Color<uint16_t, 1>;
    template class ENGINE_API Color<uint16_t, 2>;
    template class ENGINE_API Color<uint16_t, 3>;
    template class ENGINE_API Color<uint16_t, 4>;

    template class ENGINE_API Color<uint32_t, 1>;
    template class ENGINE_API Color<uint32_t, 2>;
    template class ENGINE_API Color<uint32_t, 3>;
    template class ENGINE_API Color<uint32_t, 4>;

    //TODO: Address warning c4661 (Add additional explicit definitions for non-floating point types?)

    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::black         = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0, 0, 0));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::blue          = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0, 0, 1));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::cyan          = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0, 1, 1));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::dark_blue     = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0, 0, 0.5f));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::dark_cyan     = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0, 0.5f, 0.5f));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::dark_green    = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0, 0.5f, 0));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::dark_grey     = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0.25f, 0.25f, 0.25f));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::dark_magenta  = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0.5f, 0, 0.5f));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::dark_red      = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0.5f, 0, 0));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::dark_yellow   = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0.5f, 0.5f, 0));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::green         = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0, 1, 0));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::grey          = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0.5f, 0.5f, 0.5f));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::light_blue    = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0.5f, 0.5f, 1));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::light_cyan    = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0.5f, 1, 1));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::light_green   = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0.5f, 1, 0.5f));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::light_grey    = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(0.75f, 0.75f, 0.75f));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::light_magenta = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(1, 0.5f, 1));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::light_red     = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(1, 0.5f, 0.5f));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::light_yellow  = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(1, 1, 0.5f));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::magenta       = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(1, 0, 1));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::red           = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(1, 0, 0));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::white         = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(1, 1, 1));
    template <typename ChannelType> const Color<ChannelType, 3> Color<ChannelType, 3>::yellow        = ColorBase<ChannelType, 3, Color<ChannelType, 3>>::fromLinearColor(Color<float, 3>(1, 1, 0));

    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::black         = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0, 0, 0, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::blue          = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0, 0, 1, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::clear         = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0, 0, 0, 0));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::cyan          = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0, 1, 1, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::dark_blue     = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0, 0, 0.5f, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::dark_cyan     = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0, 0.5f, 0.5f, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::dark_green    = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0, 0.5f, 0, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::dark_grey     = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0.25f, 0.25f, 0.25f, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::dark_magenta  = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0.5f, 0, 0.5f, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::dark_red      = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0.5f, 0, 0, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::dark_yellow   = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0.5f, 0.5f, 0, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::green         = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0, 1, 0, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::grey          = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0.5f, 0.5f, 0.5f, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::light_blue    = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0.5f, 0.5f, 1, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::light_cyan    = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0.5f, 1, 1, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::light_green   = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0.5f, 1, 0.5f, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::light_grey    = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(0.75f, 0.75f, 0.75f, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::light_magenta = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(1, 0.5f, 1, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::light_red     = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(1, 0.5f, 0.5f, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::light_yellow  = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(1, 1, 0.5f, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::magenta       = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(1, 0, 1, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::red           = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(1, 0, 0, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::white         = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(1, 1, 1, 1));
    template <typename ChannelType> const Color<ChannelType, 4> Color<ChannelType, 4>::yellow        = ColorBase<ChannelType, 4, Color<ChannelType, 4>>::fromLinearColor(Color<float, 4>(1, 1, 0, 1));

    LinearColor::LinearColor() : LinearColor(0, 0, 0, 1) {

    }

    LinearColor::LinearColor(Vector3 vec) : LinearColor(vec.x, vec.y, vec.z) {}

    LinearColor::LinearColor(Vector4 vec) : LinearColor(vec.x, vec.y, vec.z, vec.w) {}

    LinearColor::LinearColor(float r, float g, float b, float a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    const LinearColor LinearColor::black = LinearColor(0, 0, 0, 1);
    const LinearColor LinearColor::blue = LinearColor(0, 0, 1, 1);
    const LinearColor LinearColor::clear = LinearColor(0, 0, 0, 0);
    const LinearColor LinearColor::cyan = LinearColor(0, 1, 1, 1);
    const LinearColor LinearColor::dark_blue = LinearColor(0, 0, 0.5f, 1);
    const LinearColor LinearColor::dark_cyan = LinearColor(0, 0.5f, 0.5f, 1);
    const LinearColor LinearColor::dark_green = LinearColor(0, 0.5f, 0, 1);
    const LinearColor LinearColor::dark_grey = LinearColor(0.25f, 0.25f, 0.25f, 1);
    const LinearColor LinearColor::dark_magenta = LinearColor(0.5f, 0, 0.5f, 1);
    const LinearColor LinearColor::dark_red = LinearColor(0.5f, 0, 0, 1);
    const LinearColor LinearColor::dark_yellow = LinearColor(0.5f, 0.5f, 0, 1);
    const LinearColor LinearColor::green = LinearColor(0, 1, 0, 1);
    const LinearColor LinearColor::grey = LinearColor(0.5f, 0.5f, 0.5f, 1);
    const LinearColor LinearColor::light_blue = LinearColor(0.5f, 0.5f, 1, 1);
    const LinearColor LinearColor::light_cyan = LinearColor(0.5f, 1, 1, 1);
    const LinearColor LinearColor::light_green = LinearColor(0.5f, 1, 0.5f, 1);
    const LinearColor LinearColor::light_grey = LinearColor(0.75f, 0.75f, 0.75f, 1);
    const LinearColor LinearColor::light_magenta = LinearColor(1, 0.5f, 1, 1);
    const LinearColor LinearColor::light_red = LinearColor(1, 0.5f, 0.5f, 1);
    const LinearColor LinearColor::light_yellow = LinearColor(1, 1, 0.5f, 1);
    const LinearColor LinearColor::magenta = LinearColor(1, 0, 1, 1);
    const LinearColor LinearColor::red = LinearColor(1, 0, 0, 1);
    const LinearColor LinearColor::white = LinearColor(1, 1, 1, 1);
    const LinearColor LinearColor::yellow = LinearColor(1, 1, 0, 1);

    LinearColor LinearColor::operator+(const LinearColor& c) const {
        return LinearColor(r + c.r, g + c.g, b + c.b, a + c.a);
    }

    LinearColor LinearColor::operator-(const LinearColor & c) const {
        return LinearColor(r - c.r, g - c.g, b - c.b, a - c.a);
    }

    LinearColor LinearColor::operator*(const LinearColor & c) const {
        return LinearColor(r * c.r, g * c.g, b * c.b, a * c.a);
    }

    LinearColor LinearColor::operator/(const LinearColor & c) const {
        return LinearColor((c.r == 0) ? 0 : r / c.r, (c.g == 0) ? 0 : g / c.g,
            (c.b == 0) ? 0 : b / c.b, (c.a == 0) ? 0 : a / c.a);
    }

    LinearColor LinearColor::operator*(const float& f) const {
        return LinearColor(r * f, g * f, b * f, a * f);
    }

    LinearColor LinearColor::operator/(const float& f) const {
        return LinearColor(r / f, g / f, b / f, a / f);
    }

    std::ostream& operator<<(std::ostream& os, const LinearColor& c) {
        os << (String)c;
        return os;
    }

    LinearColor::operator String() const {
        return "(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + ")";
    }

    LinearColor::operator Vector3() const {
        return Vector3(r, g, b);
    }

    LinearColor::operator Vector4() const {
        return Vector4(r, g, b, a);
    }

    LinearColor operator*(const float& f, const LinearColor& c) {
        return c * f;
    }

}