#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "Interfaces/IController.h"
#include <cocos2d.h>

class CharacterController : public IController {
public:
    CharacterController(cocos2d::Sprite* characterNode, cocos2d::EventDispatcher& eventDispatcher);
    virtual ~CharacterController();

    CharacterController(const CharacterController&) = delete;
    CharacterController& operator=(const CharacterController&) = delete;
    CharacterController(CharacterController&&) = delete;
    CharacterController& operator=(CharacterController&&) = delete;

    void setup() override;
    void update(float delta) override;

private:
    cocos2d::Sprite* _characterSprite; // updated to work with sprites directly since they are on the same node, but like this it gives more manipulation
    cocos2d::EventDispatcher& _eventDispatcher;

    cocos2d::EventListenerCustom* _jumpEventListener;
    cocos2d::EventListenerCustom* _characterUpdatedEventListener;

    float _jumpHeightPercentage; // Percentage of the screen height for the jump

    void characterUpdateEvent(cocos2d::EventCustom* event); // Method to update the character sprite
    void handleJumpEvent(cocos2d::EventCustom* event); // Method to make the character jump
};

#endif // CHARACTERCONTROLLER_H
