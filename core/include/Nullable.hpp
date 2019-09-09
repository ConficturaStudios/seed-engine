#ifndef SEEDENGINE_INCLUDE_NULLABLE_H_
#define SEEDENGINE_INCLUDE_NULLABLE_H_

#include <string>
#include <iostream>
#include <typeinfo>

namespace seedengine {

    struct nullable_t;

    //TODO: Modify or remove null object implementation

    /** The type of a null object. */
    struct null_t final {

        /** The null object singleton. */
        static null_t null_object;

        friend bool operator==(const null_t& n0, const null_t& n1);

        friend std::ostream& operator<<(std::ostream& os, const null_t& null) {
            os << "null";
            return os;
        }

        template <
            class N,
            typename = typename std::enable_if<std::is_base_of<nullable_t, N>::value>::type
        >
        operator N() const {
            N n = N();
            n.is_null_ = true;
            return n;
        }

        operator bool() const {
            return false;
        }

    private:
        /** Constructs a new null object. */
        null_t() = default;

    };

    /** The null object. */
    #define nullobj null_t::null_object

    /**
     * @brief The base class for nullable objects.
     * @details
     */
    struct nullable_t {

        friend struct null_t;

    public:

        /**
         * @brief Returns true if this object is null.
         * 
         * @return true If this object is null.
         * @return false If this object is not null.
         */
        bool isNull() const { return is_null_; }
        
        nullable_t& operator=(const null_t& null) {
            this->is_null_ = true;
            return *this;
        }

        bool operator==(const null_t& null) {
            return is_null_;
        }

        bool operator!=(const null_t& null) {
            return !is_null_;
        }

        virtual operator std::string() const { return "nullable_t"; }

        operator bool() const { return is_null_; }

        friend std::ostream& operator<<(std::ostream& os, const nullable_t& obj) {
            if (obj.is_null_) os << "null";
            else os << (std::string)(obj);
            return os;
        }

    protected:
        /** Constructs a new nullable object. */
        nullable_t() : is_null_(false) {}
        /**
         * @brief Constructs a new nullable object.
         * 
         * @param null True if the object is initialized as null.
         */
        nullable_t(const bool& null) : is_null_(null) {}
        /**
         * @brief Constructs a new nullable object.
         * 
         * @param null The null object to initialize this object as null.
         */
        nullable_t(const null_t& null) : is_null_(true) {}


    private:

        /** Is this object null? */
        bool is_null_;

    };

}

#endif