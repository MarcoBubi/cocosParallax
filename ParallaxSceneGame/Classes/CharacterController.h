#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "IController.h"
#include <cocos2d.h>

class CharacterController : public IController {
public:
    explicit CharacterController(cocos2d::Node* characterNode, cocos2d::EventDispatcher& eventDispatcher);

    void setup() override;
    void update(float delta) override;

private:
    cocos2d::Node* _characterNode;
    cocos2d::EventDispatcher& _eventDispatcher;

    void handleJumpEvent(cocos2d::EventCustom* event);  // Method to make the character jump
};

#endif // CHARACTERCONTROLLER_H
