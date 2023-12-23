#include "Game/GameSettings.h"
#include "Game/GameConstants.h"

GameSettings& GameSettings::getInstance() {
    static GameSettings instance;
    return instance;
}

GameSettings::GameSettings() {
    _visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    _designResolution = GameConstants::DESIGN_RESOLUTION;

    calculateScaleFactors();
    calculateAspectRatios();
}

void GameSettings::calculateScaleFactors() {
    _scaleFactorWidth = _visibleSize.width / _designResolution.width;
    _scaleFactorHeight = _visibleSize.height / _designResolution.height;
}

void GameSettings::calculateAspectRatios()
{
    _designAspectRatio = _designResolution.width / _designResolution.height;
    _currentAspectRatio = _visibleSize.width / _visibleSize.height;
}

float GameSettings::getScaleFactorWidth() const {
    return _scaleFactorWidth;
}

float GameSettings::getScaleFactorHeight() const {
    return _scaleFactorHeight;
}

float GameSettings::getDesignAspectRatio() const
{
    return _designAspectRatio;
}

float GameSettings::getCurrentAspectRatio() const
{
    return _currentAspectRatio;
}
