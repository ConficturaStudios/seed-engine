#ifndef SEEDENGINE_INCLUDE_NULLABLE_H_
#define SEEDENGINE_INCLUDE_NULLABLE_H_

#include <string>
#include <iostream>
#include <typeinfo>

namespace seedengine {

    struct nullable_t;

    struct null_t final {

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

        null_t() = default;

    };

    #define nullobj null_t::null_object


    struct nullable_t {

        friend struct null_t;

    public:

        bool isNull() const { return is_null_; }

        template <
            class N,
            typename = typename std::enable_if<std::is_base_of<nullable_t, N>::value>::type
        >
        N& operator=(const null_t& null) {
            this->is_null_ = true;
        }

        template <class N, typename = typename std::enable_if<std::is_base_of<nullable_t, N>::value>::type>
        friend bool operator==(const N& obj, const null_t& null) {
            return obj.is_null_;
        }

        template <class N, typename = typename std::enable_if<std::is_base_of<nullable_t, N>::value>::type>
        friend bool operator!=(const N& obj, const null_t& null) {
            return !obj.is_null_;
        }

        virtual operator std::string() const { return "nullable_t"; }

        operator bool() const { return is_null_; }

        friend std::ostream& operator<<(std::ostream& os, const nullable_t& obj) {
            if (obj.is_null_) os << "null";
            else os << (std::string)(obj);
            return os;
        }

    protected:

        nullable_t() : is_null_(false) {}
        nullable_t(const bool& null) : is_null_(null) {}


    private:

        bool is_null_;

    };

}

#endif