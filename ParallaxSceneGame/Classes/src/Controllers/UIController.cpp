#include "Controllers/UIController.h"
#include "Game/GameSettings.h"
#include <algorithm>

UIController::UIController(cocos2d::Node* parent)
    : _parent(parent), _scaleFactorWidth(1.0f), _scaleFactorHeight(1.0f) {
}

UIController::~UIController()
{

}

void UIController::setup() {
    _visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    calculateScaleFactors(); // This will now set the scale factors directly
}

void UIController::update(float delta) {
    // Implement any continuous update logic if needed - not for now though
}

void UIController::registerUIElement(IResizableUI* element) {
    _uiElements.push_back(element);
    // Scale the element
    cocos2d::Size size = { _scaleFactorWidth, _scaleFactorHeight };
    // Perhaps this should be a function itself, but I can't really think of why this would be bad for now
    element->adjustForResolution(size);
}

void UIController::calculateScaleFactors() {
    // Get designed resolution and get aspect ratio
    GameSettings& gameSettings = GameSettings::getInstance();

    _scaleFactorWidth = gameSettings.getScaleFactorWidth();
    _scaleFactorHeight = gameSettings.getScaleFactorHeight();

    if (gameSettings.getCurrentAspectRatio() != gameSettings.getDesignAspectRatio()) {
        // Use the smaller scale factor for both dimensions to maintain aspect ratio
        float uniformScaleFactor = std::min(_scaleFactorWidth, _scaleFactorHeight);
        _scaleFactorWidth = uniformScaleFactor; // huh, _scaleFactorWidth = _scaleFactorHeight = uniformScaleFactor
        _scaleFactorHeight = uniformScaleFactor;
    }
}
