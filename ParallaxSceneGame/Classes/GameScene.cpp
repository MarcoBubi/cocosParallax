#include "GameScene.h"
#include "ui/CocosGUI.h"

cocos2d::Scene* GameScene::createScene() {
    auto scene = GameScene::create();
    return scene;
}

bool GameScene::init() {

    if (!Scene::init()) {
        return false;
    }

    // Scene setup and initialization goes here, e.g.
    // bg color, adding sprites for the scene will be added here, init of objects, etc.
    // @mkrevatin

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    float x = origin.x + visibleSize.width * 0.5;                   // X for the center of the screen
    float y = origin.y + visibleSize.height * 0.5;                  // y for the center of the screen

    // TODO: split this later into more logical chunks, just idea for now.
    _parallaxNode = cocos2d::ParallaxNode::create();
    _parallaxNode2 = cocos2d::ParallaxNode::create();
    _parallaxNode3 = cocos2d::ParallaxNode::create();
    

    // TODO:  Background environment, don't use hardcoded values - define them all in a separate header.
    // addChild(sprite, layer, motion ratio, position offset(compared to the parent)
    _parallaxNode->addChild(cocos2d::Sprite::create("textures/background_1_sky.png"), 1, cocos2d::Vec2(.05f, .0f), cocos2d::Vec2(x, y));
    _parallaxNode->addChild(cocos2d::Sprite::create("textures/background_2_sky.png"), 2, cocos2d::Vec2(.1f, .0f), cocos2d::Vec2(x, y* .65f));
    _parallaxNode->addChild(cocos2d::Sprite::create("textures/background_4_mountains.png"), 3, cocos2d::Vec2(.2f, .0f), cocos2d::Vec2(x, y * .5f));
    _parallaxNode->addChild(cocos2d::Sprite::create("textures/background_3_mountains.png"), 4, cocos2d::Vec2(.35f, .0f), cocos2d::Vec2(x, y * .45f));
    _parallaxNode->addChild(cocos2d::Sprite::create("textures/background_5_clouds.png"), 5, cocos2d::Vec2(2.4f, .0f), cocos2d::Vec2(x, y * 1.2f));
    _parallaxNode->addChild(cocos2d::Sprite::create("textures/background_6_clouds.png"), 6, cocos2d::Vec2(.45f, .0f), cocos2d::Vec2(x, y * 1.3f));
    _parallaxNode->addChild(cocos2d::Sprite::create("textures/background_8_bushes.png"), 7, cocos2d::Vec2(.55f, .0f), cocos2d::Vec2(x, y * .4f));
    _parallaxNode->addChild(cocos2d::Sprite::create("textures/background_9_trees.png"), 8, cocos2d::Vec2(.62f, .0f), cocos2d::Vec2(x, y * .45f));
    _parallaxNode->addChild(cocos2d::Sprite::create("textures/background_10_trees.png"), 9, cocos2d::Vec2(.83f, .0f), cocos2d::Vec2(x, y * .53f));

    // This is nice when it's not moving. it gives some effect since the main character isn't moving either
    _parallaxNode2->addChild(cocos2d::Sprite::create("textures/background_11_road.png"), 10, cocos2d::Vec2(0.1f, .0f), cocos2d::Vec2(x, y * .25f));
    
    // Create the character sprite
    // TODO: Should this be here anyways? @mkrevatin
    // this should be a standalone imo...todo
    auto character = cocos2d::Sprite::create("textures/character.png");
    character->setName("character");
    _parallaxNode2->addChild(character, 11, cocos2d::Vec2(.0f, .0f), cocos2d::Vec2(x * .7f, y * .48f)); // Position offset

    // Create the foreground sprite
    _parallaxNode3->addChild(cocos2d::Sprite::create("textures/foreground_3_clouds.png"), 12, cocos2d::Vec2(1.2f, .0f), cocos2d::Vec2(x, y * .65f));
    _parallaxNode3->addChild(cocos2d::Sprite::create("textures/foreground_2_tree.png"), 13, cocos2d::Vec2(.3f, .0f), cocos2d::Vec2(x * .05f, y * .45f));
    _parallaxNode3->addChild(cocos2d::Sprite::create("textures/foreground_0_squirrel.png"), 14, cocos2d::Vec2(.4f, .0f), cocos2d::Vec2(x * .4f, y * .16f));
    _parallaxNode3->addChild(cocos2d::Sprite::create("textures/foreground_1_bushes.png"), 15, cocos2d::Vec2(.6f, .0f), cocos2d::Vec2(x * .45f, y * .4f));
    _parallaxNode3->addChild(cocos2d::Sprite::create("textures/foreground_4_bench.png"), 16, cocos2d::Vec2(.8f, .0f), cocos2d::Vec2(x * 1.63f, y * .23f));

    this->addChild(_parallaxNode);
    this->addChild(_parallaxNode2);
    this->addChild(_parallaxNode3);

    // touch listener to move the parallax node // TODO: set this in some kind of parallax controller @mkrevatin
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event) { return true; };
    listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto diff = touch->getDelta();
        auto newPos = _parallaxNode->getPosition() + cocos2d::Vec2(diff.x, 0);
        auto newPos3 = _parallaxNode3->getPosition() + cocos2d::Vec2(diff.x, 0);

        // Limiting the move on each side.
        float limit = 1000; // left set to max -1000
        newPos.x = std::max(newPos.x, -limit);
        newPos.x = std::min(newPos.x, limit);
        newPos3.x = std::max(newPos3.x, -limit);
        newPos3.x = std::min(newPos3.x, limit);

        _parallaxNode->setPosition(newPos);
        _parallaxNode3->setPosition(newPos3);
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // TODO: move this and implement it properly to work and to do something for the character
    auto jumpButton = cocos2d::ui::Button::create(
        "textures/jump_button.png", 
        "textures/jump_button_hover.png"
        "textures/jump_button_inactive.png");
    jumpButton->setPosition(cocos2d::Vec2(visibleSize.width / 2 + (origin.x/2), jumpButton->getContentSize().height * 0.3));
    jumpButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            this->makeCharacterJump();
        }
        });

    this->addChild(jumpButton, 100); // higher z-order so it's rendered above other layers, but mvoe ths in a a different place


    return true;
}

void GameScene::makeCharacterJump() {
    auto character = _parallaxNode2->getChildByName<cocos2d::Sprite*>("character");
    if (character && !character->getNumberOfRunningActions()) {
        auto jumpAction = cocos2d::JumpBy::create(1.0, cocos2d::Vec2(0, 0), 100, 1);
        character->runAction(jumpAction);
    }
}