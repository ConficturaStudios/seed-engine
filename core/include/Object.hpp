#ifndef SEEDENGINE_INCLUDE_OBJECT_H_
#define SEEDENGINE_INCLUDE_OBJECT_H_

#include "Core.hpp"

namespace seedengine {

    class Object {

    public:

        // Constructs a new Object.
        Object() : Object("object") {
            
        }

        // Constructs a new Object with a custom name.
        Object(string name) : id_(generateID()), name_(name) {

        }

        // Destroys this Object.
        virtual ~Object() {

        }

        // Returns the ID of this Object.
        // @returns: The ID of this Object.
        inline const unsigned int getID() const { return id_; }

        // Converts this Object into a string.
        // @returns: The string form of this Object.
        virtual string toString() const { return name_; }

        /// Cast operators

        operator unsigned int() const {
            return this->getID();
        }

        operator string() const {
            return this->toString();
        }

        /// Operator overloads

        friend std::ostream& operator<<(std::ostream& os, const Object& obj) {
            os << obj.toString();
            return os;
        }

        virtual bool operator==(const Object& obj) const {
            return this->getID() == obj.getID() && this->toString().compare(obj.toString()) == 0;
        }

        virtual bool operator!=(const Object& obj) const {
            return this->getID() != obj.getID() || this->toString().compare(obj.toString()) != 0;
        }

        virtual bool operator<(const Object& obj) const {
            int c = this->toString().compare(obj.toString());
            return (c == 0) ? this->getID() < obj.getID() : c < 0;
        }

        virtual bool operator>(const Object& obj) const {
            int c = this->toString().compare(obj.toString());
            return (c == 0) ? this->getID() > obj.getID() : c > 0;
        }

        virtual bool operator<=(const Object& obj) const {
            return *this < obj || *this == obj;
        }

        virtual bool operator>=(const Object& obj) const {
            return *this > obj || *this == obj;
        }

        /// Static Functions

        // Calls the destructor on the passed Object.
        // @param(Object&) obj: The Object to destroy.
        // @param(float) delay: The delay before destroying the Object. Defaults to 0.
        static void Destroy(Object* obj, float delay = 0.0f) {
            delete obj;
        }

    protected:

        // The name of this Object.
        string name_;

    private:

        // A mutex to lock functions for thread safety.
        static std::mutex s_mu;

        // The id of this Object.
        const unsigned int id_;

        // The latest id generated.
        static unsigned int latest_id_;

        // Generates a unique new Object ID.
        // @returns: A new Object ID.
        static unsigned int generateID() {
            std::lock_guard<std::mutex> gaurd(s_mu);
            latest_id_++;
            return latest_id_;
        }

    };

}

namespace std {

    // Object hashing function.
    template <> struct hash<seedengine::Object> {
        // Object hashing function.
        size_t operator()(const seedengine::Object& obj) const {
            return (hash<unsigned int>()(obj.getID())
                    ^ (hash<string>()(obj.toString()) << 1) >> 1);
        }
    };

}

#endif