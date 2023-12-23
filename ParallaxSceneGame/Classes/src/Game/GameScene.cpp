#include "Game/GameScene.h"

#include "UI/CustomUIButton.h"
#include "Game/GameConstants.h"
#include "Game/GameEvents.h"

cocos2d::Scene* GameScene::createScene() {
    return GameScene::create();
}

bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    AssetManagerSingleton& assetManager = AssetManagerSingleton::getInstance();                     // set assetmanager as ref so we save a bit of func. calls
    assetManager.setBasePath(GameConstants::TEXTURES_DIR);                                          // specify path for where to look for the textures.

    _inputController = std::make_unique<InputController>(this, *this->getEventDispatcher());        // init input controller for general inputs in the game, like dragging, etc...
    _inputController->setup();                                                                      // setup the controller's basic stuff

    _uiController = std::make_unique<UIController>(this);                                           // init ui controller to setup UI and scale it depending on resolution, aspect ratio,...
    _uiController->setup();                                                                         // setup the controller's basic stuff

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();                          // get visible size so we can have a viewpoint
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();                             // same for origin point
    float x = visibleSize.width / 2 + origin.x;                                                     // X for the center of the screen
    float y = origin.y;                                                                             // y for the origin of the screen

    // create takes care of setting the autorealease functionality up.
    CustomUIButton* jumpButton = CustomUIButton::create(assetManager.getFullPath("jump_button.png"));   // creating the jump button 
    _uiController->registerUIElement(jumpButton);                                                       // register the button to the ui controller for scaling purposes and position
    _inputController->registerListenerToButton(jumpButton, GameEvents::EVENT_UI_BUTTON_JUMP_PRESSED);   // register the jump button to the input controller
    jumpButton->setAnchorPoint(cocos2d::Vec2(0.5f, 0.0f));                                              // setting anchor point to bottom middle since we want it to always be there(do we?)
    jumpButton->setPosition(cocos2d::Vec2(x, origin.y));                                                //offset the object from the bottom, just a bit
    this->addChild(jumpButton, GameConstants::UI_LAYER_Z_ORDER);

    _parallaxController = std::make_unique<ParallaxController>(this, *this->getEventDispatcher());  // init parallax controller to control the layers of the parallax nodes
    _parallaxController->setup();                                                                   // setup the controller's basic stuff
    // Add all the textures to the parallax controller
    //Background level
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_1_sky.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.05f, .0f), cocos2d::Vec2(x, y));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_2_sky.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.1f, .0f), cocos2d::Vec2(x, y));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_3_mountains.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.2f, .0f), cocos2d::Vec2(x, y));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_4_clouds.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.35f, .0f), cocos2d::Vec2(x, 650));

    // changed this clouds ratio just for the sake of dynamics and testability, not sure if it breaks the parallax principle.
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_5_mountains.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.45f, .0f), cocos2d::Vec2(x, y));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_6_clouds.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(2.0f, .0f), cocos2d::Vec2(x, 580));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_7_bushes.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.55f, .0f), cocos2d::Vec2(x, y));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_8_trees.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.62f, .0f), cocos2d::Vec2(x, y));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_9_trees.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.83f, .0f), cocos2d::Vec2(x, y));

    //Focus layer
    _parallaxController->addSpriteToLayerWithAutoZOrder("focus_1_road.png", ParallaxController::ParallaxLayer::Focus, cocos2d::Vec2(0.1f, .0f), cocos2d::Vec2(x, 80));
    _parallaxController->addSpriteToLayerWithAutoZOrder("character.png", ParallaxController::ParallaxLayer::Focus, cocos2d::Vec2(.0f, .0f), cocos2d::Vec2(x * .7f, 200));

    //Foreground layer
    _parallaxController->addSpriteToLayerWithAutoZOrder("foreground_1_clouds.png", ParallaxController::ParallaxLayer::Foreground, cocos2d::Vec2(1.2f, .0f), cocos2d::Vec2(x, y + 450));
    _parallaxController->addSpriteToLayerWithAutoZOrder("foreground_2_tree.png", ParallaxController::ParallaxLayer::Foreground, cocos2d::Vec2(.3f, .0f), cocos2d::Vec2(x * .05f, 30));
    _parallaxController->addSpriteToLayerWithAutoZOrder("foreground_3_squirrel.png", ParallaxController::ParallaxLayer::Foreground, cocos2d::Vec2(.4f, .0f), cocos2d::Vec2(x * .4f, 10));
    _parallaxController->addSpriteToLayerWithAutoZOrder("foreground_4_bench.png", ParallaxController::ParallaxLayer::Foreground, cocos2d::Vec2(.8f, .0f), cocos2d::Vec2(x * 1.63f, 55));
    _parallaxController->addSpriteToLayerWithAutoZOrder("foreground_5_bushes.png", ParallaxController::ParallaxLayer::Foreground, cocos2d::Vec2(.6f, .0f), cocos2d::Vec2(x * .45f, y));

    // get the parallax node on focus layer so we get the character reference from it.
    auto parallaxFocusNode = _parallaxController->getParallaxNode(ParallaxController::ParallaxLayer::Focus);
    if (parallaxFocusNode) {
        auto characterNode = parallaxFocusNode->getChildByName("character.png"); // get character node
        if (characterNode) {
            _characterController = std::make_unique<CharacterController>(characterNode, *this->getEventDispatcher()); // init character controller to control the character node and it's behaviour
            _characterController->setup();                                                                              // setup the controller's basic stuff
        }
    }

    return true;
}