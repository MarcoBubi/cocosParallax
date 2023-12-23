#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "Interfaces/IController.h"
#include <cocos2d.h>

class CharacterController : public IController {
public:
    CharacterController(cocos2d::Node* characterNode, cocos2d::EventDispatcher& eventDispatcher);
    virtual ~CharacterController();

    CharacterController(const CharacterController&) = delete;
    CharacterController& operator=(const CharacterController&) = delete;
    CharacterController(CharacterController&&) = delete;
    CharacterController& operator=(CharacterController&&) = delete;

    void setup() override;
    void update(float delta) override;

private:
    cocos2d::Node* _characterNode;
    cocos2d::EventDispatcher& _eventDispatcher;
    cocos2d::EventListenerCustom* _jumpEventListener;

    float _jumpHeightPercentage; // Percentage of the screen height for the jump

    void handleJumpEvent(cocos2d::EventCustom* event); // Method to make the character jump
};

#endif // CHARACTERCONTROLLER_H
