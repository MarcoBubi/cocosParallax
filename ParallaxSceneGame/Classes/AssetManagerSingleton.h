#ifndef ASSET_MANAGER_SINGLETON_H
#define ASSET_MANAGER_SINGLETON_H

#include <string>
#include <unordered_map>
#include <list>
#include <cocos2d.h>

class AssetManagerSingleton {
public:
    static AssetManagerSingleton& getInstance();

    cocos2d::Sprite* GetSprite(const std::string& filename);
    void UpdateResolution(float newScaleFactor);
    void setBasePath(const std::string& path);

    std::string getFullPath(const std::string& filename) const;
    bool fileExists(const std::string& filename) const;

private:
    AssetManagerSingleton();
    ~AssetManagerSingleton();

    // Copy and Move constructors and assignment operators are disabled
    AssetManagerSingleton(const AssetManagerSingleton&) = delete;
    AssetManagerSingleton(AssetManagerSingleton&&) = delete;
    AssetManagerSingleton& operator=(const AssetManagerSingleton&) = delete;
    AssetManagerSingleton& operator=(AssetManagerSingleton&&) = delete;

    std::unordered_map<std::string, std::pair<cocos2d::Sprite*, std::list<std::string>::iterator>> _spriteCache;
    std::list<std::string> _usageList;
    size_t _maxCacheSize;
    float _scaleFactor;
    std::string _basePath;

    // Additional private helper methods as needed
};

#endif // ASSET_MANAGER_SINGLETON_H