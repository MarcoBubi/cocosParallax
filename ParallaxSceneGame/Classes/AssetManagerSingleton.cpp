#include "AssetManagerSingleton.h"

AssetManagerSingleton& AssetManagerSingleton::getInstance() {
    static AssetManagerSingleton instance;
    return instance;
}

AssetManagerSingleton::AssetManagerSingleton() : _maxCacheSize(5), _scaleFactor(1.0f) {

    // Initialization code if needed
}

AssetManagerSingleton::~AssetManagerSingleton() {
    // Clean up code: release sprites and clear containers
    for (auto& pair : _spriteCache) {
        pair.second.first->release(); // Assuming you have called retain on the sprite
    }
    _spriteCache.clear();
    _usageList.clear();
}

cocos2d::Sprite* AssetManagerSingleton::GetSprite(const std::string& filename) {
    // Check if sprite is in the cache
    auto mapIt = _spriteCache.find(filename);
    if (mapIt != _spriteCache.end()) {
        // Move the touched sprite to the front of the usage list
        _usageList.splice(_usageList.begin(), _usageList, mapIt->second.second);
        return mapIt->second.first;
    }
    else {
        // Load sprite and scale it based on current resolution
        auto sprite = cocos2d::Sprite::create(_basePath + filename);
        
        if (!sprite) {
            //I should probably throw something here, depending on the game type and behaviour - will leave like this for this scenario
            return nullptr; // Failed to load sprite
        }
        sprite->setName(filename);
        // Perform scaling based on resolution
        sprite->retain(); // Retain the sprite as we are storing it in the cache
        // ... 

        // Insert sprite at the beginning of the usage list
        _usageList.push_front(filename);
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

void AssetManagerSingleton::UpdateResolution(float newScaleFactor) {
    _scaleFactor = newScaleFactor;
    // Update scale for all sprites in cache
    // ...
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

// Additional private helper methods implementation as needed
