#include "UIController.h"
#include "ui/CocosGUI.h"

UIController::UIController(cocos2d::Node* parent) : _parent(parent) 
{
    _visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    _origin = cocos2d::Director::getInstance()->getVisibleOrigin();
}

void UIController::setup() {
    ScreenType screenType = determineScreenType();

    switch (screenType) {
    case ScreenType::ASPECT_16_9:
        setupUIForAspectRatio16_9();
        break;
    case ScreenType::ASPECT_4_3:
        setupUIForAspectRatio4_3();
        break;
    case ScreenType::ASPECT_5_4:
        setupUIForAspectRatio5_4();
        break;
        // Handle other cases
    }
}

void UIController::update(float delta) {
    // Implement any continuous update logic if needed
}

void UIController::registerUIElement(IResizableUI* element) {
    _uiElements.push_back(element);
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

void UIController::setupUIForAspectRatio16_9() {
    // TODO: move this and implement it properly to work and to do something for the character
    //setupJumpButton(cocos2d::Vec2(_visibleSize.width / 2 + (_origin.x / 2), 150));
    // Setup UI for 16:9 screens
}

void UIController::setupUIForAspectRatio4_3() {
    // Setup UI for 4:3 screens
}

void UIController::setupUIForAspectRatio5_4() {
    // Setup UI for 5:4 screens
}

// Additional methods for other aspect ratios
