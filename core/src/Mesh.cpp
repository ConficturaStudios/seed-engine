#include "Mesh.hpp"

namespace seedengine {

    Mesh::Mesh(const std::string& path) : Asset<float>(path) {
        
    }

    void Mesh::load() {
    }

    void Mesh::unload() {
        data_ = nullptr;
    }

}