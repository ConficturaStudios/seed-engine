#ifndef SEEDENGINE_INCLUDE_OBJECT_H_
#define SEEDENGINE_INCLUDE_OBJECT_H_

#include "Core.hpp"

namespace seedengine {

    class Object {

    public:

        /** Constructs a new Object. */
        Object();

        /**
         * @brief Constructs a new Object.
         * 
         * @param name The name of this Object.
         */
        Object(string name);

        /**
         * @brief Constructs a new Object.
         * 
         * @param obj The Object to copy when constructing this Object.
         */
        Object(const Object& obj);

        /** Destroys this Object. */
        virtual ~Object();

        /**
         * @brief Returns the ID of this Object.
         * 
         * @return const unsigned int The ID of this Object.
         */
        inline const unsigned int getID() const { return id_; }

        /**
         * @brief Converts this Object into a string.
         * 
         * @return string The string form of this Object.
         */
        virtual string toString() const;

        // Cast operators

        explicit operator unsigned int() const;

        operator string() const;

        // Operator overloads

        friend std::ostream& operator<<(std::ostream& os, const Object& obj);

        virtual bool operator==(const Object& obj) const;

        virtual bool operator!=(const Object& obj) const;

        virtual bool operator<(const Object& obj) const;

        virtual bool operator>(const Object& obj) const;

        virtual bool operator<=(const Object& obj) const;

        virtual bool operator>=(const Object& obj) const;

        // Static Functions

        /**
         * @brief Calls the destructor on the passed Object.
         * 
         * @param obj The Object to destroy.
         * @param delay The delay before destroying the Object. Defaults to 0.
         */
        static void Destroy(Object* obj, float delay = 0.0f) {
            delete obj;
        }

    protected:

        /** The name of this Object. */
        string name_;

    private:

        /** A mutex to lock functions for thread safety. */
        static std::mutex s_mu;

        /** The id of this Object. */
        const unsigned int id_;

        /** The latest id generated. */
        static unsigned int latest_id_;

        /**
         * @brief Generates a unique new Object ID.
         * 
         * @return unsigned int A new Object ID.
         */
        static unsigned int generateID() {
            std::lock_guard<std::mutex> gaurd(s_mu);
            latest_id_++;
            return latest_id_;
        }

    };

    std::ostream& operator<<(std::ostream& os, const Object& obj);

}

namespace std {

    /** Object hashing function. */
    template <> struct hash<seedengine::Object> {
        /**
         * @brief Object hashing function.
         * 
         * @param obj The Object to hash.
         * @return size_t The resulting hash value.
         */
        size_t operator()(const seedengine::Object& obj) const {
            return (hash<unsigned int>()(obj.getID())
                    ^ (hash<string>()(obj.toString()) << 1) >> 1);
        }
    };

}

#endif