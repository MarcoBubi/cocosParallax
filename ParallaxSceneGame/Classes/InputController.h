#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "IController.h"
#include "ui/CocosGUI.h"
#include <cocos2d.h>

class InputController : public IController {
public:
    explicit InputController(cocos2d::Node* parent, cocos2d::EventDispatcher& eventDispatcher);

    void setup() override;
    void update(float delta) override;

    void registerListenerToButton(cocos2d::ui::Button* button, const std::string& eventName);

private:
    cocos2d::Node* _parent;
    cocos2d::EventDispatcher& _eventDispatcher;

    void setupTouchListener();

    // Event callbacks
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif // INPUTCONTROLLER_H