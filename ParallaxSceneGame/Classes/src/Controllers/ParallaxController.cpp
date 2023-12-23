#include "Controllers/ParallaxController.h"
#include "AssetManager/AssetManagerSingleton.h"
#include "Game/GameConstants.h"
#include "Game/GameEvents.h"
#include "Game/GameSettings.h"

ParallaxController::ParallaxController(cocos2d::Node* parent, cocos2d::EventDispatcher& eventDispatcher)
    : _parent(parent), _eventDispatcher(eventDispatcher) {
    // Initialization can be performed here if needed
}

ParallaxController::~ParallaxController()
{

}

void ParallaxController::setup() {
    // This could be macroed to look nicer, but IMO it's quite readable so won't touch it
    // Register onSceneDragged(...) to react on specific game event EVENT_SCENE_DRAGGED
    auto listener = cocos2d::EventListenerCustom::create(GameEvents::EVENT_SCENE_DRAGGED, [this](cocos2d::EventCustom* event) {
        this->onSceneDragged(event);
        });
    _eventDispatcher.addEventListenerWithSceneGraphPriority(listener, _parent);

    // Init parallax nodes for each layer
    _parallaxNodes[ParallaxLayer::Background] = cocos2d::ParallaxNode::create();
    _parallaxNodes[ParallaxLayer::Focus] = cocos2d::ParallaxNode::create();
    _parallaxNodes[ParallaxLayer::Foreground] = cocos2d::ParallaxNode::create();

    // Add nodes to parent
    for (auto& pair : _parallaxNodes) {
        _parent->addChild(pair.second);
    }
}

void ParallaxController::update(float delta) {
    // Implement any update logic for the parallax layers if needed
}

void ParallaxController::addSpriteToLayer(const std::string& filename, ParallaxLayer layer,
    const cocos2d::Vec2& ratio, const cocos2d::Vec2& originalPosition, int zOrder) {
    // Get sprite from asset manager
    auto sprite = AssetManagerSingleton::getInstance().GetSprite(filename);

    if (!sprite) {
        // Not sure what approach is better, but I think the error is more viable.
        // We load an image that doesn't exist, perhaps we may not function correctly
        // since we have no placeholders, so I went with the error option.
        throw std::runtime_error("Failed to load sprite: " + filename);
    }

    // Set name to sprite
    sprite->setName(filename);
    // Scale sprite with the current resolution so it's properly displayed on the screen
    scaleSpriteForCurrentResolution(*sprite);
    // We are dealing with a horizontal parallax system, so we set the anchor to the bottom mid of the parent
    sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.0f));

    // Calculate scaling factors for the y position
    float scaleFactorHeight = GameSettings::getInstance().getScaleFactorHeight();

    // Apply the scale factors to the y position because we are dealing with horizontal parallax
    // and we anchored to the bottom mid, so horizontal values aren't relevant 
    cocos2d::Vec2 scaledPosition(originalPosition.x, originalPosition.y * scaleFactorHeight);

    // Add the sprite to the parallax node with the adjusted position
    _parallaxNodes[layer]->addChild(sprite, zOrder, ratio, scaledPosition);
    // Keep in mind the highest Z order :)
    _highestZOrders[layer] = std::max(_highestZOrders[layer], zOrder);
}

void ParallaxController::addSpriteToLayerWithAutoZOrder(const std::string& filename, ParallaxLayer layer, const cocos2d::Vec2& ratio, const cocos2d::Vec2& position) {
    // If we don't specify the z order we just add it to the last added
    int nextZOrder = _highestZOrders[layer] + 1;
    addSpriteToLayer(filename, layer, ratio, position, nextZOrder);
}

cocos2d::ParallaxNode* ParallaxController::getParallaxNode(ParallaxLayer layer) {
    // Get a node layer
    return _parallaxNodes[layer];
}

void ParallaxController::scaleSpriteForCurrentResolution(cocos2d::Sprite& sprite) {
    // Design resolution and aspect ratio
    GameSettings& gameSettings = GameSettings::getInstance();

    // Check if aspect ratios are different
    float uniformScaleFactor = (gameSettings.getCurrentAspectRatio() != gameSettings.getDesignAspectRatio()) ?
        std::min(gameSettings.getScaleFactorWidth(), gameSettings.getScaleFactorHeight()) :
        gameSettings.getScaleFactorWidth(); // Use width as a baseline for scaling if aspect ratios are the same because of horizontal parallax

    // Scale the sprite
    sprite.setScale(uniformScaleFactor);
}

void ParallaxController::onSceneDragged(cocos2d::EventCustom* event) {
    // Dragged difference sent through the event
    auto diff = static_cast<cocos2d::Vec2*>(event->getUserData());
    if (diff) {
        // We allow the resolution to go double the sides because the images are set to 2* designResolution width        
        float limit = cocos2d::Director::getInstance()->getVisibleSize().width / 2;

        for (auto& pair : _parallaxNodes) {
            if (pair.first == ParallaxLayer::Focus) { // The focus layer should be static so the front and back moves around it
                continue;
            }
            auto node = pair.second;
            auto newPos = node->getPosition() + cocos2d::Vec2(diff->x, 0); // Modify y-coordinate as needed

            // We want to allow some movement to the left and right, so the parallax effect can be spotted
            newPos.x = std::max(newPos.x, -limit);
            newPos.x = std::min(newPos.x, limit);

            node->setPosition(newPos); // Update the position of the node
        }
    }
}
