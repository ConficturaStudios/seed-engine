#ifndef SEEDENGINE_INCLUDE_ASSET_H_
#define SEEDENGINE_INCLUDE_ASSET_H_

#include "Core.hpp"

namespace seedengine {

    // Custom Asset Macros

    #define ENGINE_ASSET_BODY() template <class AssetData, class AssetType>\
        friend class AssetLibrary;

    // An asset with data type T.
    template <class T>
    class Asset {

        ENGINE_ASSET_BODY()

    public:

        // Gets the path to this image. Returns an empty string if no path exits.
        // @returns: The path to this image.
        inline std::string path() { return path_; }
        // Gets the data of this asset.
        // @returns: The data of this asset.
        inline std::shared_ptr<T> data() { return data_; }

        inline bool isLoaded() { return data_ == nullptr; }

    protected:

        std::string path_;
        std::shared_ptr<T> data_;

        Asset(const std::string& path) : path_(path), data_(nullptr) {}

        virtual void load() = 0;

        virtual void unload() = 0;

    };

    // A library of assets of type AssetType that encapsulate type AssetData.
    template <class AssetData, class AssetType>
    class AssetLibrary {

    public:

        AssetLibrary() {
            static_assert(std::is_base_of<Asset<AssetData>, AssetType>::value,
                "AssetType is not of type Asset.");
            atlas_ = std::map<std::string, std::shared_ptr<AssetType>>();
        }
    
        // Requests an asset from the library by path. If the asset is not loaded in memory or
        // does not exist, nullptr will be returned.
        // @param(const std::string&) path: The path to the asset.
        // @returns: A pointer to the requested asset.
        std::shared_ptr<AssetType> request(const std::string& path) {
            if (atlas_[path]->isLoaded()) return atlas_[path];
            else return nullptr;
        }

        // Allocates a new asset from the disk into the library.
        // @param(const std::string&) path: The path to the asset.
        // @returns: A pointer to the prepared asset.
        std::shared_ptr<AssetType> prepare(const std::string& path) {
            std::shared_ptr<AssetType> newAsset(new AssetType(path));
            atlas_[path] = newAsset;
            return newAsset;
        }

        // Loads an asset from the disk into memory. If the asset is already loaded, nothing happens.
        // @param(const std::string&) path: The path to the asset.
        // @returns: A pointer to the loaded asset.
        std::shared_ptr<AssetType> load(const std::string& path) {
            if (atlas_.find(path) != atlas_.end()) {
                if (!atlas_[path]->isLoaded()) atlas_[path]->load();
            }
            else {
                prepare(path)->load();
            }
            return atlas_[path];
        }

        // Unloads an asset from memory. If the asset is already unloaded, nothing happens.
        // If the asset does not yet exist, it is created but not loaded.
        // @param(const std::string&) path: The path of the image to unload.
        inline void unload(const std::string& path) {
            if (atlas_.find(path) != atlas_.end()) {
                if (atlas_[path]->isLoaded()) atlas_[path]->unload();
            }
            else {
                prepare(path);
            }
            return atlas_[path];
        }

        // Unloads all assets from the library.
        inline void unloadAll() {
            for (auto const& x : atlas_) {
                if (x.second->isLoaded()) atlas_[x.first]->unload();
            }
        }

        // Unloads all assets from the library with fewer references than the threshold.
        // @param(unsinged int) threshold: The minimum number of references required to not unload.
        inline void unloadUnused(unsigned int = 2) {
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