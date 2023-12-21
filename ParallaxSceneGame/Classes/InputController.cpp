#include "InputController.h"
#include "ui/CocosGUI.h"

InputController::InputController(cocos2d::Node* parent, cocos2d::EventDispatcher& eventDispatcher) 
    : _parent(parent), _eventDispatcher(eventDispatcher) {}

void InputController::setup() {
    setupTouchListener();
}

void InputController::update(float delta) {
    // Handle continuous input if necessary
}

void InputController::registerListenerToButton(cocos2d::ui::Button* button, const std::string& eventName)
{
    button->addTouchEventListener([=](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            cocos2d::EventCustom event(eventName.c_str());
            _eventDispatcher.dispatchEvent(&event);
        }
    });
}

void InputController::setupTouchListener() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(InputController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(InputController::onTouchMoved, this);

    _parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, _parent);
}

bool InputController::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

    return true;
}

void InputController::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto diff = touch->getDelta();

    cocos2d::Vec2* diffData = new cocos2d::Vec2(diff); // Allocate new data to pass with the event
    cocos2d::EventCustom draggedEvent("EVENT_SCENE_DRAGGED");
    draggedEvent.setUserData(static_cast<void*>(diffData));

    _eventDispatcher.dispatchEvent(&draggedEvent);

    delete diffData; // Clean up after dispatching
}