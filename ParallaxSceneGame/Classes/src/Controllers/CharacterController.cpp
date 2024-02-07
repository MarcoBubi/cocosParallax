#include "Controllers/CharacterController.h"

#include "AssetManager/AssetManagerSingleton.h"
#include "Game/GameEvents.h"
#include "Game/GameEventsPriority.h"

CharacterController::CharacterController(cocos2d::Sprite* characterSprite, cocos2d::EventDispatcher& eventDispatcher)
    : _characterSprite(characterSprite)
    , _eventDispatcher(eventDispatcher)
    , _jumpHeightPercentage(.15f)
    , _jumpEventListener(nullptr)
    , _characterUpdatedEventListener(nullptr) {
}

CharacterController::~CharacterController() {
    if (_jumpEventListener) {
        _eventDispatcher.removeEventListener(_jumpEventListener);
    }
    
    if (_characterUpdatedEventListener)
    {
        _eventDispatcher.removeEventListener(_characterUpdatedEventListener);
    }
}

void CharacterController::setup() {

    // Register the character to react on the event of avatar change
    _characterUpdatedEventListener = cocos2d::EventListenerCustom::create(GameEvents::EVENT_CHARACTER_AVATAR_CHANGED, 
                                                                           CC_CALLBACK_1(CharacterController::characterUpdateEvent, this));
    _eventDispatcher.addEventListenerWithFixedPriority(_characterUpdatedEventListener, GameEventsPriority::Low);

    // Register the character to react on the event UI button jump pressed with the handle jump event
    _jumpEventListener = cocos2d::EventListenerCustom::create(GameEvents::EVENT_UI_BUTTON_JUMP_PRESSED, CC_CALLBACK_1(CharacterController::handleJumpEvent, this));
    _eventDispatcher.addEventListenerWithFixedPriority(_jumpEventListener, GameEventsPriority::Low);
}

void CharacterController::update(float delta) {
    // Update logic, if any
}

void CharacterController::characterUpdateEvent(cocos2d::EventCustom* event) {
    std::string* path = static_cast<std::string*>(event->getUserData());
    if (path && _characterSprite) {
        std::string fullPath = AssetManagerSingleton::getInstance().getFullPath(*path);
        auto texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(fullPath);
        if (texture && _characterSprite) {
            _characterSprite->setTexture(texture);
        }
    }
}

void CharacterController::handleJumpEvent(cocos2d::EventCustom* event) {
    // If character is linked and the character is doing nothing we can try to jump
    if (_characterSprite && !_characterSprite->getNumberOfRunningActions()) {
        float jumpHeight = cocos2d::Director::getInstance()->getVisibleSize().height * _jumpHeightPercentage;
        auto jumpAction = cocos2d::JumpBy::create(1.0, cocos2d::Vec2(0, 0), jumpHeight, 1);
        _characterSprite->runAction(jumpAction);
    }
}
