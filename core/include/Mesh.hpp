#ifndef SEEDENGINE_INCLUDE_MESH_H_
#define SEEDENGINE_INCLUDE_MESH_H_

#include "Core.hpp"
#include "Parser.hpp"
#include "Asset.hpp"

namespace seedengine {

    /** The draw type of a mesh. */
    enum class MeshDrawType {
        STATIC,
        DYNAMIC
    };

    // Struct for binary mesh data

    /**
     * @brief The raw data of a mesh loaded from a file.
     * @details
     */
    struct mesh_data {

        std::vector<float> positions;
        std::vector<float> normals;
        std::vector<float> uvs;
        std::vector<float> colors;
        std::vector<float> bone_weights;
        std::vector<float> morphs;
        std::vector<uint32_t> indices;

        uint8_t uvs_per_vertex;
        uint8_t colors_per_vertex;

        uint32_t vertex_size;

    };

    /**
     * @brief The raw data of a mesh loaded from a file.
     * @details
     */
    struct meshdata {
        /** The properties of the mesh. */
        std::map<string, string> properties = std::map<string, string>();
        /** The vertex positions of the mesh. */
        std::vector<float> positions = std::vector<float>();
        /** The vertex normals of the mesh. */
        std::vector<float> normals = std::vector<float>();
        /** The primary vertex colors of the mesh. */
        std::vector<float> p_colors = std::vector<float>();
        /** The secondary vertex colors of the mesh. */
        std::vector<float> s_colors = std::vector<float>();
        /** The uv channel 0 of the mesh. */
        std::vector<float> uv_0 = std::vector<float>();
        /** The uv channel 1 of the mesh. */
        std::vector<float> uv_1 = std::vector<float>();
        /** The uv channel 2 of the mesh. */
        std::vector<float> uv_2 = std::vector<float>();
        /** The uv channel 3 of the mesh. */
        std::vector<float> uv_3 = std::vector<float>();
        /** The uv channel 4 of the mesh. */
        std::vector<float> uv_4 = std::vector<float>();
        /** The uv channel 5 of the mesh. */
        std::vector<float> uv_5 = std::vector<float>();
        /** The uv channel 6 of the mesh. */
        std::vector<float> uv_6 = std::vector<float>();
        /** The uv channel 7 of the mesh. */
        std::vector<float> uv_7 = std::vector<float>();
        /** The faces of the mesh. */
        std::vector<int>   faces = std::vector<int>();
        /** The total vertex attribute count. */
        unsigned int vertex_attrib_count = 0;

    };

    /**
     * @brief A mesh asset.
     * @details
     */
    class Mesh : public Asset<mesh_data> {

        ENGINE_ASSET_BODY()

        friend class Renderer;

    public:

    protected:

        /**
         * @brief Constructs a new mesh from data in a file.
         * 
         * @param path The path to the mesh to be loaded.
         */
        Mesh(const string& path);

        /** Loads this mesh into memory. */
        void load();
        /** Unloads this mesh from memory. */
        void unload();

        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
        
            /** The vertex array object (VAO) of this mesh. */
            GLuint vao_ = 0;
            /** All vertex buffer objects (VBOs) of this mesh. */
            std::vector<GLuint> vertex_buffers_ = std::vector<GLuint>();
            /** The indices buffer of this mesh. */
            GLuint indices_buffer_ = 0;

            /**
             * @brief Creates a new VBO using the passed data.
             * 
             * @param location The location in the buffer to bind to.
             * @param size The size of the data elements.
             * @param data The data to bind.
             */
            void opglCreateVertexBuffer(uint32_t location, uint32_t size, std::vector<float> data) {
                GLuint buffer;
                glGenBuffers(1, &buffer);
                glBindBuffer(GL_ARRAY_BUFFER, buffer);
                glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
                vertex_buffers_.push_back(buffer);
                glVertexAttribPointer(
                    location,
                    size,
                    GL_FLOAT,
                    GL_FALSE,
                    0,
                    0
                );
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                //TODO: Add option for gl dynamic draw in procedural mesh class.
            }

            /**
             * @brief Creates a new Indices VBO using the passed data.
             * 
             * @param data The data to bind.
             */
            void opglCreateIndicesBuffer(std::vector<uint32_t> data) {
                glGenBuffers(1, &indices_buffer_);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer_);
                glBufferData(
                    GL_ELEMENT_ARRAY_BUFFER,
                    data.size() * sizeof(uint32_t),
                    &data[0],
                    GL_STATIC_DRAW
                );
            }

        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN

        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX

        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL

        #endif

    private:

        /**
         * @brief Loads the *.mesh file into data.
         * 
         * @param path The path to the mesh to be loaded.
         * @param out The data stored within the passed file.
         * @return true If the mesh data was able to be extracted.
         * @return false If the mesh data was not able to be extracted.
         */
        static bool extractMesh(const string& path, meshdata& out);

        /**
         * @brief Loads the *mesh file into data
         *
         * @param path The path to the mesh to be loaded.
         * @param out The data stored within the passed file.
         * @return true If the mesh data was able to be extracted.
         * @return false If the mesh data was not able to be extracted.
         */
        static bool parse(const string& path, mesh_data* out);

    };

}

#endif