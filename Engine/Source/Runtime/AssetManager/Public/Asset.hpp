/**
 * Asset.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_ASSET_MANAGER_ASSET_H_
#define SEEDENGINE_INCLUDE_RUNTIME_ASSET_MANAGER_ASSET_H_

#include "AssetManagerAPI.hpp"
#include "String.hpp"
#include "SmartPointer.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    template <typename DataType, typename AssetType>
    class ENGINE_API Asset {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Asset objects.
             * @details Constructs a new Asset with default initialization for all members.
             */
            Asset() {

            }

            /**
             * @brief The copy constructor for Asset objects.
             * @details Constructs a new Asset by copying an existing Asset.
             */
            Asset(const Asset& ref) = default;
            
            /**
             * @brief The move constructor for Asset objects.
             * @details Constructs a new Asset by moving the data of a Asset into this object.
             */
            Asset(Asset&& ref) = default;

            /**
             * @brief The destructor for Asset objects.
             * @details Called when an instance of Asset is deleted.
             */
            virtual ~Asset() {

            }

        // Functions

            [[nodiscard]] inline String path() const { return m_path; }

            [[nodiscard]] inline bool isLoaded() const { return m_is_loaded; }

            [[nodiscard]] inline       WeakPtr<DataType> data()       { return m_data; }
            [[nodiscard]] inline const WeakPtr<DataType> data() const { return m_data; }

        // Operators

            /**
             * @brief The copy assignment operator for Asset objects.
             * @details Reassigns the value of this object by copying the data of a Asset into this object.
             */
            Asset& operator=(const Asset& ref) = default;

            /**
             * @brief The move assignment operator for Asset objects.
             * @details Reassigns the value of this object by moving the data of a Asset into this object.
             */
            Asset& operator=(Asset&& ref) = default;

        protected:

            void markLoaded() {
                if (m_is_loaded) return;
                else m_is_loaded = true;
            }

            void markUnloaded() {
                if (!m_is_loaded) return;
                else m_is_loaded = false;
            }

            virtual AssetType& load() = 0;
            virtual AssetType& unload() = 0;

        private:

            String m_path;

            bool m_is_loaded;

            SharedPtr<DataType> m_data;

    };

}

#endif