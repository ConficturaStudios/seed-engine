#ifndef SEEDENGINE_INCLUDE_ASSET_H_
#define SEEDENGINE_INCLUDE_ASSET_H_

#include "Core.hpp"

namespace seedengine {

    //TODO: Add asset thread safety.

    // Custom Asset Macros

    #define ENGINE_ASSET_BODY() template <class AssetData, class AssetType>\
        friend class AssetLibrary;

    // An asset with data type T.
    template <class T>
    class Asset {

        ENGINE_ASSET_BODY()

    public:

        // Gets the path to this asset. Returns an empty string if no path exits.
        // @returns: The path to this asset.
        inline std::string path() { return path_; }
        // Gets the data of this asset.
        // @returns: The data of this asset.
        inline std::shared_ptr<T> data() { return data_; }

        // Is this asset loaded into memory?
        // @returns: True if the asset has been loaded.
        inline bool isLoaded() { return data_ != nullptr; }

    protected:

        // The file path to this asset.
        std::string path_;
        // The data stored in this asset.
        std::shared_ptr<T> data_;

        // Constructs a new asset from data in a file.
        // @param(const std::string&) path: The path to the asset to be loaded.
        Asset(const std::string& path) : path_(path), data_(nullptr) {
            std::ifstream test_path(path);
            if (!test_path) throw std::invalid_argument("Asset path '" + path + "' not found.");
        }

        // Loads this asset into memory.
        virtual void load() = 0;
        // Unloads this asset from memory.
        virtual void unload() = 0;

    };

    // A library of assets of type AssetType that encapsulate type AssetData.
    template <class AssetData, class AssetType>
    class AssetLibrary {

    public:

        // Constructs a new asset library.
        AssetLibrary() {
            // Ensure that AssetType is an Asset<AssetData>
            static_assert(std::is_base_of<Asset<AssetData>, AssetType>::value,
                "AssetType is not of type Asset<AssetData>.");
            // Initialize map
            atlas_ = std::map<std::string, std::shared_ptr<AssetType>>();
        }
    
        // Requests an asset from the library by path. If the asset is not loaded in memory or
        // does not exist, nullptr will be returned.
        // @param(const std::string&) path: The path to the asset.
        // @returns: A pointer to the requested asset.
        std::shared_ptr<AssetType> request(const std::string& path) const {
            if (atlas_.count(path) != 0) return nullptr;
            else if (atlas_.at(path)->isLoaded()) return atlas_.at(path);
            else return nullptr;
        }

        // Creates a new asset from the disk and adds it into the library.
        // @param(const std::string&) path: The path to the asset.
        // @returns: A pointer to the prepared asset.
        std::shared_ptr<AssetType> prepare(const std::string& path) {
            std::shared_ptr<AssetType> newAsset(new AssetType(path));
            atlas_[path] = newAsset;
            return newAsset;
        }

        // Loads an asset from the disk into memory. If the asset is already loaded, nothing happens.
        // If the asset has not yet been added to the library, it is prepared and loaded.
        // @param(const std::string&) path: The path to the asset.
        // @returns: A pointer to the loaded asset.
        std::shared_ptr<AssetType> load(const std::string& path) {
            if (atlas_.count(path) != 0) {
                if (!atlas_.at(path)->isLoaded()) atlas_.at(path)->load();
            }
            else {
                prepare(path)->load();
            }
            return atlas_.at(path);
        }

        // Unloads an asset from memory. If the asset is already unloaded, nothing happens.
        // If the asset does not yet exist, it is created but not loaded.
        // @param(const std::string&) path: The path of the image to unload.
        inline void unload(const std::string& path) {
            if (atlas_.count(path) != 0) {
                if (atlas_.at(path)->isLoaded()) atlas_.at(path)->unload();
            }
            else {
                prepare(path);
            }
        }

        // Unloads all assets from the library.
        inline void unloadAll() {
            for (auto const& x : atlas_) {
                if (x.second->isLoaded()) atlas_[x.first]->unload();
            }
        }

        // Unloads all assets from the library with fewer references than the threshold.
        // @param(unsinged int) threshold: The minimum number of references required to not unload.
        inline void unloadUnused(unsigned int threshold = 2) {
            for (auto const& x : atlas_) {
                if (x.second.use_count() < (int)threshold && x.second->isLoaded()) {
                    atlas_[x.first]->unload();
                }
            }
        }

    protected:

        // A map of all assets in memory to their path reference.
        std::map<std::string, std::shared_ptr<AssetType>> atlas_;

    };

}

#endif