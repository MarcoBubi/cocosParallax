#include "Controllers/CharacterController.h"
#include "Game/GameEvents.h"

CharacterController::CharacterController(cocos2d::Node* characterNode, cocos2d::EventDispatcher& eventDispatcher)
    : _characterNode(characterNode), _eventDispatcher(eventDispatcher), _jumpHeightPercentage(0.15f), _jumpEventListener(nullptr) {
}

CharacterController::~CharacterController() {
    if (_jumpEventListener) {
        _eventDispatcher.removeEventListener(_jumpEventListener);
    }
}

void CharacterController::setup() {
    // Register the character to react on the event UI button jump pressed with the handle jump event
    _jumpEventListener = cocos2d::EventListenerCustom::create(GameEvents::EVENT_UI_BUTTON_JUMP_PRESSED, CC_CALLBACK_1(CharacterController::handleJumpEvent, this));
    _eventDispatcher.addEventListenerWithFixedPriority(_jumpEventListener, 1);
}

void CharacterController::update(float delta) {
    // Update logic, if any
}

void CharacterController::handleJumpEvent(cocos2d::EventCustom* event) {
    // If character is linked and the character is doing nothing we can try to jump
    if (_characterNode && !_characterNode->getNumberOfRunningActions()) {
        float jumpHeight = cocos2d::Director::getInstance()->getVisibleSize().height * _jumpHeightPercentage;
        auto jumpAction = cocos2d::JumpBy::create(1.0, cocos2d::Vec2(0, 0), jumpHeight, 1);
        _characterNode->runAction(jumpAction);
    }
}
