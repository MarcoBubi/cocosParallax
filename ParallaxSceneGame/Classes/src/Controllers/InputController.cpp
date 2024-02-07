#include "Controllers/InputController.h"
#include "Game/GameEvents.h"
#include "Game/GameEventsPriority.h"
#include "ui/CocosGUI.h"

InputController::InputController(cocos2d::Node* parent, cocos2d::EventDispatcher& eventDispatcher)
    : _parent(parent), _eventDispatcher(eventDispatcher), _touchListener(nullptr) {
}

InputController::~InputController() {
    // Remove listener if still available
    if (_touchListener) {
        _parent->getEventDispatcher()->removeEventListener(_touchListener);
    }
}

void InputController::setup() {
    setupTouchListener();
}

void InputController::update(float delta) {
    // Update logic, if any
}

void InputController::registerListenerToButton(cocos2d::ui::Button* button, const std::string& eventName) {
    // Register the button to a specific event provided
    button->addTouchEventListener([this, eventName](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            cocos2d::EventCustom event(eventName.c_str());
            _eventDispatcher.dispatchEvent(&event);
        }
        });
}

void InputController::setupTouchListener() {
    // Register drag event and touch event on the system
    _touchListener = cocos2d::EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(InputController::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(InputController::onTouchMoved, this);

    _parent->getEventDispatcher()->addEventListenerWithFixedPriority(_touchListener, GameEventsPriority::Low);
}

bool InputController::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    return true;
}

void InputController::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto diff = touch->getDelta();
    cocos2d::EventCustom draggedEvent(GameEvents::EVENT_SCENE_DRAGGED);
    draggedEvent.setUserData(new cocos2d::Vec2(diff)); // Pass data through the event

    _eventDispatcher.dispatchEvent(&draggedEvent); // Broadcast the event to the system
}

