#include "Color.hpp"

namespace seedengine {

    Color::Color(Vector3 vec) : Color(vec.x, vec.y, vec.z) {}

    Color::Color(Vector4 vec) : Color(vec.x, vec.y, vec.z, vec.w) {}

    Color::Color(float r, float g, float b, float a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    const Color Color::black = Color(0, 0, 0, 1);
    const Color Color::blue = Color(0, 0, 1, 1);
    const Color Color::clear = Color(0, 0, 0, 0);
    const Color Color::cyan = Color(0, 1, 1, 1);
    const Color Color::dark_blue = Color(0, 0, 0.5f, 1);
    const Color Color::dark_cyan = Color(0, 0.5f, 0.5f, 1);
    const Color Color::dark_green = Color(0, 0.5f, 0, 1);
    const Color Color::dark_grey = Color(0.25f, 0.25f, 0.25f, 1);
    const Color Color::dark_magenta = Color(0.5f, 0, 0.5f, 1);
    const Color Color::dark_red = Color(0.5f, 0, 0, 1);
    const Color Color::dark_yellow = Color(0.5f, 0.5f, 0, 1);
    const Color Color::green = Color(0, 1, 0, 1);
    const Color Color::grey = Color(0.5f, 0.5f, 0.5f, 1);
    const Color Color::light_blue = Color(0.5f, 0.5f, 1, 1);
    const Color Color::light_cyan = Color(0.5f, 1, 1, 1);
    const Color Color::light_green = Color(0.5f, 1, 0.5f, 1);
    const Color Color::light_grey = Color(0.75f, 0.75f, 0.75f, 1);
    const Color Color::light_magenta = Color(1, 0.5f, 1, 1);
    const Color Color::light_red = Color(1, 0.5f, 0.5f, 1);
    const Color Color::light_yellow = Color(1, 1, 0.5f, 1);
    const Color Color::magenta = Color(1, 0, 1, 1);
    const Color Color::red = Color(1, 0, 0, 1);
    const Color Color::white = Color(1, 1, 1, 1);
    const Color Color::yellow = Color(1, 1, 0, 1);

    Color Color::operator+(const Color& c) const {
        return Color(r + c.r, g + c.g, b + c.b, a + c.a);
    }

    Color Color::operator-(const Color & c) const {
        return Color(r - c.r, g - c.g, b - c.b, a - c.a);
    }

    Color Color::operator*(const Color & c) const {
        return Color(r * c.r, g * c.g, b * c.b, a * c.a);
    }

    Color Color::operator/(const Color & c) const {
        return Color((c.r == 0) ? 0 : r / c.r, (c.g == 0) ? 0 : g / c.g,
            (c.b == 0) ? 0 : b / c.b, (c.a == 0) ? 0 : a / c.a);
    }

    Color Color::operator*(const float& f) const {
        return Color(r * f, g * f, b * f, a * f);
    }

    Color Color::operator/(const float& f) const {
        return Color(r / f, g / f, b / f, a / f);
    }

    std::ostream& operator<<(std::ostream& os, const Color& c) {
        os << (string)c;
        return os;
    }

    Color::operator string() const {
        return "(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + ")";
    }

    Color::operator Vector3() const {
        return Vector3(r, g, b);
    }

    Color::operator Vector4() const {
        return Vector4(r, g, b, a);
    }

    Color operator*(const float& f, const Color& c) {
        return c * f;
    }

}