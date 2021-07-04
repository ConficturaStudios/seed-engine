/**
 * Mesh.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_MESH_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_MESH_H_

#include "GraphicsAPI.hpp"
#include "Color.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

namespace seedengine {

    struct MeshData {

        // Internal types

        struct FileHeader {
            // TODO: Add version identifier support to allow changes to format without breaking old files
            uint32_t positionCount;
            uint32_t normalCount;
            uint32_t uvCount;
            uint32_t colorCount;

            uint32_t boneCount;
            uint32_t boneWeightCount;
            uint32_t morphCount;

            union {
                uint32 rawUvAndColorData;
                struct {
                    uint32 uvsPerVertex : 3;
                    uint32 colorsPerVertex : 3;
                    uint32 _padding_0 : 26;
                };
            };

            uint32_t vertexCount;
            uint32_t smoothingGroupCount;
        };

        /*struct Vertex {
            uint32 position;
            uint32 normal;
            uint32* uvs;
            uint32* colors;
            uint32* weights; // TODO: Store weights in key value pairs (bone id, weight index) to 0 default unused bones
        };*/

        struct Face {
            uint32 indices[3];
        };

        struct Morph {
            uint32 originalVertex;
            uint32 targetVertex;
        };

        struct SmoothingGroup {
            uint32 faceCount;
            MeshData::Face* faces;
        };

        // Data members

        MeshData::FileHeader header;

        Vector3* positions;
        Vector3* normals;
        Vector2* uvs;
        LinearColor* colors;

        // bones?
        float* boneWeights;
        // Morphs

        //MeshData::Vertex* vertices;
        MeshData::SmoothingGroup* smoothingGroups;

    };

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Mesh {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Mesh objects.
             * @details Constructs a new Mesh with default initialization for all members.
             */
            Mesh();

            /**
             * @brief The copy constructor for Mesh objects.
             * @details Constructs a new Mesh by copying an existing Mesh.
             */
            Mesh(const Mesh& ref) = default;
            
            /**
             * @brief The move constructor for Mesh objects.
             * @details Constructs a new Mesh by moving the data of a Mesh into this object.
             */
            Mesh(Mesh&& ref) = default;

            /**
             * @brief The destructor for Mesh objects.
             * @details Called when an instance of Mesh is deleted.
             */
            virtual ~Mesh();

        // Functions

            [[nodiscard]] static UniquePtr<Mesh> load(const char* path);

        // Operators

            /**
             * @brief The copy assignment operator for Mesh objects.
             * @details Reassigns the value of this object by copying the data of a Mesh into this object.
             */
            Mesh& operator=(const Mesh& ref) = default;

            /**
             * @brief The move assignment operator for Mesh objects.
             * @details Reassigns the value of this object by moving the data of a Mesh into this object.
             */
            Mesh& operator=(Mesh&& ref) = default;

        protected:

            MeshData m_data{};

        private:

    };

}

#endif