#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "Interfaces/IController.h"
#include "ui/CocosGUI.h"
#include <cocos2d.h>

class InputController : public IController {
public:
    InputController(cocos2d::Node* parent, cocos2d::EventDispatcher& eventDispatcher);
    virtual ~InputController();

    InputController(const InputController&) = delete;
    InputController& operator=(const InputController&) = delete;
    InputController(InputController&&) = delete;
    InputController& operator=(InputController&&) = delete;

    void setup() override;
    void update(float delta) override;

    void registerListenerToButton(cocos2d::ui::Button* button, const std::string& eventName);

private:
    cocos2d::Node* _parent;
    cocos2d::EventDispatcher& _eventDispatcher;
    cocos2d::EventListenerTouchOneByOne* _touchListener;

    void setupTouchListener();

    // Event callbacks
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif // INPUTCONTROLLER_H
