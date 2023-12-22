#include "CustomUIButton.h"

CustomUIButton* CustomUIButton::create() {
    CustomUIButton* btn = new CustomUIButton();
    if (btn && btn->init()) {
        btn->autorelease();
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}

CustomUIButton* CustomUIButton::create(const std::string& texture) {
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
    // adjust button scale?
    this->setScale(size.width, size.height);
}
