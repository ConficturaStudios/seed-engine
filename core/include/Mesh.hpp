#ifndef SEEDENGINE_INCLUDE_MESH_H_
#define SEEDENGINE_INCLUDE_MESH_H_

#include "Core.hpp"
#include "Asset.hpp"

namespace seedengine {

    // The draw type of a mesh.
    enum class MeshDrawType {
        STATIC,
        DYNAMIC
    };

    // The raw data of a mesh loaded from a file.
    struct meshdata {
        // The properties of the mesh.
        std::map<std::string, const std::string> properties;
        // The vertex positions of the mesh.
        std::vector<float> positions;
        // The vertex normals of the mesh.
        std::vector<float> normals;
        // The primary vertex colors of the mesh.
        std::vector<float> p_colors;
        // The secondary vertex colors of the mesh.
        std::vector<float> s_colors;
        // The uv channel 0 of the mesh.
        std::vector<float> uv_0;
        // The uv channel 1 of the mesh.
        std::vector<float> uv_1;
        // The uv channel 2 of the mesh.
        std::vector<float> uv_2;
        // The uv channel 3 of the mesh.
        std::vector<float> uv_3;
        // The uv channel 4 of the mesh.
        std::vector<float> uv_4;
        // The uv channel 5 of the mesh.
        std::vector<float> uv_5;
        // The uv channel 6 of the mesh.
        std::vector<float> uv_6;
        // The uv channel 7 of the mesh.
        std::vector<float> uv_7;
        // The faces of the mesh.
        std::vector<int>   faces;
        // The total vertex attribute count.
        unsigned int vertex_attrib_count;

    };

    // A mesh asset.
    class Mesh : public Asset<meshdata> {

        ENGINE_ASSET_BODY()

        friend class Renderer;

    public:

    protected:

        // Constructs a new mesh from data in a file.
        // @param(const std::string&) path: The path to the mesh to be loaded.
        Mesh(const std::string&);

        // Loads this mesh into memory.
        void load();
        // Unloads this mesh from memory.
        void unload();

        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
        
            // The vertex array object (VAO) of this mesh.
            GLuint vao_;
            // All vertex buffer objects (VBOs) of this mesh.
            std::vector<GLuint> vertex_buffers_;

            // Creates a new VBO using the passed data.
            // @param(unsigned int) size: The size of the data elements.
            // @param(std::vector<float>) data: The data to bind.
            void opglCreateVertexBuffer(unsigned int size, std::vector<float> data) {
                GLuint buffer;
                glGenBuffers(1, &buffer);
                glBindBuffer(GL_ARRAY_BUFFER, buffer);
                glBufferData(GL_ARRAY_BUFFER, sizeof( data.data() ), data.data(), GL_STATIC_DRAW);
                vertex_buffers_.push_back(buffer);
                glVertexAttribPointer(
                    vertex_buffers_.size() - 1,
                    size,
                    GL_FLOAT,
                    GL_FALSE,
                    0,
                    0
                );
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                //TODO: Add option for gl dynamic draw.
            }

            // Creates a new Indices VBO using the passed data.
            // @param(std::vector<int>) data: The data to bind.
            void opglCreateIndicesBuffer(std::vector<int> data) {
                GLuint buffer;
                glGenBuffers(1, &buffer);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
                glBufferData(
                    GL_ELEMENT_ARRAY_BUFFER,
                    data.size() * sizeof(unsigned int),
                    &data[0],
                    GL_STATIC_DRAW
                );
                vertex_buffers_.push_back(buffer);
            }

        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN

        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX

        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL

        #endif

    private:

        // Loads the *.mesh file into data.
        // @param(const std::string&) path: The path to the mesh to be loaded.
        // @param(std::shared_ptr<meshdata>) data: A pointer to the location to store the parsed data.
        static meshdata* extractMesh(const std::string&);

    };

    // A library of mesh assets.
    class MeshLibrary : public AssetLibrary<meshdata, Mesh> {

    public:

        // Constructs a new mesh library.
        MeshLibrary() : AssetLibrary<meshdata, Mesh>() {}

    };

}

#endif