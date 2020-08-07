/**
 * Matrix.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Matrix.hpp"

namespace seedengine {

    // Explicit template instantiation

    template class ENGINE_API Matrix<float, 1, 1>;
    template class ENGINE_API Matrix<float, 1, 2>;
    template class ENGINE_API Matrix<float, 1, 3>;
    template class ENGINE_API Matrix<float, 1, 4>;

    template class ENGINE_API Matrix<float, 2, 1>;
    template class ENGINE_API Matrix<float, 2, 2>;
    template class ENGINE_API Matrix<float, 2, 3>;
    template class ENGINE_API Matrix<float, 2, 4>;

    template class ENGINE_API Matrix<float, 3, 1>;
    template class ENGINE_API Matrix<float, 3, 2>;
    template class ENGINE_API Matrix<float, 3, 3>;
    template class ENGINE_API Matrix<float, 3, 4>;

    template class ENGINE_API Matrix<float, 4, 1>;
    template class ENGINE_API Matrix<float, 4, 2>;
    template class ENGINE_API Matrix<float, 4, 3>;
    template class ENGINE_API Matrix<float, 4, 4>;


    template class ENGINE_API Matrix<int, 1, 1>;
    template class ENGINE_API Matrix<int, 1, 2>;
    template class ENGINE_API Matrix<int, 1, 3>;
    template class ENGINE_API Matrix<int, 1, 4>;

    template class ENGINE_API Matrix<int, 2, 1>;
    template class ENGINE_API Matrix<int, 2, 2>;
    template class ENGINE_API Matrix<int, 2, 3>;
    template class ENGINE_API Matrix<int, 2, 4>;

    template class ENGINE_API Matrix<int, 3, 1>;
    template class ENGINE_API Matrix<int, 3, 2>;
    template class ENGINE_API Matrix<int, 3, 3>;
    template class ENGINE_API Matrix<int, 3, 4>;

    template class ENGINE_API Matrix<int, 4, 1>;
    template class ENGINE_API Matrix<int, 4, 2>;
    template class ENGINE_API Matrix<int, 4, 3>;
    template class ENGINE_API Matrix<int, 4, 4>;

}