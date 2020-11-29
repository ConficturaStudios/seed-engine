/**
 * AssetLibrary.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_ASSET_MANAGER_ASSET_LIBRARY_H_
#define SEEDENGINE_INCLUDE_RUNTIME_ASSET_MANAGER_ASSET_LIBRARY_H_

#include "AssetManagerAPI.hpp"
#include "Asset.hpp"
#include "String.hpp"
#include "SmartPointer.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    template <typename AssetType>
    class ENGINE_API AssetLibrary {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for AssetLibrary objects.
             * @details Constructs a new AssetLibrary with default initialization for all members.
             */
            AssetLibrary();

            /**
             * @brief The copy constructor for AssetLibrary objects.
             * @details Constructs a new AssetLibrary by copying an existing AssetLibrary.
             */
            AssetLibrary(const AssetLibrary& ref) = default;
            
            /**
             * @brief The move constructor for AssetLibrary objects.
             * @details Constructs a new AssetLibrary by moving the data of a AssetLibrary into this object.
             */
            AssetLibrary(AssetLibrary&& ref) = default;

            /**
             * @brief The destructor for AssetLibrary objects.
             * @details Called when an instance of AssetLibrary is deleted.
             */
            virtual ~AssetLibrary();

        // Functions

            static bool terminate();

            static bool unloadAll();
            static bool unloadUnused();

            static WeakPtr<AssetType> load(/*AssetID id*/);
            static WeakPtr<AssetType> unload(/*AssetID id*/);

            [[nodiscard]] static WeakPtr<AssetType> request(/*AssetID id*/);

        // Operators

            /**
             * @brief The copy assignment operator for AssetLibrary objects.
             * @details Reassigns the value of this object by copying the data of a AssetLibrary into this object.
             */
            AssetLibrary& operator=(const AssetLibrary& ref) = default;

            /**
             * @brief The move assignment operator for AssetLibrary objects.
             * @details Reassigns the value of this object by moving the data of a AssetLibrary into this object.
             */
            AssetLibrary& operator=(AssetLibrary&& ref) = default;

        protected:

        private:

    };

}

#endif