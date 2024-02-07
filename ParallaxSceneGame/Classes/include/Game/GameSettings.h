#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include <cocos2d.h>

class GameSettings {
public:
    static GameSettings& getInstance();

    void calculateScaleFactors();
    void calculateAspectRatios();

    float getScaleFactorWidth() const;
    float getScaleFactorHeight() const;
    float getDesignAspectRatio() const;
    float getCurrentAspectRatio() const;

private:
    GameSettings();
    ~GameSettings() = default;

    GameSettings(const GameSettings&) = delete;
    GameSettings(GameSettings&&) = delete;

    GameSettings& operator=(const GameSettings&) = delete;
    GameSettings& operator=(GameSettings&&) = delete;

    cocos2d::Size _designResolution;
    cocos2d::Size _visibleSize;
    float _scaleFactorWidth;
    float _scaleFactorHeight;
    float _designAspectRatio;
    float _currentAspectRatio;
};

#endif // GAME_SETTINGS_H