#include "Object.hpp"

namespace seedengine {

    Object::Object() : Object("Object") {

    }

    Object::Object(string name) : id_(generateID()), name_(name) {

    }

    Object::~Object() {

    }

    string Object::toString() const {
        return name_;
    }


    Object::operator unsigned int() const {
        return this->getID();
    }

    Object::operator string() const {
        return this->toString();
    }


    std::ostream& operator<<(std::ostream& os, const Object& obj) {
        os << (string)obj;
        return os;
    }

    bool Object::operator==(const Object& obj) const {
        return this->getID() == obj.getID() && this->toString().compare(obj.toString()) == 0;
    }

    bool Object::operator!=(const Object& obj) const {
        return this->getID() != obj.getID() || this->toString().compare(obj.toString()) != 0;
    }

    bool Object::operator<(const Object& obj) const {
        int c = this->toString().compare(obj.toString());
        return (c == 0) ? this->getID() < obj.getID() : c < 0;
    }

    bool Object::operator>(const Object & obj) const {
        int c = this->toString().compare(obj.toString());
        return (c == 0) ? this->getID() > obj.getID() : c > 0;
    }

    bool Object::operator<=(const Object & obj) const {
        return *this < obj || *this == obj;
    }

    bool Object::operator>=(const Object & obj) const {
        return *this > obj || *this == obj;
    }

}