#include "ParallaxController.h"

#include "AssetManagerSingleton.h"
#include "GameEvents.h"

ParallaxController::ParallaxController(cocos2d::Node* parent, cocos2d::EventDispatcher& eventDispatcher) 
    : _parent(parent), _eventDispatcher(eventDispatcher) {
    // Note: setup() is called separately, not in the constructor
}

void ParallaxController::setup() {
    auto listener = cocos2d::EventListenerCustom::create(GameEvents::EVENT_SCENE_DRAGGED, [this](cocos2d::EventCustom* event) {
        this->onSceneDragged(event);
        });
    _eventDispatcher.addEventListenerWithSceneGraphPriority(listener, _parent);

    // Initialize Parallax Nodes for each layer
    _parallaxNodes[ParallaxLayer::Background] = cocos2d::ParallaxNode::create();
    _parallaxNodes[ParallaxLayer::Focus] = cocos2d::ParallaxNode::create();
    _parallaxNodes[ParallaxLayer::Foreground] = cocos2d::ParallaxNode::create();

    // Add Parallax Nodes to the parent node
    for (auto& pair : _parallaxNodes) {
        _parent->addChild(pair.second);
    }
}

void ParallaxController::update(float delta) {
    // Implement any update logic for the parallax layers if needed
}

void ParallaxController::addSpriteToLayer(const std::string& filename, ParallaxLayer layer,
    const cocos2d::Vec2& ratio, const cocos2d::Vec2& originalPosition, int zOrder) {

    auto sprite = AssetManagerSingleton::getInstance().GetSprite(filename);
    if (sprite) {
        sprite->setName(filename);
        scaleSpriteForCurrentResolution(*sprite);
        sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.0f));

        // Calculate scaling factors for position
        cocos2d::Size designResolution(1920, 1080);
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        float scaleFactorWidth = visibleSize.width / designResolution.width;
        float scaleFactorHeight = visibleSize.height / designResolution.height;

        // Apply the scale factors to the position
        cocos2d::Vec2 scaledPosition(originalPosition.x,
            originalPosition.y * scaleFactorHeight);

        // Add the sprite to the parallax node with the adjusted position
        _parallaxNodes[layer]->addChild(sprite, zOrder, ratio, scaledPosition);

        _highestZOrders[layer] = std::max(_highestZOrders[layer], zOrder);
    }
}

void ParallaxController::addSpriteToLayerWithAutoZOrder(const std::string& filename, ParallaxLayer layer, const cocos2d::Vec2& ratio, const cocos2d::Vec2& position) {
    int nextZOrder = _highestZOrders[layer] + 1;
    addSpriteToLayer(filename, layer, ratio, position, nextZOrder);
}

cocos2d::ParallaxNode* ParallaxController::getParallaxNode(ParallaxLayer layer) {
    return _parallaxNodes[layer];
}

void ParallaxController::scaleSpriteForCurrentResolution(cocos2d::Sprite& sprite) {
    // Design resolution and aspect ratio
    cocos2d::Size designResolution(1920, 1080);
    float designAspectRatio = designResolution.width / designResolution.height;

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize(); // get visible size
    // Current screen resolution and aspect ratio
    float currentAspectRatio = visibleSize.width / visibleSize.height;

    // Calculate individual scale factors
    float scaleFactorWidth = visibleSize.width / designResolution.width;
    float scaleFactorHeight = visibleSize.height / designResolution.height;

    // Check if aspect ratios are different
    float uniformScaleFactor = (currentAspectRatio != designAspectRatio) ?
        std::min(scaleFactorWidth, scaleFactorHeight) :
        scaleFactorWidth; // Use width as a baseline for scaling if aspect ratios are the same

    // Apply the uniform scale factor to the sprite
    sprite.setScale(uniformScaleFactor);
    // Optionally, adjust the position if necessary, based on your game's needs
}

void ParallaxController::onSceneDragged(cocos2d::EventCustom* event) {
    auto diff = static_cast<cocos2d::Vec2*>(event->getUserData());
    if (diff) {
        // Define movement limits
        // we allow the resolution to go double the sides because the images are set to 2* designResolution width
        float limit = cocos2d::Director::getInstance()->getVisibleSize().width / 2; 


        // Iterate over each parallax layer and update its position
        for (auto& pair : _parallaxNodes) {
            if (pair.first == ParallaxLayer::Focus) // the focus layer should be static so the front and back moves around it
            {
                continue;
            }
            auto node = pair.second;
            auto newPos = node->getPosition() + cocos2d::Vec2(diff->x, 0); // Modify y-coordinate as needed

            // Apply limits to the movement
            newPos.x = std::max(newPos.x, -limit);
            newPos.x = std::min(newPos.x, limit);

            node->setPosition(newPos);
        }
    }
}