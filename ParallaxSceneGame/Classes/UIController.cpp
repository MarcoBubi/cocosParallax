#include "UIController.h"
#include "ui/CocosGUI.h"

UIController::UIController(cocos2d::Node* parent) 
    : _parent(parent), _scaleFactorWidth(1), _scaleFactorHeight(1) {
}

void UIController::setup() {
    _visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    ScreenType screenType = determineScreenType();
    calculateScaleFactors(); // This will now set the scale factors directly
    // Other setup code...
}

void UIController::update(float delta) {
    // Implement any continuous update logic if needed
}

void UIController::registerUIElement(IResizableUI* element) {
    _uiElements.push_back(element);
    // Apply scale factors to the newly added element
    cocos2d::Size size = { _scaleFactorWidth, _scaleFactorHeight };
    element->adjustForResolution(size);
}

void UIController::adjustUIElementsForResolution(const cocos2d::Size& size) {
    for (auto& element : _uiElements) {
        element->adjustForResolution(size);
    }
}

UIController::ScreenType UIController::determineScreenType() {
    auto screenSize = cocos2d::Director::getInstance()->getWinSize();
    float aspectRatio = screenSize.width / screenSize.height;

    if (aspectRatio > 1.7) {
        return ScreenType::ASPECT_16_9;
    }
    else if (aspectRatio > 1.3) {
        return ScreenType::ASPECT_4_3;
    }
    else {
        return ScreenType::ASPECT_5_4;
    }
}

void UIController::calculateScaleFactors() {
    // Design resolution and aspect ratio
    cocos2d::Size designResolution(1920, 1080);
    float designAspectRatio = designResolution.width / designResolution.height;

    // Current screen resolution and aspect ratio
    float currentAspectRatio = _visibleSize.width / _visibleSize.height;

    // Calculate individual scale factors
    _scaleFactorWidth = _visibleSize.width / designResolution.width;
    _scaleFactorHeight = _visibleSize.height / designResolution.height;

    // Check if aspect ratios are different
    if (currentAspectRatio != designAspectRatio) {
        // Use the smaller scale factor for both dimensions to maintain aspect ratio
        float uniformScaleFactor = std::min(_scaleFactorWidth, _scaleFactorHeight);
        _scaleFactorWidth = _scaleFactorHeight = uniformScaleFactor;
    }
}

// Additional methods for other aspect ratios
