#ifndef SEEDENGINE_INCLUDE_ASSET_H_
#define SEEDENGINE_INCLUDE_ASSET_H_

#include "Core.hpp"

namespace seedengine {

    //TODO: Add asset thread safety.

    // Custom Asset Macros

    /**
     * @brief The standard body to include in all engine assets.
     */
    #define ENGINE_ASSET_BODY() \
        template <class AssetType>\
        friend class AssetLibrary;

    /**
     * @brief An asset with data type T.
     * @details A data asset that is loaded from the disk on demand. The asset is
     *          associated with its path on the disk within an #AssetLibrary.
     * 
     * @tparam T The type of data stored.
     * 
     * @see #AssetLibrary
     */
    template <class T>
    class Asset {

        ENGINE_ASSET_BODY()

    public:

        /**
         * @brief Gets the path to this asset. Returns an empty string if no path exits.
         * 
         * @return The path to this asset.
         */
        inline string path() { return path_; }
        
        /**
         * @brief Gets the data of this asset.
         * 
         * @return The data of this asset.
         */
        inline T* data() { return data_; }

        /**
         * @brief Is this asset loaded into memory?
         * 
         * @return True if the asset has been loaded.
         */
        inline bool isLoaded() { return data_ != nullptr; }

    protected:

        /**
         * @brief The file path to this asset.
         */
        string path_;
        /**
         * @brief The data stored in this asset.
         */
        T* data_;

        /**
         * @brief Construct a new Asset object from data in a file.
         * 
         * @param path The path to the asset to be loaded.
         */
        Asset(const string& path) : path_(path), data_(nullptr) {
            std::ifstream test_path(path);
            if (!test_path) throw std::invalid_argument("Asset path '" + path + "' not found.");
        }

        /**
         * @brief Loads this asset into memory.
         */
        virtual void load() = 0;
        /**
         * @brief Unloads this asset from memory.
         */
        virtual void unload() = 0;

    };

    /**
     * @brief A library of assets of type AssetType that encapsulate type AssetData.
     * @details 
     * 
     * @tparam AssetData The type of data encapsulated by assets in this library.
     * @tparam AssetType The type of asset stored in this library.
     * 
     * @see #Asset
     */
    template <class T>
    class AssetLibrary final {

    public:

        /**
         * @brief Construct a new Asset Library object
         */
        /*AssetLibrary() {
            // Ensure that AssetType is an Asset<AssetData>
            //static_assert(std::is_base_of<Asset<AssetData>, AssetType>::value,
            //    "AssetType is not of type Asset<AssetData>.");
            static_assert(is_base_of_t<Asset, AssetType>::value,
                "AssetType is not of type Asset.");
            // Initialize map
            atlas_ = std::unordered_map<string, std::shared_ptr<AssetType>>();
        }*/

        /**
         * @brief Requests an asset from the library by path.
         * @details Requests an asset from the library by path. If the asset is not loaded in memory or
         *          does not exist, nullptr will be returned.
         * 
         * @param path The path to the asset.
         * 
         * @return A pointer to the requested asset.
         */
        template <typename = std::enable_if<is_base_of_t<Asset, T>::value>::type>
        static std::shared_ptr<T> request(const string& path) {
            //ENGINE_DEBUG("Requesting asset '" + path + "'...");
            if (atlas_.find(path) == atlas_.end()) {
                ENGINE_WARN("Asset '" + path + "' was not found.");
                return nullptr;
            }
            else if (atlas_.at(path)->isLoaded()) {
                //ENGINE_DEBUG("Found loaded asset '" + path + "'.");
                return atlas_.at(path);
            }
            else {
                ENGINE_WARN("Asset '" + path + "' is not loaded.");
                return nullptr;
            }
        }

        /**
         * @brief Creates a new asset from the disk and adds it into the library.
         * @details This will create a new asset in the library without loading its data
         *          into memory. Call load() to load the data into memory before use.
         * 
         * @param path The path to the asset.
         * 
         * @return A pointer to the prepared asset.
         */
        template <typename = std::enable_if<is_base_of_t<Asset, T>::value>::type>
        static std::shared_ptr<T> prepare(const string& path) {
            atlas_.insert(std::pair<string, std::shared_ptr<T>>(path, std::shared_ptr<T>(new T(path))));
            return atlas_.at(path);
        }

        /**
         * @brief Loads an asset from the disk into memory.
         * @details Loads an asset from the disk into memory. If the asset is already loaded, nothing happens.
         *          If the asset has not yet been added to the library, it is prepared and loaded.
         * 
         * @param path The path to the asset.
         * 
         * @return A pointer to the loaded asset.
         */
        template <typename = std::enable_if<is_base_of_t<Asset, T>::value>::type>
        static std::shared_ptr<T> load(const string& path) {
            if (atlas_.find(path) != atlas_.end()) {
                if (!atlas_.at(path)->isLoaded()) atlas_.at(path)->load();
            }
            else {
                prepare(path)->load();
            }
            return atlas_.at(path);
        }

        /**
         * @brief Unloads an asset from memory.
         * @details Unloads an asset from memory. If the asset is already unloaded, nothing happens.
         *          If the asset does not yet exist in the library, it is created but not loaded.
         * 
         * @param path The path of the image to unload.
         */
        template <typename = std::enable_if<is_base_of_t<Asset, T>::value>::type>
        static inline void unload(const string& path) {
            if (atlas_.count(path) != 0) {
                if (atlas_.at(path)->isLoaded()) atlas_.at(path)->unload();
            }
            else {
                prepare(path);
            }
        }

        /**
         * @brief Unloads all assets from the library.
         */
        template <typename = std::enable_if<is_base_of_t<Asset, T>::value>::type>
        static inline void unloadAll() {
            for (auto const& x : atlas_) {
                if (x.second->isLoaded()) atlas_[x.first]->unload();
            }
        }

        /**
         * @brief Unloads all assets from the library with fewer references than the threshold.
         * 
         * @param threshold The minimum number of references required to not unload.
         */
        template <typename = std::enable_if<is_base_of_t<Asset, T>::value>::type>
        static inline void unloadUnused(unsigned int threshold = 2) {
            for (auto const& x : atlas_) {
                if (x.second.use_count() < (int)threshold && x.second->isLoaded()) {
                    atlas_[x.first]->unload();
                }
            }
        }

    private:

        /**
         * @brief A map of all assets in memory to their path reference.
         */
        static std::unordered_map<string, std::shared_ptr<T>> atlas_;

    };

    template <class T>
    std::unordered_map<string, std::shared_ptr<T>> AssetLibrary<T>::atlas_ = std::unordered_map<string, std::shared_ptr<T>>();

}

#endif