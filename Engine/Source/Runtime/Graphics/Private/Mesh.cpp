/**
 * Mesh.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Mesh.hpp"

namespace seedengine {

    Mesh::Mesh() = default;

    Mesh::~Mesh() {
        
        // Clear/unload mesh data
        if (m_data.positions) {
            for (uint32 i = 0; i < m_data.header.positionCount; i++) {
                m_data.positions[i].~Vector3();
            }
            free(m_data.positions);
        }
        if (m_data.normals) {
            for (uint32 i = 0; i < m_data.header.normalCount; i++) {
                m_data.normals[i].~Vector3();
            }
            free(m_data.normals);
        }
        if (m_data.uvs) {
            for (uint32 i = 0; i < m_data.header.uvCount; i++) {
                m_data.uvs[i].~Vector2();
            }
            free(m_data.uvs);
        }
        if (m_data.colors) {
            for (uint32 i = 0; i < m_data.header.colorCount; i++) {
                m_data.colors[i].~LinearColor();
            }
            free(m_data.colors);
        }
        if (m_data.boneWeights) free(m_data.boneWeights);
        /*if (m_data.vertices) {
            for (uint32 i = 0; i < m_data.header.vertexCount; i++) {
                free(m_data.vertices[i].uvs);
                free(m_data.vertices[i].colors);
                free(m_data.vertices[i].weights);
            }
            free(m_data.vertices);
        }*/
        if (m_data.smoothingGroups) {
            for (uint32 i = 0; i < m_data.header.smoothingGroupCount; i++) {
                free(m_data.smoothingGroups[i].faces);
            }
            free(m_data.smoothingGroups);
        }
    }

    UniquePtr<Mesh> Mesh::load(const char* path) {
        FILE* source = fopen(path, "rb");
        // Open file
        if (!source) {
            ENGINE_DEBUG_ERROR("Failed to open mesh file '{0}'", path);
            return nullptr;
        }
        // Allocate mesh
        UniquePtr<Mesh> instance = CreateUniquePtr<Mesh>();
        MeshData* data = &instance->m_data;
        
        // Read header
        uint32 header[10];
        // TODO: Check read bytes count for error checking
        if (fread(header, sizeof(uint32), 10, source) != 10) {
            ENGINE_DEBUG_ERROR("Failed to read header data from file '{0}'", path);
            fclose(source);
            return nullptr;
        }
        data->header.positionCount = Memory::ntoh(header[0]);
        data->header.normalCount = Memory::ntoh(header[1]);
        data->header.uvCount = Memory::ntoh(header[2]);
        data->header.colorCount = Memory::ntoh(header[3]);
        data->header.boneCount = Memory::ntoh(header[4]);
        data->header.boneWeightCount = Memory::ntoh(header[5]);
        data->header.morphCount = Memory::ntoh(header[6]);
        data->header.rawUvAndColorData = Memory::ntoh(header[7]);
        data->header.vertexCount = Memory::ntoh(header[8]);
        data->header.smoothingGroupCount = Memory::ntoh(header[9]);

        // Allocate buffers
        auto* positions = (float*)malloc(sizeof(float) * 3 * data->header.positionCount);
        auto* normals = (float*)malloc(sizeof(float) * 3 * data->header.normalCount);
        auto* uvs = (float*)malloc(sizeof(float) * 2 * data->header.uvCount);
        auto* colors = (float*)malloc(sizeof(float) * 4 * data->header.colorCount);

        auto* boneWeights = (float*)malloc(sizeof(float) * data->header.boneWeightCount);

        // Store the number of expected elements for error checking
        size_t expectedCount;

        // Read positions
        expectedCount = 3 * data->header.positionCount;
        if (fread(positions, sizeof(float), expectedCount, source) != expectedCount) {
            ENGINE_DEBUG_ERROR("Failed to read position data from file '{0}'", path);
            fclose(source);
            return nullptr;
        }
        // Read normals
        expectedCount = 3 * data->header.normalCount;
        if (fread(normals, sizeof(float), expectedCount, source) != expectedCount) {
            ENGINE_DEBUG_ERROR("Failed to read normal data from file '{0}'", path);
            fclose(source);
            return nullptr;
        }
        // Read uvs
        expectedCount = 2 * data->header.uvCount;
        if (fread(uvs, sizeof(float), expectedCount, source) != expectedCount) {
            ENGINE_DEBUG_ERROR("Failed to read uv data from file '{0}'", path);
            fclose(source);
            return nullptr;
        }
        // Read colors
        expectedCount = 4 * data->header.colorCount;
        if (fread(colors, sizeof(float), expectedCount, source) != expectedCount) {
            ENGINE_DEBUG_ERROR("Failed to read color data from file '{0}'", path);
            fclose(source);
            return nullptr;
        }
        // Read weights
        expectedCount = data->header.boneWeightCount;
        if (fread(boneWeights, sizeof(float), expectedCount, source) != expectedCount) {
            ENGINE_DEBUG_ERROR("Failed to read bone weight data from file '{0}'", path);
            fclose(source);
            return nullptr;
        }

        // TODO: Apply ntoh to buffer data

        // Allocate vertex buffers
        data->positions = (Vector3*)malloc(sizeof(Vector3) * data->header.vertexCount);
        data->normals = (Vector3*)malloc(sizeof(Vector3) * data->header.vertexCount);

        // TODO: Handle multiple UV and color channels, convert to 2d array
        data->uvs = (Vector2*)malloc(sizeof(Vector2) * data->header.vertexCount);

        data->colors = (LinearColor*)malloc(sizeof(LinearColor) * data->header.vertexCount);

        data->boneWeights = (float*)malloc(sizeof(float) * data->header.vertexCount);

        // Read vertices
        uint32 perVertexSize = 2U + data->header.uvsPerVertex + data->header.colorsPerVertex + data->header.boneCount;
        uint32 vertexDataSize = data->header.vertexCount * perVertexSize;
        auto* vertexData = (uint32*)malloc(sizeof(uint32) * vertexDataSize);

        // TODO: Check read bytes count for error checking
        // TODO: Apply ntoh to vertex data
        if (fread(vertexData, sizeof(uint32), vertexDataSize, source) != vertexDataSize) {
            ENGINE_DEBUG_ERROR("Failed to read vertex data from file '{0}'", path);
            fclose(source);
            return nullptr;
        }

        // Copy each vertex from the buffer
        for (uint32 i = 0; i < data->header.vertexCount; i++) {
//            data->vertices[i] = MeshData::Vertex();
//            data->vertices[i].uvs = (uint32*)malloc(sizeof(uint32) * data->header.uvsPerVertex);
//            data->vertices[i].colors = (uint32*)malloc(sizeof(uint32) * data->header.colorsPerVertex);
//            data->vertices[i].weights = (uint32*)malloc(sizeof(uint32) * data->header.boneCount);

//            uint32 idx = 0;
//            data->vertices[i].position = vertexData[i * perVertexSize + idx++];
//            data->vertices[i].normal = vertexData[i * perVertexSize + idx++];
//            for (int j = 0; j < data->header.uvsPerVertex; j++) {
//                data->vertices[i].uvs[j] = vertexData[i * perVertexSize + idx++];
//            }
//            for (int j = 0; j < data->header.colorsPerVertex; j++) {
//                data->vertices[i].colors[j] = vertexData[i * perVertexSize + idx++];
//            }
//            for (int j = 0; j < data->header.boneCount; j++) {
//                data->vertices[i].weights[j] = vertexData[i * perVertexSize + idx++];
//            }

            uint32 idx = 0;
            uint32 positionIdx = i * perVertexSize + idx++;
            uint32 normalIdx = i * perVertexSize + idx++;

            auto* uvIndexes = (uint32*)malloc(sizeof(uint32) * data->header.uvsPerVertex);
            for (uint32 j = 0; j < data->header.uvsPerVertex; j++) {
                uvIndexes[j] = i * perVertexSize + idx++;
            }
            //uint32 uvIdx = i * perVertexSize + idx++;

            auto* colorIndexes = (uint32*)malloc(sizeof(uint32) * data->header.colorsPerVertex);
            for (uint32 j = 0; j < data->header.colorsPerVertex; j++) {
                colorIndexes[j] = i * perVertexSize + idx++;
            }
            //uint32 colorIdx = i * perVertexSize + idx++;

            uint32 weightIdx = i * perVertexSize + idx++;

            auto* position = (float(*)[3])&positions[vertexData[positionIdx]];
            data->positions[i] = Vector3(*position);

            auto* normal = (float(*)[3])&normals[vertexData[normalIdx]];
            data->normals[i] = Vector3(*normal);

            for (uint32 j = 0; j < data->header.uvsPerVertex; j++) {
                auto* uv = (float(*)[2])&uvs[vertexData[uvIndexes[j]]];
                data->uvs[i] = Vector2(*uv); // -> data->uvs[j][i]
            }


            for (uint32 j = 0; j < data->header.colorsPerVertex; j++) {
                auto* color = (float(*)[4])&colors[vertexData[colorIndexes[j]]];
                data->colors[i] = LinearColor((*color)[0], (*color)[1], (*color)[2], (*color)[3]); // -> data->colors[j][i]
            }

            float weight = boneWeights[vertexData[weightIdx]];
            data->boneWeights[i] = weight;
        }

        free(vertexData);

        free(positions);
        free(normals);
        free(uvs);
        free(colors);
        free(boneWeights);

        // Read smoothing groups
        data->smoothingGroups = (MeshData::SmoothingGroup*)malloc(sizeof(MeshData::SmoothingGroup) * data->header.smoothingGroupCount);

        auto* groupSizes = (uint32*)malloc(sizeof(uint32) * data->header.smoothingGroupCount);

        if (fread(groupSizes, sizeof(uint32), data->header.smoothingGroupCount, source) != data->header.smoothingGroupCount) {
            ENGINE_DEBUG_ERROR("Failed to read group size data from file '{0}'", path);
            fclose(source);
            return nullptr;
        }

        for (int i = 0; i < data->header.smoothingGroupCount; i++) {
            data->smoothingGroups[i] = MeshData::SmoothingGroup();
            data->smoothingGroups[i].faceCount = groupSizes[i];
            data->smoothingGroups[i].faces = (MeshData::Face*)malloc(sizeof(MeshData::Face) * groupSizes[i]);
        }

        fclose(source);
        return instance;
    }

}