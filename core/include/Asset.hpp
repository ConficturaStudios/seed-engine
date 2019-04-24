#ifndef SEEDENGINE_INCLUDE_ASSET_H_
#define SEEDENGINE_INCLUDE_ASSET_H_

#include "Core.hpp"

namespace seedengine {

    // An asset with data type T.
    template <class T>
    class Asset {

        template <class E>
        friend class AssetLibrary;

    public:

        inline std::shared_ptr<T> data() { return data_; }

        inline bool isLoaded() { return data_ == nullptr; }
        
    protected:

        std::string path_;
        std::shared_ptr<T> data_;

        Asset(const std::string& path) : path_(path), data_(nullptr) {}

        virtual void load() const = 0;

        virtual void unload() const = 0;

    };

    // A library of assets of type E.
    template <class E>
    class AssetLibrary {

    public:
    
        // Requests an asset from the library by path. If the asset is not in memory, it will be loaded.
        // If the asset does not exist, nullptr will be returned.
        // @param(const std::string&) path: The path to the asset.
        // @returns: A pointer to the requested asset.
        static std::shared_ptr<Asset<E>> request(const std::string&);

        // Allocates a new asset from the disk into the library.
        // @param(const std::string&) path: The path to the asset.
        // @returns: A pointer to the prepared asset.
        static std::shared_ptr<Asset<E>> prepare(const std::string&);

        // Loads an asset from the disk into memory. If the asset is already loaded, nothing happens.
        // @param(const std::string&) path: The path to the asset.
        // @returns: A pointer to the loaded asset.
        static std::shared_ptr<Asset<E>> load(const std::string&);

        // Unloads an asset from memory. If the asset is already unloaded, nothing happens.
        // If the asset does not yet exist, it is created but not loaded.
        // @param(const std::string&) path: The path of the image to unload.
        static inline void unload(const std::string&);

        // Unloads all assets from the library.
        static inline void unloadAll();

        // Unloads all assets from the library with fewer references than the threshold.
        // @param(unsinged int) threshold: The minimum number of references required to not unload.
        static inline void unloadUnused(unsigned int = 2);

    private:

        // A map of all assets in memory to their path reference.
        static std::map<std::string, std::shared_ptr<Asset<E>>> atlas_;

    };

}

#endif