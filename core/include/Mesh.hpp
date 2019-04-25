#ifndef SEEDENGINE_INCLUDE_MESH_H_
#define SEEDENGINE_INCLUDE_MESH_H_

#include "Core.hpp"
#include "Asset.hpp"

namespace seedengine {

    // A mesh asset.
    class Mesh : public Asset<float> {

        ENGINE_ASSET_BODY()

    public:

    protected:

        // Constructs a new mesh from data in a file.
        // @param(const std::string&) path: The path to the mesh to be loaded.
        Mesh(const std::string&);

        // Loads this mesh into memory.
        void load();
        // Unloads this mesh from memory.
        void unload();

    private:

    };

    // A library of mesh assets.
    class MeshLibrary : public AssetLibrary<float, Mesh> {

    public:

        MeshLibrary() : AssetLibrary<float, Mesh>() {}

    };

}

#endif