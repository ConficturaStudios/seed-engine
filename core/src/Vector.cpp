#include "Vector.hpp"

namespace seedengine {
    // Define constants ------------------------------------------------------

    const Vector2 Vector2::UP = Vector2(0, 1);
    const Vector2 Vector2::DOWN = Vector2(0, -1);
    const Vector2 Vector2::LEFT = Vector2(-1, 0);
    const Vector2 Vector2::RIGHT = Vector2(1, 0);
    const Vector2 Vector2::ONE = Vector2(1);
    const Vector2 Vector2::ZERO = Vector2(0);

    const Vector3 Vector3::UP = Vector3(0, 1, 0);
    const Vector3 Vector3::DOWN = Vector3(0, -1, 0);
    const Vector3 Vector3::LEFT = Vector3(-1, 0, 0);
    const Vector3 Vector3::RIGHT = Vector3(1, 0, 0);
    const Vector3 Vector3::FORWARD = Vector3(0, 0, 1);
    const Vector3 Vector3::BACKWARD = Vector3(0, 0, -1);
    const Vector3 Vector3::ONE = Vector3(1);
    const Vector3 Vector3::ZERO = Vector3(0);

    const Vector4 Vector4::UP = Vector4(0, 1, 0, 0);
    const Vector4 Vector4::DOWN = Vector4(0, -1, 0, 0);
    const Vector4 Vector4::LEFT = Vector4(-1, 0, 0, 0);
    const Vector4 Vector4::RIGHT = Vector4(1, 0, 0, 0);
    const Vector4 Vector4::FORWARD = Vector4(0, 0, 1, 0);
    const Vector4 Vector4::BACKWARD = Vector4(0, 0, -1, 0);
    const Vector4 Vector4::KATA = Vector4(0, 0, 0, 1);
    const Vector4 Vector4::ANA = Vector4(0, 0, 0, -1);
    const Vector4 Vector4::ONE = Vector4(1);
    const Vector4 Vector4::ZERO = Vector4(0);


    const Vector2Int Vector2Int::UP = Vector2Int(0, 1);
    const Vector2Int Vector2Int::DOWN = Vector2Int(0, -1);
    const Vector2Int Vector2Int::LEFT = Vector2Int(-1, 0);
    const Vector2Int Vector2Int::RIGHT = Vector2Int(1, 0);
    const Vector2Int Vector2Int::ONE = Vector2Int(1);
    const Vector2Int Vector2Int::ZERO = Vector2Int(0);

    const Vector3Int Vector3Int::UP = Vector3Int(0, 1, 0);
    const Vector3Int Vector3Int::DOWN = Vector3Int(0, -1, 0);
    const Vector3Int Vector3Int::LEFT = Vector3Int(-1, 0, 0);
    const Vector3Int Vector3Int::RIGHT = Vector3Int(1, 0, 0);
    const Vector3Int Vector3Int::FORWARD = Vector3Int(0, 0, 1);
    const Vector3Int Vector3Int::BACKWARD = Vector3Int(0, 0, -1);
    const Vector3Int Vector3Int::ONE = Vector3Int(1);
    const Vector3Int Vector3Int::ZERO = Vector3Int(0);

    const Vector4Int Vector4Int::UP = Vector4Int(0, 1, 0, 0);
    const Vector4Int Vector4Int::DOWN = Vector4Int(0, -1, 0, 0);
    const Vector4Int Vector4Int::LEFT = Vector4Int(-1, 0, 0, 0);
    const Vector4Int Vector4Int::RIGHT = Vector4Int(1, 0, 0, 0);
    const Vector4Int Vector4Int::FORWARD = Vector4Int(0, 0, 1, 0);
    const Vector4Int Vector4Int::BACKWARD = Vector4Int(0, 0, -1, 0);
    const Vector4Int Vector4Int::KATA = Vector4Int(0, 0, 0, 1);
    const Vector4Int Vector4Int::ANA = Vector4Int(0, 0, 0, -1);
    const Vector4Int Vector4Int::ONE = Vector4Int(1);
    const Vector4Int Vector4Int::ZERO = Vector4Int(0);

    // Vector2 ---------------------------------------------------------------

    // Constructors

    Vector2::Vector2() : Vector2(0) {};

    Vector2::Vector2(const float& value) : Vector2(value, value) {};

    Vector2::Vector2(const float& x, const float& y) {
        this->x = x;
        this->y = y;
        this->elements_[0] = &(this->x);
        this->elements_[1] = &(this->y);
    }

    // Static Functions

