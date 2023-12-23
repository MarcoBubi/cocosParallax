#include "UI/CustomUIButton.h"

CustomUIButton* CustomUIButton::create(const std::string& texture) {
    // just a copy of the Button create function, but I like to have it here because
    // of logic purposes and to possibly extend the creation since
    // we are dealing with UI buttons here
    CustomUIButton* btn = new CustomUIButton();
    if (btn && btn->init()) {
        btn->autorelease();
        btn->loadTextures(texture, texture); // Using the same texture for normal and selected states
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}

void CustomUIButton::adjustForResolution(const cocos2d::Size& size) {
    // adjust the scale regarding the size provided
    this->setScale(size.width, size.height);
}
