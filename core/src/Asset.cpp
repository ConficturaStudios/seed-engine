#include "Asset.hpp"

namespace seedengine {

    template <class E>
    std::map<std::string, std::shared_ptr<Asset<E>>> AssetLibrary<E>::atlas_;

    template <class E>
    std::shared_ptr<Asset<E>> AssetLibrary<E>::request(const std::string& path) {
        return atlas_[path];
    }

    template <class E>
    std::shared_ptr<Asset<E>> AssetLibrary<E>::prepare(const std::string& path) {
        std::shared_ptr<Asset<E>> newAsset(new Asset<E>(path));
        atlas_[path] = newAsset;
        return newAsset;
    }

    template <class E>
    std::shared_ptr<Asset<E>> AssetLibrary<E>::load(const std::string& path) {
        if (atlas_.contains(path)) {
            if (!atlas_[path]->isLoaded()) atlas_[path]->load();
        }
        else {
            prepare(path)->load();
        }
        return atlas_[path];
    }

    template <class E>
    void AssetLibrary<E>::unload(const std::string& path) {
        if (atlas_.contains(path)) {
            if (atlas_[path]->isLoaded()) atlas_[path]->unload();
        }
        else {
            prepare(path);
        }
        return atlas_[path];
    }

    template <class E>
    void AssetLibrary<E>::unloadAll() {
        for (auto const& x : atlas_) {
            if (x.second->isLoaded()) atlas_[x.first]->unload();
        }
    }

    template <class E>
    void AssetLibrary<E>::unloadUnused(unsigned int threshold) {
        for (auto const& x : atlas_) {
            if (x.second.use_count() < (int)threshold && x.second->isLoaded()) {
                atlas_[x.first]->unload();
            }
        }
    }

}