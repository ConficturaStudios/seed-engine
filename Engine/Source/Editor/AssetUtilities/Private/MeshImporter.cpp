/**
 * @file MeshImporter.cpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "MeshImporter.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace seedengine {

    bool MeshImporter::Import(const char* path) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path,
            aiProcess_Triangulate);

        if (!scene) {
            // TODO: Output to error log, failed to import
            return false;
        }

        // TODO: Allow user to input import properties when requesting an import

        // Iterate through all meshes
        for (uint32 i = 0; i < scene->mNumMeshes; i++) {
            // Get mesh, allocate storage
            const aiMesh* mesh = scene->mMeshes[i];
            //MeshData data; // TODO: Fix mesh data generation

            // Iterate through vertices
            for (uint32 j = 0; j < mesh->mNumVertices; j++) {
                // Store position and normals
                const aiVector3D* pos = &(mesh->mVertices[j]);
                const aiVector3D* normal = &(mesh->mNormals[j]);
                // Gets UVs
                const aiVector3D* uvs[AI_MAX_NUMBER_OF_TEXTURECOORDS] = {};
                uint32 uvChannelCount = 0;
                for (uint32 t = 0; t < AI_MAX_NUMBER_OF_TEXTURECOORDS; t++) {
                    if (mesh->HasTextureCoords(t)) {
                        uvs[t] = mesh->mTextureCoords[t];
                        uvChannelCount++;
                    }
                    else break;
                }
                // Get colors
                const aiColor4D* colors[AI_MAX_NUMBER_OF_COLOR_SETS] = {};
                uint32 colorSetCount = 0;
                for (uint32 c = 0; c < AI_MAX_NUMBER_OF_COLOR_SETS; c++) {
                    if (mesh->HasVertexColors(c)) {
                        colors[c] = mesh->mColors[c];
                        colorSetCount++;
                    }
                    else break;
                }

                // TODO: Store vertex data
            }

            // TODO: Handle bone and animation data

            // Iterate through faces
            for (uint32 j = 0; j < mesh->mNumFaces; j++) {
                const aiFace& face = mesh->mFaces[j];
                for (uint32 k = 0; k < face.mNumIndices; k++) {
                    // TODO: Store indices data
                    // TODO: Handle smoothing groups
                    // Something like: data.smoothing_group[0].faces[j].vertices[k] = face.mIndices[k];
                }
            }

            // TODO: Finalize data
            // TODO: Generate .mesh file in asset library or roll into an asset/package file

        }

        return true;
    }
}