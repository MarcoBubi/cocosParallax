#include "GameScene.h"

#include "AssetManagerSingleton.h"
#include "CustomUIButton.h"
#include "ui/CocosGUI.h"


cocos2d::Scene* GameScene::createScene() {
    return GameScene::create();
}

bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    AssetManagerSingleton& assetManager = AssetManagerSingleton::getInstance();                     // set assetmanager as ref so we save a bit of func. calls
    assetManager.setBasePath("textures/");                                                          // specify path for where to look for the textures.

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();                          // get visible size so we can have a viewpoint
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();                             // same for origin point
    float x = origin.x + visibleSize.width * 0.5;                                                   // X for the center of the screen
    float y = origin.y + visibleSize.height * 0.5;                                                  // y for the center of the screen

    _inputController = std::make_unique<InputController>(this, *this->getEventDispatcher());        // init input controller for general inputs in the game, like dragging, etc...
    _inputController->setup();                                                                      // setup the controller's basic stuff

    _uiController = std::make_unique<UIController>(this);                                           // init ui controller to setup UI and scale it depending on resolution, aspect ratio,...
    _uiController->setup();                                                                         // setup the controller's basic stuff

    // TODO: refactor this, no need to use raw pointers, too tired now
    auto jumpButton = CustomUIButton::create(assetManager.getFullPath("jump_button.png"));                                          // creating the jump button 
    _inputController->registerListenerToButton(jumpButton, "jump_event");                                               // registering the event to the jump button from the input controller
    jumpButton->setPosition(cocos2d::Vec2(visibleSize.width / 2 + (origin.x / 2), 150));
    this->addChild(jumpButton, 100);

    _parallaxController = std::make_unique<ParallaxController>(this, *this->getEventDispatcher());  // init parallax controller to control the layers of the parallax nodes
    _parallaxController->setup();                                                                   // setup the controller's basic stuff
    // Add all the textures to the parallax controller
    //Background level
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_1_sky.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.05f, .0f), cocos2d::Vec2(x, y));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_2_sky.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.1f, .0f), cocos2d::Vec2(x, y * .65f));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_4_mountains.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.2f, .0f), cocos2d::Vec2(x, y * .5f));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_3_mountains.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.35f, .0f), cocos2d::Vec2(x, y * .45f));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_5_clouds.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(2.4f, .0f), cocos2d::Vec2(x, y * 1.2f));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_6_clouds.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.45f, .0f), cocos2d::Vec2(x, y * 1.3f));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_8_bushes.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.55f, .0f), cocos2d::Vec2(x, y * .4f));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_9_trees.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.62f, .0f), cocos2d::Vec2(x, y * .45f));
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_10_trees.png", ParallaxController::ParallaxLayer::Background, cocos2d::Vec2(.83f, .0f), cocos2d::Vec2(x, y * .53f));
    
    //Focus layer
    _parallaxController->addSpriteToLayerWithAutoZOrder("background_11_road.png", ParallaxController::ParallaxLayer::Focus, cocos2d::Vec2(0.1f, .0f), cocos2d::Vec2(x, y * .25f));
    _parallaxController->addSpriteToLayerWithAutoZOrder("character.png", ParallaxController::ParallaxLayer::Focus, cocos2d::Vec2(.0f, .0f), cocos2d::Vec2(x * .7f, y * .48f));

    //Foreground layer
    _parallaxController->addSpriteToLayerWithAutoZOrder("foreground_3_clouds.png", ParallaxController::ParallaxLayer::Foreground, cocos2d::Vec2(1.2f, .0f), cocos2d::Vec2(x, y * .65f));
    _parallaxController->addSpriteToLayerWithAutoZOrder("foreground_2_tree.png", ParallaxController::ParallaxLayer::Foreground, cocos2d::Vec2(.3f, .0f), cocos2d::Vec2(x * .05f, y * .45f));
    _parallaxController->addSpriteToLayerWithAutoZOrder("foreground_0_squirrel.png", ParallaxController::ParallaxLayer::Foreground, cocos2d::Vec2(.4f, .0f), cocos2d::Vec2(x * .4f, y * .16f));
    _parallaxController->addSpriteToLayerWithAutoZOrder("foreground_1_bushes.png", ParallaxController::ParallaxLayer::Foreground, cocos2d::Vec2(.6f, .0f), cocos2d::Vec2(x * .45f, y * .4f));
    _parallaxController->addSpriteToLayerWithAutoZOrder("foreground_4_bench.png", ParallaxController::ParallaxLayer::Foreground, cocos2d::Vec2(.8f, .0f), cocos2d::Vec2(x * 1.63f, y * .23f));

    // the character is not a direct child of the game scene, but he's found in the parallax node - that's why we get him from there
    // maybe a better approach would be to have a specific layer for the character itself?
    auto parallaxFocusNode = _parallaxController->getParallaxNode(ParallaxController::ParallaxLayer::Focus);
    if (parallaxFocusNode)
    {
        auto characterNode = parallaxFocusNode->getChildByName("character.png");
        
        if (characterNode) {
            _characterController = std::make_unique<CharacterController>(characterNode, *this->getEventDispatcher());   // init character controller to controll the character node and it's behaviour
            _characterController->setup();                                                                              // setup the controller's basic stuff
        }
        
    }

    return true;
}