#include "AssetManager/AssetManagerSingleton.h"

AssetManagerSingleton& AssetManagerSingleton::getInstance() {
    static AssetManagerSingleton instance;
    return instance;
}

AssetManagerSingleton::AssetManagerSingleton() : _maxCacheSize(5) {
    // we setup a max cache of 5 just for the sake of the idea, since we are dealing with a low number of textures
}

AssetManagerSingleton::~AssetManagerSingleton() {
    // we release the sprites and clear the containers
    for (auto& pair : _spriteCache) {
        pair.second.first->release(); // we retain each sprite, so we should release them too if they are not automatically released
    }
    _spriteCache.clear();
    _usageList.clear();
}

cocos2d::Sprite* AssetManagerSingleton::GetSprite(const std::string& filename) {
    // we check in the iterator if the file is already cached in the map
    auto mapIt = _spriteCache.find(filename);
    if (mapIt != _spriteCache.end()) {
        // if no sprite found, we add to the begining - simulation of LRU, simple approach
        // used splice because it just rearranges nodes, so it's a bit more optimized
        _usageList.splice(_usageList.begin(), _usageList, mapIt->second.second);
        return mapIt->second.first;
    }
    else {
        // we load the sprite with the concatenation of the texure path and the filename
        auto sprite = cocos2d::Sprite::create(_basePath + filename);
        
        if (!sprite) {
            // depending on scenario we can throw an error here
            return nullptr; // Failed to load sprite
        }
        sprite->retain(); // Retain the sprite as we are storing it in the cache

        // Insert sprite at the beginning of the usage list, LRU 
        _usageList.push_front(filename);
        // add pair to spritecache
        _spriteCache[filename] = std::make_pair(sprite, _usageList.begin());

        // If cache exceeds size limit, remove the least recently used sprite
        if (_spriteCache.size() > _maxCacheSize) {
            auto last = _usageList.end();
            last--;
            auto lastIt = _spriteCache.find(*last);
            if (lastIt != _spriteCache.end()) {
                lastIt->second.first->release(); // Release the sprite
                _spriteCache.erase(lastIt);
            }
            _usageList.pop_back();
        }
        return sprite;
    }
}

void AssetManagerSingleton::setBasePath(const std::string& path)
{
    _basePath = path;
    // creating a base path, adding slash to end just to ensure correct path
    if (!_basePath.empty() && _basePath.back() != '/') {
        _basePath += '/';
    }
}

std::string AssetManagerSingleton::getFullPath(const std::string& filename) const
{
    return _basePath + filename;
}

bool AssetManagerSingleton::fileExists(const std::string& filename) const {
    std::string fullPath = _basePath + filename;
    return cocos2d::FileUtils::getInstance()->isFileExist(fullPath);
}