    float Vector2::angle(const Vector2& v0, const Vector2& v1) {
        return math::acos(dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
    }

    float Vector2::distance(const Vector2& v0, const Vector2& v1) {
        return magnitude(v0 - v1);
    }

    float Vector2::dot(const Vector2& v0, const Vector2& v1) {
        float t = 0;
        for (int i = 0; i < SIZE; i++) {
            t += (*(v0.elements_[i])) * (*(v1.elements_[i]));
        }
        return t;
    }

    float Vector2::magnitude(const Vector2& v) {
        return math::sqrt(dot(v, v));
    }

    Vector2 Vector2::normalize(const Vector2& v) {
        return v / magnitude(v);
    }

    Vector2 Vector2::reflect(const Vector2& incident, const Vector2& normal) {
        return incident - (2 * dot(normal, incident) * normal);
    }

    Vector2 Vector2::refract(const Vector2& incident, const Vector2& normal, const float& eta) {
        float d = dot(normal, incident);
        float t = 1 - (eta * eta * (1 - d * d));
        if (t < 0) return Vector2();
        else return (eta * incident) - ((eta * d + math::sqrt(t)) * normal);
    }

    Vector2 Vector2::project(const Vector2& a, const Vector2& b) {
        return b * (dot(a, b) / dot(b, b));
    }

    Vector2 Vector2::ortho(const Vector2& a, const Vector2& b) {
        return a - (b * (dot(a, b) / dot(b, b)));
    }

    // Member Functions

    float Vector2::angle(const Vector2& v) const {
        return angle(*this, v);
    }

    float Vector2::distance(const Vector2& v) const {
        return distance(*this, v);
    }

    float Vector2::dot(const Vector2& v) const {
        return dot(*this, v);
    }

    float Vector2::magnitude() const {
        return magnitude(*this);
    }

    Vector2 Vector2::normalize() const {
        return normalize(*this);
    }

    // Accessor operators

    float& Vector2::operator[](const int& index) {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return *(elements_[index]);
    }

    const float& Vector2::operator[](const int& index) const {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return *(elements_[index]);
    }

    // Arithmatic operators

    Vector2 Vector2::operator+(const Vector2& vec) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) + (*(vec.elements_[i]));
        }
        return v;
    }

    Vector2 Vector2::operator+(const float& f) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) + f;
        }
        return v;
    }

    Vector2 Vector2::operator-(const Vector2& vec) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) - (*(vec.elements_[i]));
        }
        return v;
    }

    Vector2 Vector2::operator-(const float& f) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) - f;
        }
        return v;
    }

    Vector2 Vector2::operator/(const Vector2& vec) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) / (*(vec.elements_[i]));
        }
        return v;
    }

    Vector2 Vector2::operator/(const float& f) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) / f;
        }
        return v;
    }

    Vector2 Vector2::operator*(const Vector2& vec) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) * (*(vec.elements_[i]));
        }
        return v;
    }

    Vector2 Vector2::operator*(const float& f) const {
        Vector2 v = Vector2();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) * f;
        }
        return v;
    }

    // Boolean operators

    bool Vector2::operator==(const Vector2& vec) const {
        bool e = true;
        for (int i = 0; i < SIZE; i++) {
            e &= ((*(this->elements_[i])) == (*(vec.elements_[i])));
        }
        return e;
    }

    bool Vector2::operator!=(const Vector2& vec) const {
        return !(*this == vec);
    }

    // Assignment operators

    Vector2& Vector2::operator=(const Vector2& vec) {
        this->x = vec.x;
        this->y = vec.y;
        return *this;
    }

    Vector2& Vector2::operator=(const float& value) {
        for (int i = 0; i < SIZE; i++) {
            *(elements_[i]) = value;
        }
        return *this;
    }

    // Cast operators

    Vector2::operator Vector3() const {
        return Vector3(x, y, 0);
    }

    Vector2::operator Vector4() const {
        return Vector4(x, y, 0, 0);
    }

    Vector2::operator Vector2Int() const {
        return Vector2Int((int)x, (int)y);
    }

    Vector2::operator Vector3Int() const {
        return Vector3Int((int)x, (int)y, 0);
    }

    Vector2::operator Vector4Int() const {
        return Vector4Int((int)x, (int)y, 0, 0);
    }

    Vector2::operator string() const {
        std::stringstream ss("<");
        for (int i = 0; i < SIZE; i++) {
            ss << *(this->elements_[i]);
            if (i < SIZE - 1) ss << ", ";
        }
        ss << ">";
        return ss.str();
    }

    // Vector3 ---------------------------------------------------------------

    // Constructors

    Vector3::Vector3() : Vector3(0) {};

    Vector3::Vector3(const float& value) : Vector3(value, value, value) {};

    Vector3::Vector3(const float& x, const float& y, const float& z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->elements_[0] = &(this->x);
        this->elements_[1] = &(this->y);
        this->elements_[2] = &(this->z);
    }

    // Static Functions

    float Vector3::angle(const Vector3& v0, const Vector3& v1) {
        return math::acos(dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
    }

    float Vector3::distance(const Vector3& v0, const Vector3& v1) {
        return magnitude(v0 - v1);
    }

    float Vector3::dot(const Vector3& v0, const Vector3& v1) {
        float t = 0;
        for (int i = 0; i < SIZE; i++) {
            t += (*(v0.elements_[i])) * (*(v1.elements_[i]));
        }
        return t;
    }

    Vector3 Vector3::cross(const Vector3& v0, const Vector3& v1) {
        return Vector3(
            v0.y * v1.z - v0.z * v1.y,
            v0.z * v1.x - v0.x * v1.z,
            v0.x * v1.y - v0.y * v1.x
        );
    }

    float Vector3::magnitude(const Vector3& v) {
        return math::sqrt(dot(v, v));
    }

    Vector3 Vector3::normalize(const Vector3& v) {
        return v / magnitude(v);
    }

    Vector3 Vector3::reflect(const Vector3& incident, const Vector3& normal) {
        return incident - (2 * dot(normal, incident) * normal);
    }

    Vector3 Vector3::refract(const Vector3& incident, const Vector3& normal, const float& eta) {
        float d = dot(normal, incident);
        float t = 1 - (eta * eta * (1 - d * d));
        if (t < 0) return Vector3();
        else return (eta * incident) - ((eta * d + math::sqrt(t)) * normal);
    }

    Vector3 Vector3::project(const Vector3& a, const Vector3& b) {
        return b * (dot(a, b) / dot(b, b));
    }

    Vector3 Vector3::ortho(const Vector3& a, const Vector3& b) {
        return a - (b * (dot(a, b) / dot(b, b)));
    }

    // Member Functions

    float Vector3::angle(const Vector3& v) const {
        return angle(*this, v);
    }

    float Vector3::distance(const Vector3& v) const {
        return distance(*this, v);
    }

    float Vector3::dot(const Vector3& v) const {
        return dot(*this, v);
    }

    Vector3 Vector3::cross(const Vector3& v) const {
        return cross(*this, v);
    }

    float Vector3::magnitude() const {
        return magnitude(*this);
    }

    Vector3 Vector3::normalize() const {
        return normalize(*this);
    }

    // Accessor operators

    float& Vector3::operator[](const int& index) {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return *(elements_[index]);
    }

    const float& Vector3::operator[](const int& index) const {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return *(elements_[index]);
    }

    // Arithmatic operators

    Vector3 Vector3::operator+(const Vector3& vec) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) + (*(vec.elements_[i]));
        }
        return v;
    }

    Vector3 Vector3::operator+(const float& f) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) + f;
        }
        return v;
    }

    Vector3 Vector3::operator-(const Vector3& vec) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) - (*(vec.elements_[i]));
        }
        return v;
    }

    Vector3 Vector3::operator-(const float& f) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) - f;
        }
        return v;
    }

    Vector3 Vector3::operator/(const Vector3& vec) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) / (*(vec.elements_[i]));
        }
        return v;
    }

    Vector3 Vector3::operator/(const float& f) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) / f;
        }
        return v;
    }

    Vector3 Vector3::operator*(const Vector3& vec) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) * (*(vec.elements_[i]));
        }
        return v;
    }

    Vector3 Vector3::operator*(const float& f) const {
        Vector3 v = Vector3();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) * f;
        }
        return v;
    }

    // Boolean operators

    bool Vector3::operator==(const Vector3& vec) const {
        bool e = true;
        for (int i = 0; i < SIZE; i++) {
            e &= ((*(this->elements_[i])) == (*(vec.elements_[i])));
        }
        return e;
    }

    bool Vector3::operator!=(const Vector3& vec) const {
        return !(*this == vec);
    }

    // Assignment operators

    Vector3& Vector3::operator=(const Vector3& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        return *this;
    }

    Vector3& Vector3::operator=(const float& value) {
        for (int i = 0; i < SIZE; i++) {
            *(elements_[i]) = value;
        }
        return *this;
    }

    // Cast operators

    Vector3::operator Vector2() const {
        return Vector2(x, y);
    }

    Vector3::operator Vector4() const {
        return Vector4(x, y, z, 0);
    }

    Vector3::operator Vector2Int() const {
        return Vector2Int((int)x, (int)y);
    }

    Vector3::operator Vector3Int() const {
        return Vector3Int((int)x, (int)y, (int)z);
    }

    Vector3::operator Vector4Int() const {
        return Vector4Int((int)x, (int)y, (int)z, 0);
    }

    Vector3::operator string() const {
        std::stringstream ss("<");
        for (int i = 0; i < SIZE; i++) {
            ss << *(this->elements_[i]);
            if (i < SIZE - 1) ss << ", ";
        }
        ss << ">";
        return ss.str();
    }

    // Vector4 ---------------------------------------------------------------

    // Constructors

    Vector4::Vector4() : Vector4(0) {};

    Vector4::Vector4(const float& value) : Vector4(value, value, value, value) {};

    Vector4::Vector4(const float& x, const float& y, const float& z, const float& w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        this->elements_[0] = &(this->x);
        this->elements_[1] = &(this->y);
        this->elements_[2] = &(this->z);
        this->elements_[3] = &(this->w);
    }

    // Static Functions

    float Vector4::angle(const Vector4& v0, const Vector4& v1) {
        return math::acos(dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
    }

    float Vector4::distance(const Vector4& v0, const Vector4& v1) {
        return magnitude(v0 - v1);
    }

    float Vector4::dot(const Vector4& v0, const Vector4& v1) {
        float t = 0;
        for (int i = 0; i < SIZE; i++) {
            t += (*(v0.elements_[i])) * (*(v1.elements_[i]));
        }
        return t;
    }

    float Vector4::magnitude(const Vector4& v) {
        return math::sqrt(dot(v, v));
    }

    Vector4 Vector4::normalize(const Vector4& v) {
        return v / magnitude(v);
    }

    Vector4 Vector4::reflect(const Vector4& incident, const Vector4& normal) {
        return incident - (2 * dot(normal, incident) * normal);
    }

    Vector4 Vector4::refract(const Vector4& incident, const Vector4& normal, const float& eta) {
        float d = dot(normal, incident);
        float t = 1 - (eta * eta * (1 - d * d));
        if (t < 0) return Vector4();
        else return (eta * incident) - ((eta * d + math::sqrt(t)) * normal);
    }

    Vector4 Vector4::project(const Vector4& a, const Vector4& b) {
        return b * (dot(a, b) / dot(b, b));
    }

    Vector4 Vector4::ortho(const Vector4& a, const Vector4& b) {
        return a - (b * (dot(a, b) / dot(b, b)));
    }

    // Member Functions

    float Vector4::angle(const Vector4& v) const {
        return angle(*this, v);
    }

    float Vector4::distance(const Vector4& v) const {
        return distance(*this, v);
    }

    float Vector4::dot(const Vector4& v) const {
        return dot(*this, v);
    }

    float Vector4::magnitude() const {
        return magnitude(*this);
    }

    Vector4 Vector4::normalize() const {
        return normalize(*this);
    }

    // Accessor operators

    float& Vector4::operator[](const int& index) {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return *(elements_[index]);
    }

    const float& Vector4::operator[](const int& index) const {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return *(elements_[index]);
    }

    // Arithmatic operators

    Vector4 Vector4::operator+(const Vector4& vec) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) + (*(vec.elements_[i]));
        }
        return v;
    }

    Vector4 Vector4::operator+(const float& f) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) + f;
        }
        return v;
    }

    Vector4 Vector4::operator-(const Vector4& vec) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) - (*(vec.elements_[i]));
        }
        return v;
    }

    Vector4 Vector4::operator-(const float& f) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) - f;
        }
        return v;
    }

    Vector4 Vector4::operator/(const Vector4& vec) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) / (*(vec.elements_[i]));
        }
        return v;
    }

    Vector4 Vector4::operator/(const float& f) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) / f;
        }
        return v;
    }

    Vector4 Vector4::operator*(const Vector4& vec) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) * (*(vec.elements_[i]));
        }
        return v;
    }

    Vector4 Vector4::operator*(const float& f) const {
        Vector4 v = Vector4();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) * f;
        }
        return v;
    }

    // Boolean operators

    bool Vector4::operator==(const Vector4& vec) const {
        bool e = true;
        for (int i = 0; i < SIZE; i++) {
            e &= ((*(this->elements_[i])) == (*(vec.elements_[i])));
        }
        return e;
    }

    bool Vector4::operator!=(const Vector4& vec) const {
        return !(*this == vec);
    }

    // Assignment operators

    Vector4& Vector4::operator=(const Vector4& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        this->w = vec.w;
        return *this;
    }

    Vector4& Vector4::operator=(const float& value) {
        for (int i = 0; i < SIZE; i++) {
            *(elements_[i]) = value;
        }
        return *this;
    }

    // Cast operators

    Vector4::operator Vector2() const {
        return Vector2(x, y);
    }

    Vector4::operator Vector3() const {
        return Vector3(x, y, z);
    }

    Vector4::operator Vector2Int() const {
        return Vector2Int((int)x, (int)y);
    }

    Vector4::operator Vector3Int() const {
        return Vector3Int((int)x, (int)y, (int)z);
    }

    Vector4::operator Vector4Int() const {
        return Vector4Int((int)x, (int)y, (int)z, (int)w);
    }

    Vector4::operator string() const {
        std::stringstream ss("<");
        for (int i = 0; i < SIZE; i++) {
            ss << *(this->elements_[i]);
            if (i < SIZE - 1) ss << ", ";
        }
        ss << ">";
        return ss.str();
    }

    // Vector2Int ---------------------------------------------------------------

    // Constructors

    Vector2Int::Vector2Int() : Vector2Int(0) {};

    Vector2Int::Vector2Int(const int& value) : Vector2Int(value, value) {};

    Vector2Int::Vector2Int(const int& x, const int& y) {
        this->x = x;
        this->y = y;
        this->elements_[0] = &(this->x);
        this->elements_[1] = &(this->y);
    }

    // Static Functions

    float Vector2Int::angle(const Vector2Int& v0, const Vector2Int& v1) {
        return math::acos((float)dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
    }

    float Vector2Int::distance(const Vector2Int& v0, const Vector2Int& v1) {
        return magnitude(v0 - v1);
    }

    int Vector2Int::dot(const Vector2Int& v0, const Vector2Int& v1) {
        int t = 0;
        for (int i = 0; i < SIZE; i++) {
            t += (*(v0.elements_[i])) * (*(v1.elements_[i]));
        }
        return t;
    }

    float Vector2Int::magnitude(const Vector2Int& v) {
        return math::sqrt((float)dot(v, v));
    }

    // Member Functions

    float Vector2Int::angle(const Vector2Int& v) const {
        return angle(*this, v);
    }

    float Vector2Int::distance(const Vector2Int& v) const {
        return distance(*this, v);
    }

    int Vector2Int::dot(const Vector2Int& v) const {
        return dot(*this, v);
    }

    float Vector2Int::magnitude() const {
        return magnitude(*this);
    }

    // Accessor operators

    int& Vector2Int::operator[](const int& index) {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return *(elements_[index]);
    }

    const int& Vector2Int::operator[](const int& index) const {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return *(elements_[index]);
    }

    // Arithmatic operators

    Vector2Int Vector2Int::operator+(const Vector2Int& vec) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) + (*(vec.elements_[i]));
        }
        return v;
    }

    Vector2Int Vector2Int::operator+(const int& f) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) + f;
        }
        return v;
    }

    Vector2Int Vector2Int::operator-(const Vector2Int& vec) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) - (*(vec.elements_[i]));
        }
        return v;
    }

    Vector2Int Vector2Int::operator-(const int& f) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) - f;
        }
        return v;
    }

    Vector2Int Vector2Int::operator/(const Vector2Int& vec) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) / (*(vec.elements_[i]));
        }
        return v;
    }

    Vector2Int Vector2Int::operator/(const int& f) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) / f;
        }
        return v;
    }

    Vector2Int Vector2Int::operator*(const Vector2Int& vec) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) * (*(vec.elements_[i]));
        }
        return v;
    }

    Vector2Int Vector2Int::operator*(const int& f) const {
        Vector2Int v = Vector2Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) * f;
        }
        return v;
    }

    // Boolean operators

    bool Vector2Int::operator==(const Vector2Int& vec) const {
        bool e = true;
        for (int i = 0; i < SIZE; i++) {
            e &= ((*(this->elements_[i])) == (*(vec.elements_[i])));
        }
        return e;
    }

    bool Vector2Int::operator!=(const Vector2Int& vec) const {
        return !(*this == vec);
    }

    // Assignment operators

    Vector2Int& Vector2Int::operator=(const Vector2Int& vec) {
        this->x = vec.x;
        this->y = vec.y;
        return *this;
    }

    Vector2Int& Vector2Int::operator=(const int& value) {
        for (int i = 0; i < SIZE; i++) {
            *(elements_[i]) = value;
        }
        return *this;
    }

    // Cast operators

    Vector2Int::operator Vector2() const {
        return Vector2((float)x, (float)y);
    }

    Vector2Int::operator Vector3() const {
        return Vector3((float)x, (float)y, 0);
    }

    Vector2Int::operator Vector4() const {
        return Vector4((float)x, (float)y, 0, 0);
    }

    Vector2Int::operator Vector3Int() const {
        return Vector3Int(x, y, 0);
    }

    Vector2Int::operator Vector4Int() const {
        return Vector4Int(x, y, 0, 0);
    }

    Vector2Int::operator string() const {
        std::stringstream ss("<");
        for (int i = 0; i < SIZE; i++) {
            ss << *(this->elements_[i]);
            if (i < SIZE - 1) ss << ", ";
        }
        ss << ">";
        return ss.str();
    }

    // Vector3Int ---------------------------------------------------------------

    // Constructors

    Vector3Int::Vector3Int() : Vector3Int(0) {};

    Vector3Int::Vector3Int(const int& value) : Vector3Int(value, value, value) {};

    Vector3Int::Vector3Int(const int& x, const int& y, const int& z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->elements_[0] = &(this->x);
        this->elements_[1] = &(this->y);
        this->elements_[2] = &(this->z);
    }

    // Static Functions

    float Vector3Int::angle(const Vector3Int& v0, const Vector3Int& v1) {
        return math::acos((float)dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
    }

    float Vector3Int::distance(const Vector3Int& v0, const Vector3Int& v1) {
        return magnitude(v0 - v1);
    }

    int Vector3Int::dot(const Vector3Int& v0, const Vector3Int& v1) {
        int t = 0;
        for (int i = 0; i < SIZE; i++) {
            t += (*(v0.elements_[i])) * (*(v1.elements_[i]));
        }
        return t;
    }

    Vector3Int Vector3Int::cross(const Vector3Int& v0, const Vector3Int& v1) {
        return Vector3Int(
            v0.y * v1.z - v0.z * v1.y,
            v0.z * v1.x - v0.x * v1.z,
            v0.x * v1.y - v0.y * v1.x
        );
    }

    float Vector3Int::magnitude(const Vector3Int& v) {
        return math::sqrt((float)dot(v, v));
    }

    // Member Functions

    float Vector3Int::angle(const Vector3Int& v) const {
        return angle(*this, v);
    }

    float Vector3Int::distance(const Vector3Int& v) const {
        return distance(*this, v);
    }

    int Vector3Int::dot(const Vector3Int& v) const {
        return dot(*this, v);
    }

    Vector3Int Vector3Int::cross(const Vector3Int& v) const {
        return cross(*this, v);
    }

    float Vector3Int::magnitude() const {
        return magnitude(*this);
    }

    // Accessor operators

    int& Vector3Int::operator[](const int& index) {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return *(elements_[index]);
    }

    const int& Vector3Int::operator[](const int& index) const {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return *(elements_[index]);
    }

    // Arithmatic operators

    Vector3Int Vector3Int::operator+(const Vector3Int& vec) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) + (*(vec.elements_[i]));
        }
        return v;
    }

    Vector3Int Vector3Int::operator+(const int& f) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) + f;
        }
        return v;
    }

    Vector3Int Vector3Int::operator-(const Vector3Int& vec) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) - (*(vec.elements_[i]));
        }
        return v;
    }

    Vector3Int Vector3Int::operator-(const int& f) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) - f;
        }
        return v;
    }

    Vector3Int Vector3Int::operator/(const Vector3Int& vec) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) / (*(vec.elements_[i]));
        }
        return v;
    }

    Vector3Int Vector3Int::operator/(const int& f) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) / f;
        }
        return v;
    }

    Vector3Int Vector3Int::operator*(const Vector3Int& vec) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) * (*(vec.elements_[i]));
        }
        return v;
    }

    Vector3Int Vector3Int::operator*(const int& f) const {
        Vector3Int v = Vector3Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) * f;
        }
        return v;
    }

    // Boolean operators

    bool Vector3Int::operator==(const Vector3Int& vec) const {
        bool e = true;
        for (int i = 0; i < SIZE; i++) {
            e &= ((*(this->elements_[i])) == (*(vec.elements_[i])));
        }
        return e;
    }

    bool Vector3Int::operator!=(const Vector3Int& vec) const {
        return !(*this == vec);
    }

    // Assignment operators

    Vector3Int& Vector3Int::operator=(const Vector3Int& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        return *this;
    }

    Vector3Int& Vector3Int::operator=(const int& value) {
        for (int i = 0; i < SIZE; i++) {
            *(elements_[i]) = value;
        }
        return *this;
    }

    // Cast operators

    Vector3Int::operator Vector2() const {
        return Vector2((float)x, (float)y);
    }

    Vector3Int::operator Vector3() const {
        return Vector3((float)x, (float)y, (float)z);
    }

    Vector3Int::operator Vector4() const {
        return Vector4((float)x, (float)y, (float)z, 0);
    }

    Vector3Int::operator Vector2Int() const {
        return Vector2Int(x, y);
    }

    Vector3Int::operator Vector4Int() const {
        return Vector4Int(x, y, z, 0);
    }

    Vector3Int::operator string() const {
        std::stringstream ss("<");
        for (int i = 0; i < SIZE; i++) {
            ss << *(this->elements_[i]);
            if (i < SIZE - 1) ss << ", ";
        }
        ss << ">";
        return ss.str();
    }

    // Vector4Int ---------------------------------------------------------------

    // Constructors

    Vector4Int::Vector4Int() : Vector4Int(0) {};

    Vector4Int::Vector4Int(const int& value) : Vector4Int(value, value, value, value) {};

    Vector4Int::Vector4Int(const int& x, const int& y, const int& z, const int& w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        this->elements_[0] = &(this->x);
        this->elements_[1] = &(this->y);
        this->elements_[2] = &(this->z);
        this->elements_[3] = &(this->w);
    }

    // Static Functions

    float Vector4Int::angle(const Vector4Int& v0, const Vector4Int& v1) {
        return math::acos((float)dot(v0, v1)) / (magnitude(v0) * magnitude(v1));
    }

    float Vector4Int::distance(const Vector4Int& v0, const Vector4Int& v1) {
        return magnitude(v0 - v1);
    }

    int Vector4Int::dot(const Vector4Int& v0, const Vector4Int& v1) {
        int t = 0;
        for (int i = 0; i < SIZE; i++) {
            t += (*(v0.elements_[i])) * (*(v1.elements_[i]));
        }
        return t;
    }

    float Vector4Int::magnitude(const Vector4Int& v) {
        return math::sqrt((float)dot(v, v));
    }

    // Member Functions

    float Vector4Int::angle(const Vector4Int& v) const {
        return angle(*this, v);
    }

    float Vector4Int::distance(const Vector4Int& v) const {
        return distance(*this, v);
    }

    int Vector4Int::dot(const Vector4Int& v) const {
        return dot(*this, v);
    }

    float Vector4Int::magnitude() const {
        return magnitude(*this);
    }

    // Accessor operators

    int& Vector4Int::operator[](const int& index) {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return *(elements_[index]);
    }

    const int& Vector4Int::operator[](const int& index) const {
        if (index < 0 || index >= SIZE) throw std::out_of_range("Attempting to access out of range element.");
        return *(elements_[index]);
    }

    // Arithmatic operators

    Vector4Int Vector4Int::operator+(const Vector4Int& vec) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) + (*(vec.elements_[i]));
        }
        return v;
    }

    Vector4Int Vector4Int::operator+(const int& f) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) + f;
        }
        return v;
    }

    Vector4Int Vector4Int::operator-(const Vector4Int& vec) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) - (*(vec.elements_[i]));
        }
        return v;
    }

    Vector4Int Vector4Int::operator-(const int& f) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) - f;
        }
        return v;
    }

    Vector4Int Vector4Int::operator/(const Vector4Int& vec) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) / (*(vec.elements_[i]));
        }
        return v;
    }

    Vector4Int Vector4Int::operator/(const int& f) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) / f;
        }
        return v;
    }

    Vector4Int Vector4Int::operator*(const Vector4Int& vec) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) * (*(vec.elements_[i]));
        }
        return v;
    }

    Vector4Int Vector4Int::operator*(const int& f) const {
        Vector4Int v = Vector4Int();
        for (int i = 0; i < SIZE; i++) {
            *(v.elements_[i]) = (*(this->elements_[i])) * f;
        }
        return v;
    }

    // Boolean operators

    bool Vector4Int::operator==(const Vector4Int& vec) const {
        bool e = true;
        for (int i = 0; i < SIZE; i++) {
            e &= ((*(this->elements_[i])) == (*(vec.elements_[i])));
        }
        return e;
    }

    bool Vector4Int::operator!=(const Vector4Int& vec) const {
        return !(*this == vec);
    }

    // Assignment operators

    Vector4Int& Vector4Int::operator=(const Vector4Int& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        this->w = vec.w;
        return *this;
    }

    Vector4Int& Vector4Int::operator=(const int& value) {
        for (int i = 0; i < SIZE; i++) {
            *(elements_[i]) = value;
        }
        return *this;
    }

    // Cast operators

    Vector4Int::operator Vector2() const {
        return Vector2((float)x, (float)y);
    }

    Vector4Int::operator Vector3() const {
        return Vector3((float)x, (float)y, (float)z);
    }

    Vector4Int::operator Vector4() const {
        return Vector4((float)x, (float)y, (float)z, (float)w);
    }

    Vector4Int::operator Vector2Int() const {
        return Vector2Int(x, y);
    }

    Vector4Int::operator Vector3Int() const {
        return Vector3Int(x, y, z);
    }

    Vector4Int::operator string() const {
        std::stringstream ss("<");
        for (int i = 0; i < SIZE; i++) {
            ss << *(this->elements_[i]);
            if (i < SIZE - 1) ss << ", ";
        }
        ss << ">";
        return ss.str();
    }

    // Arithmatic operators ----------------------------------------------------------

    Vector2 operator+(const float& f, const Vector2& vector) {
        return vector + f;
    }
    Vector2 operator-(const float& f, const Vector2& vector) {
        return Vector2(f - vector.x, f - vector.y);
    }
    Vector2 operator*(const float& f, const Vector2& vector) {
        return vector * f;
    }
    Vector2 operator/(const float& f, const Vector2& vector) {
        return Vector2(f / vector.x, f / vector.y);
    }

    Vector3 operator+(const float& f, const Vector3& vector) {
        return vector + f;
    }
    Vector3 operator-(const float& f, const Vector3& vector) {
        return Vector3(f - vector.x, f - vector.y, f - vector.z);
    }
    Vector3 operator*(const float& f, const Vector3& vector) {
        return vector * f;
    }
    Vector3 operator/(const float& f, const Vector3& vector) {
        return Vector3(f / vector.x, f / vector.y, f / vector.z);
    }

    Vector4 operator+(const float& f, const Vector4& vector) {
        return vector + f;
    }
    Vector4 operator-(const float& f, const Vector4& vector) {
        return Vector4(f - vector.x, f - vector.y, f - vector.z, f - vector.w);
    }
    Vector4 operator*(const float& f, const Vector4& vector) {
        return vector * f;
    }
    Vector4 operator/(const float& f, const Vector4& vector) {
        return Vector4(f / vector.x, f / vector.y, f / vector.z, f / vector.w);
    }

    Vector2Int operator+(const int& f, const Vector2Int& vector) {
        return vector + f;
    }
    Vector2Int operator-(const int& f, const Vector2Int& vector) {
        return Vector2Int(f - vector.x, f - vector.y);
    }
    Vector2Int operator*(const int& f, const Vector2Int& vector) {
        return vector * f;
    }
    Vector2Int operator/(const int& f, const Vector2Int& vector) {
        return Vector2Int(f / vector.x, f / vector.y);
    }

    Vector3Int operator+(const int& f, const Vector3Int& vector) {
        return vector + f;
    }
    Vector3Int operator-(const int& f, const Vector3Int& vector) {
        return Vector3Int(f - vector.x, f - vector.y, f - vector.z);
    }
    Vector3Int operator*(const int& f, const Vector3Int& vector) {
        return vector * f;
    }
    Vector3Int operator/(const int& f, const Vector3Int& vector) {
        return Vector3Int(f / vector.x, f / vector.y, f / vector.z);
    }

    Vector4Int operator+(const int& f, const Vector4Int& vector) {
        return vector + f;
    }
    Vector4Int operator-(const int& f, const Vector4Int& vector) {
        return Vector4Int(f - vector.x, f - vector.y, f - vector.z, f - vector.w);
    }
    Vector4Int operator*(const int& f, const Vector4Int& vector) {
        return vector * f;
    }
    Vector4Int operator/(const int& f, const Vector4Int& vector) {
        return Vector4Int(f / vector.x, f / vector.y, f / vector.z, f / vector.w);
    }

    // IO operators ----------------------------------------------------------

    std::ostream& operator<< (std::ostream& os, const Vector2& c) {
        os << (string)c;
        return os;
    }

    std::ostream& operator<< (std::ostream& os, const Vector3& c) {
        os << (string)c;
        return os;
    }

    std::ostream& operator<< (std::ostream& os, const Vector4& c) {
        os << (string)c;
        return os;
    }

    std::ostream& operator<< (std::ostream& os, const Vector2Int& c) {
        os << (string)c;
        return os;
    }

    std::ostream& operator<< (std::ostream& os, const Vector3Int& c) {
        os << (string)c;
        return os;
    }

    std::ostream& operator<< (std::ostream& os, const Vector4Int& c) {
        os << (string)c;
        return os;
    }
}