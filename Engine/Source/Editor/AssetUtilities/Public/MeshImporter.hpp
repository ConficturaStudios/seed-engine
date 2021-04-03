/**
 * @file MeshImporter.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_EDITOR_ASSET_UTILITIES_MESH_IMPORTER_H_
#define SEEDENGINE_INCLUDE_EDITOR_ASSET_UTILITIES_MESH_IMPORTER_H_

#include "AssetUtilitiesAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API MeshImporter {

        public:

        // Constructors and destructor

            /**
             * @brief [Deleted] The default constructor for MeshImporter objects.
             * @details Constructs a new MeshImporter with default initialization for all members.
             */
            MeshImporter() = delete;

        // Functions

            /**
             * Imports a 3D scene or model from the specified file path into the editor. This
             * function will generate a file in a format that the engine can load and process.
             * @param path The path to the model or scene to load.
             * @return True if the import was successful.
             */
            static bool Import(const char* path);

    };

}

#endif