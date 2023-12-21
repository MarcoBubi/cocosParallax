#include "CharacterController.h"

CharacterController::CharacterController(cocos2d::Node* characterNode, cocos2d::EventDispatcher& eventDispatcher) 
    : _characterNode(characterNode), _eventDispatcher(eventDispatcher) {
}

void CharacterController::setup() {
    auto listener = cocos2d::EventListenerCustom::create("jump_event", CC_CALLBACK_1(CharacterController::handleJumpEvent, this));
    _eventDispatcher.addEventListenerWithFixedPriority(listener, 1);
}

void CharacterController::update(float delta) {
    // Implement any update logic for the character if needed
}

void CharacterController::handleJumpEvent(cocos2d::EventCustom* event) {
    if (_characterNode && !_characterNode->getNumberOfRunningActions()) {
        auto jumpAction = cocos2d::JumpBy::create(1.0, cocos2d::Vec2(0, 0), 100, 1);
        _characterNode->runAction(jumpAction);
    }
}
