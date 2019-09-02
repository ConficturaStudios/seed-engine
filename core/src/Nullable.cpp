#include "Nullable.hpp"

namespace seedengine {

    null_t null_t::null_object = null_t();

    bool operator==(const null_t& n0, const null_t& n1) {
        return true;
    }

}