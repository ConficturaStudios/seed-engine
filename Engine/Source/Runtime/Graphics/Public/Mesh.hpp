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

    struct Vertex {
        Vector3 position;
        Vector3 normal;
        Vector2* uvs;
        LinearColor* colors;
        //float* bone_weights; // ?
        //Vector3 morphs; // ?
    };

    struct MeshFileData {

            // Internal types

            struct FileHeader {
                uint32_t position_count;
                uint32_t normal_count;
                uint32_t uv_count;
                uint32_t color_count;

                uint32_t bone_count;
                uint32_t bone_weight_count;
                uint32_t morph_count;

                union {
                    uint32_t uvc_raw;
                    struct {
                        uint8_t  uv_channel_count : 3;
                        uint8_t  color_channel_count : 3;
                        uint8_t  UNUSED_0x03000000 : 2;
                        uint8_t  UNUSED_0x00FF0000;
                        uint16_t UNUSED_0x0000FFFF;
                    };
                };

                uint32_t vertex_count;
                uint32_t smoothing_group_count;

                // Note: ensure Big Endian during IO operations
                friend std::ostream& operator<<(std::ostream& lhs, const MeshFileData::FileHeader& rhs);
                friend std::istream& operator>>(std::istream& lhs,       MeshFileData::FileHeader& rhs);
            };

            struct SmoothingGroup {
                uint32_t* faces;
            };

            // Data members

            MeshFileData::FileHeader header_data;

            //TODO: Decide between heap (*) and stack ([]) allocated storage for variable sized data

            float* positions;
            float* normals;
            float* uvs;
            float* colors;

            //float* ? bones;
            float* bone_weights;
            float* morphs;

            uint32_t* vertices;
            MeshFileData::SmoothingGroup* smoothing_group;

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

        private:

    };

}

#endif